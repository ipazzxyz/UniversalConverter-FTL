#include "../inc/Interface.hpp"

#include <QApplication>

int main(int argc, char *argv[])
{
  QApplication app(argc, argv);
  Window w;
  app.exec();
}