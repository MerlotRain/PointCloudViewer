#include "pcv_collapsiblegroupbox.h"

#include <QApplication>
#include <QMouseEvent>
#include <QPushButton>
#include <QScrollArea>
#include <QStyleOptionGroupBox>
#include <QToolButton>

namespace pcv {

const QString COLLAPSE_HIDE_BORDER_FIX =
        QStringLiteral("CollapsibleGroupBoxBasic { border: none; }");

CollapsibleGroupBoxBasic::CollapsibleGroupBoxBasic(QWidget *parent) : QGroupBox(parent) { init(); }

CollapsibleGroupBoxBasic::CollapsibleGroupBoxBasic(const QString &title, QWidget *parent)
    : QGroupBox(title, parent)
{
    init();
}

void CollapsibleGroupBoxBasic::init()
{
    // variables
    mCollapsed = false;
    mInitFlat = false;
    mInitFlatChecked = false;
    mScrollOnExpand = true;
    mShown = false;
    mParentScrollArea = nullptr;
    mSyncParent = nullptr;
    mAltDown = false;
    mShiftDown = false;
    mTitleClicked = false;

    // init icons
    mCollapseIcon = QIcon(QStringLiteral("/mIconCollapse.svg"));
    mExpandIcon = QIcon(QStringLiteral("/mIconExpand.svg"));

    // collapse button
    mCollapseButton = new GroupBoxCollapseButton(this);
    mCollapseButton->setObjectName(QStringLiteral("collapseButton"));
    mCollapseButton->setAutoRaise(true);
    mCollapseButton->setFixedSize(16, 16);
    mCollapseButton->setIconSize(QSize(12, 12));
    mCollapseButton->setIcon(mCollapseIcon);
    setFocusPolicy(Qt::StrongFocus);

    connect(mCollapseButton, &QAbstractButton::clicked, this,
            &CollapsibleGroupBoxBasic::toggleCollapsed);
    connect(this, &QGroupBox::toggled, this, &CollapsibleGroupBoxBasic::checkToggled);
    connect(this, &QGroupBox::clicked, this, &CollapsibleGroupBoxBasic::checkClicked);
}

void CollapsibleGroupBoxBasic::showEvent(QShowEvent *event)
{
    // initialize widget on first show event only
    if (mShown)
    {
        event->accept();
        return;
    }

    // check if groupbox was set to flat in Designer or in code
    if (!mInitFlatChecked)
    {
        mInitFlat = isFlat();
        mInitFlatChecked = true;
    }

    // find parent QScrollArea - this might not work in complex layouts - should we look deeper?
    if (parent() && parent()->parent())
        mParentScrollArea = qobject_cast<QScrollArea *>(parent()->parent()->parent());
    else
        mParentScrollArea = nullptr;

    updateStyle();

    // expand if needed - any calls to setCollapsed() before only set mCollapsed, but have UI effect
    if (mCollapsed) { setCollapsed(mCollapsed); }
    else
    {
        // emit signal for connections using collapsed state
        emit collapsedStateChanged(isCollapsed());
    }

    // verify triangle mirrors groupbox's enabled state
    mCollapseButton->setEnabled(isEnabled());

    // set mShown after first setCollapsed call or expanded groupboxes
    // will scroll scroll areas when first shown
    mShown = true;
    event->accept();
}

void CollapsibleGroupBoxBasic::mousePressEvent(QMouseEvent *event)
{
    // avoid leaving checkbox in pressed state if alt- or shift-clicking
    if (event->modifiers() & (Qt::AltModifier | Qt::ControlModifier | Qt::ShiftModifier) &&
        titleRect().contains(event->pos()) && isCheckable())
    {
        event->ignore();
        return;
    }

    // default behavior - pass to QGroupBox
    QGroupBox::mousePressEvent(event);
}

void CollapsibleGroupBoxBasic::mouseReleaseEvent(QMouseEvent *event)
{
    mAltDown = (event->modifiers() & (Qt::AltModifier | Qt::ControlModifier));
    mShiftDown = (event->modifiers() & Qt::ShiftModifier);
    mTitleClicked = (titleRect().contains(event->pos()));

    // sync group when title is alt-clicked
    // collapse/expand when title is clicked and non-checkable
    // expand current and collapse others on shift-click
    if (event->button() == Qt::LeftButton && mTitleClicked &&
        (mAltDown || mShiftDown || !isCheckable()))
    {
        toggleCollapsed();
        return;
    }

    // default behavior - pass to QGroupBox
    QGroupBox::mouseReleaseEvent(event);
}

void CollapsibleGroupBoxBasic::changeEvent(QEvent *event)
{
    // always re-enable mCollapseButton when groupbox was previously disabled
    // e.g. resulting from a disabled parent of groupbox, or a signal/slot connection

    // default behavior - pass to QGroupBox
    QGroupBox::changeEvent(event);

    if (event->type() == QEvent::EnabledChange && isEnabled()) mCollapseButton->setEnabled(true);
}

void CollapsibleGroupBoxBasic::setSyncGroup(const QString &grp)
{
    mSyncGroup = grp;
    QString tipTxt;
    if (!grp.isEmpty())
    {
        tipTxt = tr("Ctrl (or Alt)-click to toggle all") + '\n' +
                 tr("Shift-click to expand, then collapse others");
    }
    mCollapseButton->setToolTip(tipTxt);
}

QRect CollapsibleGroupBoxBasic::titleRect() const
{
    QStyleOptionGroupBox box;
    initStyleOption(&box);
    return style()->subControlRect(QStyle::CC_GroupBox, &box, QStyle::SC_GroupBoxLabel, this);
}

void CollapsibleGroupBoxBasic::clearModifiers()
{
    mCollapseButton->setAltDown(false);
    mCollapseButton->setShiftDown(false);
    mAltDown = false;
    mShiftDown = false;
}

void CollapsibleGroupBoxBasic::checkToggled(bool chkd)
{
    Q_UNUSED(chkd)
    mCollapseButton->setEnabled(true);// always keep enabled
}

void CollapsibleGroupBoxBasic::checkClicked(bool chkd)
{
    // expand/collapse when checkbox toggled by user click.
    // don't do this on toggle signal, otherwise group boxes will default to collapsed
    // in option dialog constructors, reducing discovery of options by new users and
    // overriding user's auto-saved collapsed/expanded state for the group box
    if (chkd && isCollapsed()) setCollapsed(false);
    else if (!chkd && !isCollapsed())
        setCollapsed(true);
}

void CollapsibleGroupBoxBasic::toggleCollapsed()
{
    // verify if sender is this group box's collapse button
    GroupBoxCollapseButton *collBtn = qobject_cast<GroupBoxCollapseButton *>(QObject::sender());
    const bool senderCollBtn = (collBtn && collBtn == mCollapseButton);

    mAltDown = (mAltDown || mCollapseButton->altDown());
    mShiftDown = (mShiftDown || mCollapseButton->shiftDown());

    // find any sync group siblings and toggle them
    if ((senderCollBtn || mTitleClicked) && (mAltDown || mShiftDown) && !mSyncGroup.isEmpty())
    {
        // get pointer to parent or grandparent widget
        if (auto *lParentWidget = parentWidget())
        {
            mSyncParent = lParentWidget;
            if (mSyncParent->parentWidget())
            {
                // don't use whole app for grandparent (common for dialogs that use main window for parent)
                if (mSyncParent->parentWidget()->objectName() != QLatin1String("QgisApp"))
                {
                    mSyncParent = mSyncParent->parentWidget();
                }
            }
        }
        else { mSyncParent = nullptr; }

        if (mSyncParent)
        {
            const bool thisCollapsed = mCollapsed;// get state of current box before its changed
            const auto groupBoxes{mSyncParent->findChildren<CollapsibleGroupBoxBasic *>()};
            for (CollapsibleGroupBoxBasic *grpbox: groupBoxes)
            {
                if (grpbox->syncGroup() == syncGroup() && grpbox->isEnabled())
                {
                    if (mShiftDown && grpbox == this)
                    {
                        // expand current group box on shift-click
                        setCollapsed(false);
                    }
                    else { grpbox->setCollapsed(mShiftDown ? true : !thisCollapsed); }
                }
            }

            clearModifiers();
            return;
        }
    }

    // expand current group box on shift-click, even if no sync group
    if (mShiftDown) { setCollapsed(false); }
    else { setCollapsed(!mCollapsed); }

    clearModifiers();
}

void CollapsibleGroupBoxBasic::setStyleSheet(const QString &style)
{
    QGroupBox::setStyleSheet(style);
}

void CollapsibleGroupBoxBasic::updateStyle()
{
    setUpdatesEnabled(false);

    QStyleOptionGroupBox box;
    initStyleOption(&box);
    const QRect rectFrame =
            style()->subControlRect(QStyle::CC_GroupBox, &box, QStyle::SC_GroupBoxFrame, this);
    const QRect rectTitle = titleRect();

    // margin/offset defaults
    const int marginLeft = 20;// title margin for disclosure triangle
    const int marginRight = 5;// a little bit of space on the right, to match space on the left
    int offsetLeft = 0;       // offset for oxygen theme
    const int offsetStyle =
            QApplication::style()->objectName().contains(QLatin1String("macintosh")) ? 8 : 0;
    const int topBuffer = 1 + offsetStyle;// space between top of title or triangle and widget above
    int offsetTop = topBuffer;
    int offsetTopTri = topBuffer;// offset for triangle

    if (mCollapseButton->height() <
        rectTitle.height())// triangle's height > title text's, offset triangle
    {
        offsetTopTri += (rectTitle.height() - mCollapseButton->height()) / 2;
        //    offsetTopTri += rectTitle.top();
    }
    else if (rectTitle.height() <
             mCollapseButton->height())// title text's height < triangle's, offset title
    {
        offsetTop += (mCollapseButton->height() - rectTitle.height()) / 2;
    }

    // calculate offset if frame overlaps triangle (oxygen theme)
    // using an offset of 6 pixels from frame border
    if (QApplication::style()->objectName().compare(QLatin1String("oxygen"), Qt::CaseInsensitive) ==
        0)
    {
        QStyleOptionGroupBox box;
        initStyleOption(&box);
        const QRect rectFrame =
                style()->subControlRect(QStyle::CC_GroupBox, &box, QStyle::SC_GroupBoxFrame, this);
        const QRect rectCheckBox = style()->subControlRect(QStyle::CC_GroupBox, &box,
                                                           QStyle::SC_GroupBoxCheckBox, this);
        if (rectFrame.left() <= 0) offsetLeft = 6 + rectFrame.left();
        if (rectFrame.top() <= 0)
        {
            if (isCheckable())
            {
                // if is checkable align with checkbox
                offsetTop = (rectCheckBox.height() / 2) - (mCollapseButton->height() / 2) +
                            rectCheckBox.top();
                offsetTopTri = offsetTop + 1;
            }
            else
            {
                offsetTop = 6 + rectFrame.top();
                offsetTopTri = offsetTop;
            }
        }
    }

    // customize style sheet for collapse/expand button and force left-aligned title
    QString ss;
    if (QApplication::style()->objectName().contains(QLatin1String("macintosh")))
    {
        ss += QLatin1String("CollapsibleGroupBoxBasic, CollapsibleGroupBox {");
        ss += QStringLiteral("  margin-top: %1px;").arg(topBuffer + rectFrame.top());
        ss += '}';
    }
    ss += QLatin1String("CollapsibleGroupBoxBasic::title, CollapsibleGroupBox::title {");
    ss += QLatin1String("  subcontrol-origin: margin;");
    ss += QLatin1String("  subcontrol-position: top left;");
    ss += QStringLiteral("  margin-left: %1px;").arg(marginLeft);
    ss += QStringLiteral("  margin-right: %1px;").arg(marginRight);
    ss += QStringLiteral("  left: %1px;").arg(offsetLeft);
    ss += QStringLiteral("  top: %1px;").arg(offsetTop);
    if (QApplication::style()->objectName().contains(QLatin1String("macintosh")))
    {
        ss += QLatin1String("  background-color: rgba(0,0,0,0)");
    }
    ss += '}';
    setStyleSheet(styleSheet() + ss);

    // clear toolbutton default background and border and apply offset
    QString ssd;
    ssd = QStringLiteral("CollapsibleGroupBoxBasic > QToolButton#%1, CollapsibleGroupBox > "
                         "QToolButton#%1 {")
                  .arg(mCollapseButton->objectName());
    ssd += QLatin1String("  background-color: rgba(255, 255, 255, 0); border: none;");
    ssd += QStringLiteral(
                   "} CollapsibleGroupBoxBasic > QToolButton#%1:focus, CollapsibleGroupBox > "
                   "QToolButton#%1:focus {  border: 1px solid palette(highlight); }")
                   .arg(mCollapseButton->objectName());
    mCollapseButton->setStyleSheet(ssd);
    if (offsetLeft != 0 || offsetTopTri != 0) mCollapseButton->move(offsetLeft, offsetTopTri);
    setUpdatesEnabled(true);
}

void CollapsibleGroupBoxBasic::setCollapsed(bool collapse)
{
    const bool changed = collapse != mCollapsed;
    mCollapsed = collapse;

    if (!isVisible()) return;

    // for consistent look/spacing across platforms when collapsed
    if (!mInitFlat)// skip if initially set to flat in Designer
        setFlat(collapse);

    // avoid flicker in X11
    // NOTE: this causes app to crash when loading a project that hits a group box with
    //       'collapse' set via dynamic property or in code (especially if auto-launching project)
    // TODO: find another means of avoiding the X11 flicker
    //  QApplication::processEvents();

    // handle visual fixes for collapsing/expanding
    collapseExpandFixes();

    // set maximum height to hide contents - does this work in all envs?
    // setMaximumHeight( collapse ? 25 : 16777215 );
    setMaximumHeight(collapse ? titleRect().bottom() + 6 : 16777215);
    mCollapseButton->setIcon(collapse ? mExpandIcon : mCollapseIcon);

    // if expanding and is in a QScrollArea, scroll down to make entire widget visible
    if (mShown && mScrollOnExpand && !collapse && mParentScrollArea)
    {
        // process events so entire widget is shown
        QApplication::processEvents();
        mParentScrollArea->setUpdatesEnabled(false);
        mParentScrollArea->ensureWidgetVisible(this);
        //and then make sure the top of the widget is visible - otherwise tall group boxes
        //scroll to their centres, which is disorienting for users
        mParentScrollArea->ensureWidgetVisible(mCollapseButton, 0, 5);
        mParentScrollArea->setUpdatesEnabled(true);
    }
    // emit signal for connections using collapsed state
    if (changed) emit collapsedStateChanged(isCollapsed());
}

void CollapsibleGroupBoxBasic::collapseExpandFixes()
{
    // handle child widgets so they don't paint while hidden
    const char *hideKey = "CollGrpBxHide";

    QString ss = styleSheet();
    if (mCollapsed)
    {
        if (!ss.contains(COLLAPSE_HIDE_BORDER_FIX))
        {
            ss += COLLAPSE_HIDE_BORDER_FIX;
            setStyleSheet(ss);
        }

        const auto constChildren = children();
        for (QObject *child: constChildren)
        {
            QWidget *w = qobject_cast<QWidget *>(child);
            if (w && w != mCollapseButton)
            {
                w->setProperty(hideKey, true);
                w->hide();
            }
        }
    }
    else// on expand
    {
        if (ss.contains(COLLAPSE_HIDE_BORDER_FIX))
        {
            ss.replace(COLLAPSE_HIDE_BORDER_FIX, QString());
            setStyleSheet(ss);
        }

        const auto constChildren = children();
        for (QObject *child: constChildren)
        {
            QWidget *w = qobject_cast<QWidget *>(child);
            if (w && w != mCollapseButton)
            {
                if (w->property(hideKey).toBool()) w->show();
            }
        }
    }
}


// ----

CollapsibleGroupBox::CollapsibleGroupBox(QWidget *parent) : CollapsibleGroupBoxBasic(parent)
{
    init();
}

CollapsibleGroupBox::CollapsibleGroupBox(const QString &title, QWidget *parent)
    : CollapsibleGroupBoxBasic(title, parent)
{
    init();
}

CollapsibleGroupBox::~CollapsibleGroupBox() { saveState(); }

void CollapsibleGroupBox::init()
{
    // variables
    mSaveCollapsedState = true;
    // NOTE: only turn on mSaveCheckedState for groupboxes NOT used
    // in multiple places or used as options for different parent objects
    mSaveCheckedState = false;

    connect(this, &QObject::objectNameChanged, this, &CollapsibleGroupBox::loadState);

    // save state immediately when collapsed state changes, so that other widgets created
    // before this one is destroyed will correctly restore the new collapsed state
    connect(this, &CollapsibleGroupBoxBasic::collapsedStateChanged, this,
            &CollapsibleGroupBox::saveState);
}

void CollapsibleGroupBox::showEvent(QShowEvent *event)
{
    // initialize widget on first show event only
    if (mShown)
    {
        event->accept();
        return;
    }

    // check if groupbox was set to flat in Designer or in code
    if (!mInitFlatChecked)
    {
        mInitFlat = isFlat();
        mInitFlatChecked = true;
    }

    loadState();

    CollapsibleGroupBoxBasic::showEvent(event);
}

QString CollapsibleGroupBox::saveKey() const
{
    if (objectName().isEmpty() || (mSettingGroup.isEmpty() && window()->objectName().isEmpty()))
        return QString();

    QString saveKey = '/' + objectName();
    const QString setgrp = mSettingGroup.isEmpty() ? window()->objectName() : mSettingGroup;
    saveKey = '/' + setgrp + saveKey;
    saveKey = QStringLiteral("CollapsibleGroupBox") + saveKey;
    return saveKey;
}

void CollapsibleGroupBox::loadState()
{
    if (!isEnabled() || (!mSaveCollapsedState && !mSaveCheckedState)) return;

    const QString key = saveKey();
    if (key.isEmpty()) return;

    setUpdatesEnabled(false);
    setUpdatesEnabled(true);
}

void CollapsibleGroupBox::saveState() const
{
    if (!mShown || !isEnabled() || (!mSaveCollapsedState && !mSaveCheckedState)) return;

    const QString key = saveKey();
    if (key.isEmpty()) return;
}


void GroupBoxCollapseButton::mouseReleaseEvent(QMouseEvent *event)
{
    mAltDown = (event->modifiers() & (Qt::AltModifier | Qt::ControlModifier));
    mShiftDown = (event->modifiers() & Qt::ShiftModifier);
    QToolButton::mouseReleaseEvent(event);
}

}// namespace pcv