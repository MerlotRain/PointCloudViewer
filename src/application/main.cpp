#include "mainwindow.h"
#include <QApplication>
#include <pcv.h>
#include <pcv_app.h>
#include <spdlog/spdlog.h>

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    pcv::App::singleApp();

    QMainWindow *w = new QMainWindow();
    pcv::PCVMainWindow *pcvMainWindow = new pcv::PCVMainWindow(w);
    pcv::App::singleApp()->setMainWindowBase(pcvMainWindow);
    w->show();
    return app.exec();
}