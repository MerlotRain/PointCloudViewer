#ifndef __PCV_TOOLBAR_H__
#define __PCV_TOOLBAR_H__

#include <QToolBar>
#include <QWidget>

class QAction;
class QMenu;

namespace pcv {

class ToolBarPrivate;
class ToolBar : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(Qt::Orientation orientation READ orientation WRITE setOrientation NOTIFY
                       orientationChanged)
    Q_PROPERTY(QSize iconSize READ iconSize WRITE setIconSize NOTIFY iconSizeChanged)
public:
    explicit ToolBar(QWidget *parent = nullptr);
    ~ToolBar();

    void setOrientation(Qt::Orientation orientation);
    Qt::Orientation orientation() const;

    void clear();

    using QWidget::addAction;
    QAction *addAction(QAction *action);
    void addMenu(QMenu *menu);

    QAction *addSeparator();
    QAction *insertSeparator(QAction *before);

    QAction *addWidget(QWidget *widget);
    QAction *insertWidget(QAction *before, QWidget *widget);


public Q_SLOTS:
    void setIconSize(const QSize &iconSize);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    Q_DISABLE_COPY(ToolBar)
    Q_DECLARE_PRIVATE(ToolBar)
};

}// namespace pcv

#endif//__PCV_TOOLBAR_H__