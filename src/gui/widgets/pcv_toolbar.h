#ifndef __PCV_TOOLBAR_H__
#define __PCV_TOOLBAR_H__

#include <QIcon>
#include <QWidget>

class QAction;
class QMenu;

namespace pcv {

class ToolBar : public QWidget
{
    Q_OBJECT
public:
    explicit ToolBar(QWidget *parent = nullptr);
    ~ToolBar();
    using QWidget::addAction;
    QAction *addAction(QAction *action);
    void addMenu(QMenu *menu);
    void addSeparator();

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    Q_DISABLE_COPY(ToolBar)
};

}// namespace pcv

#endif//__PCV_TOOLBAR_H__