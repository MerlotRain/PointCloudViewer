#include "mainwindow.h"

namespace pcv {

PCVMainWindow::PCVMainWindow(QMainWindow *window) : m_window(window) {}

PCVMainWindow::~PCVMainWindow() {}

QMainWindow *PCVMainWindow::window() { return m_window; }

void PCVMainWindow::addDockWidget(Qt::DockWidgetArea area, QDockWidget *dock)
{
    if (m_window) m_window->addDockWidget(area, dock);
}

void PCVMainWindow::addDockWidget(Qt::DockWidgetArea area, QDockWidget *dock,
                                  Qt::Orientation orientation)
{
    if (m_window) m_window->addDockWidget(area, dock, orientation);
}

void PCVMainWindow::addWidget(QWidget *widget) {}

}// namespace pcv