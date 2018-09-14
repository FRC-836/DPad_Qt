#include <iostream>

#include <qapplication.h>

#include "DPad.h"

int main(int argc, char** argv)
{
  QApplication app(argc, argv);

  DPad d;

  d.show();

  return app.exec();
}