#include <iostream>

#include <qapplication.h>

#include "DPad.h"

int main(int argc, char** argv)
{
  QApplication app(argc, argv);

  DPad d;

  d.show();
  d.pressButton(DPad::Button::LEFT);
  d.pressButton(DPad::Button::UP);

  return app.exec();
}