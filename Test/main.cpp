#include <iostream>

#include <qapplication.h>
#include <qpushbutton.h>

#include "DPad.h"

int main(int argc, char** argv)
{
  QApplication app(argc, argv);

  DPad d;

  d.show();
  d.pressButton(DPad::Button::LEFT);
  d.pressButton(DPad::Button::UP);

  QPushButton btnUp("up");
  btnUp.show();
  btnUp.move(200, 100);
  qApp->connect(&btnUp, &QPushButton::clicked, [&]() {d.setButtonState(DPad::Button::UP, !d.buttonState(DPad::Button::UP)); });

  QPushButton btnDown("down");
  btnDown.show();
  btnDown.move(200, 300);
  qApp->connect(&btnDown, &QPushButton::clicked, [&]() {d.setButtonState(DPad::Button::DOWN, !d.buttonState(DPad::Button::DOWN)); });

  QPushButton btnLeft("Left");
  btnLeft.show();
  btnLeft.move(100, 200);
  qApp->connect(&btnLeft, &QPushButton::clicked, [&]() {d.setButtonState(DPad::Button::LEFT, !d.buttonState(DPad::Button::LEFT)); });

  QPushButton btnRight("Right");
  btnRight.show();
  btnRight.move(300, 200);
  qApp->connect(&btnRight, &QPushButton::clicked, [&]() {d.setButtonState(DPad::Button::RIGHT, !d.buttonState(DPad::Button::RIGHT)); });

  return app.exec();
}