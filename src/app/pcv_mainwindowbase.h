#ifndef __PCV_MAINWINDOWBASE_H__
#define __PCV_MAINWINDOWBASE_H__

#include <QDockWidget>
#include <QMainWindow>

namespace pcv {

class MainWindowBase
{
public:
    MainWindowBase() = default;
    virtual ~MainWindowBase() = default;
    virtual QMainWindow *window() = 0;
    virtual void addDockWidget(Qt::DockWidgetArea area, QDockWidget *dock) = 0;
    virtual void addDockWidget(Qt::DockWidgetArea area, QDockWidget *dock,
                               Qt::Orientation orientation) = 0;
    virtual void addWidget(QWidget *widget) = 0;
};

}// namespace pcv

#endif//__PCV_MAINWINDOWBASE_H__