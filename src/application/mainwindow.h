#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <pcv_mainwindowbase.h>

namespace pcv {

class PCVMainWindow : public MainWindowBase
{
public:
    PCVMainWindow(QMainWindow *window);
    ~PCVMainWindow();
    QMainWindow *window() override;
    void addDockWidget(Qt::DockWidgetArea area, QDockWidget *dock) override;
    void addDockWidget(Qt::DockWidgetArea area, QDockWidget *dock,
                       Qt::Orientation orientation) override;
    void addWidget(QWidget *widget) override;

private:
    QMainWindow *m_window;
};

}// namespace pcv


#endif//MAINWINDOW_H