#include "mainwindow.hpp"
#include <QApplication>
int main(int argc, char *argv[])
{
  QApplication app(argc, argv);
  MainWindow w;
  return app.exec();
}