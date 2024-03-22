#ifndef __PCV_COLLAPSIBLEGROUPBOX_H__
#define __PCV_COLLAPSIBLEGROUPBOX_H__

#include <QGroupBox>
#include <QPointer>
#include <QToolButton>

#include "pcv_gui_global.h"

class QMouseEvent;
class QToolButton;
class QScrollArea;

namespace pcv {


class GUI_EXPORT GroupBoxCollapseButton : public QToolButton
{
    Q_OBJECT

public:
    GroupBoxCollapseButton(QWidget *parent = nullptr) : QToolButton(parent) {}
    bool altDown() const { return mAltDown; }
    void setAltDown(bool updown) { mAltDown = updown; }
    bool shiftDown() const { return mShiftDown; }
    void setShiftDown(bool shiftdown) { mShiftDown = shiftdown; }

protected:
    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    bool mAltDown = false;
    bool mShiftDown = false;
};

class GUI_EXPORT CollapsibleGroupBoxBasic : public QGroupBox
{
    Q_OBJECT
    Q_PROPERTY(bool collapsed READ isCollapsed WRITE setCollapsed USER true)
    Q_PROPERTY(QString syncGroup READ syncGroup WRITE setSyncGroup)
    Q_PROPERTY(bool scrollOnExpand READ scrollOnExpand WRITE setScrollOnExpand)

public:
    CollapsibleGroupBoxBasic(QWidget *parent = nullptr);
    CollapsibleGroupBoxBasic(const QString &title, QWidget *parent = nullptr);
    bool isCollapsed() const { return mCollapsed; }
    void setCollapsed(bool collapse);
    QString syncGroup() const { return mSyncGroup; }
    void setSyncGroup(const QString &grp);
    void setScrollOnExpand(bool scroll) { mScrollOnExpand = scroll; }
    bool scrollOnExpand() { return mScrollOnExpand; }

signals:
    void collapsedStateChanged(bool collapsed);

public slots:
    void checkToggled(bool ckd);
    void checkClicked(bool ckd);
    void toggleCollapsed();
    void setStyleSheet(const QString &style);

protected:
    void init();
    void collapseExpandFixes();

    void showEvent(QShowEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void changeEvent(QEvent *event) override;

    void updateStyle();
    QRect titleRect() const;
    void clearModifiers();

    bool mCollapsed;
    bool mInitFlat;
    bool mInitFlatChecked;
    bool mScrollOnExpand;
    bool mShown;
    QScrollArea *mParentScrollArea = nullptr;
    GroupBoxCollapseButton *mCollapseButton = nullptr;
    QWidget *mSyncParent = nullptr;
    QString mSyncGroup;
    bool mAltDown;
    bool mShiftDown;
    bool mTitleClicked;

    QIcon mCollapseIcon;
    QIcon mExpandIcon;
};

class GUI_EXPORT CollapsibleGroupBox : public CollapsibleGroupBoxBasic
{
    Q_OBJECT
    Q_PROPERTY(bool saveCollapsedState READ saveCollapsedState WRITE setSaveCollapsedState)
    Q_PROPERTY(bool saveCheckedState READ saveCheckedState WRITE setSaveCheckedState)

public:
    CollapsibleGroupBox(QWidget *parent = nullptr);
    CollapsibleGroupBox(const QString &title, QWidget *parent = nullptr);
    ~CollapsibleGroupBox() override;

    void setSaveCollapsedState(bool save) { mSaveCollapsedState = save; }
    void setSaveCheckedState(bool save) { mSaveCheckedState = save; }
    bool saveCollapsedState() { return mSaveCollapsedState; }
    bool saveCheckedState() { return mSaveCheckedState; }

    void setSettingGroup(const QString &group) { mSettingGroup = group; }
    QString settingGroup() const { return mSettingGroup; }

protected slots:
    void loadState();
    void saveState() const;

protected:
    void init();
    void showEvent(QShowEvent *event) override;
    QString saveKey() const;

    bool mSaveCollapsedState;
    bool mSaveCheckedState;
    QString mSettingGroup;
};

}// namespace pcv

#endif//__PCV_COLLAPSIBLEGROUPBOX_H__
