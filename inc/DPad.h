#ifndef D_PAD_REPRESENTATION_H
#define D_PAD_REPRESENTATION_H

#include <cmath>

#include <qwidget.h>
#include <qpainter.h>
#include <qbrush.h>
#include <qpen.h>
#include <qpainterpath.h>
#include <qevent.h>
#include <qcolor.h>
#ifdef INCLUDE_DPAD_GENERATED
#include "ui_DPad.h"
#else
class Ui_DPad;
class Light;
#endif

class DPad : public QWidget
{
  Q_OBJECT

public:
  //enums and types
  enum class Button
  {
    UP,
    DOWN,
    LEFT,
    RIGHT,
  };

private:
  //member data
  Ui_DPad* m_ui;
  QColor m_arrowColor;
  QColor m_backgroundColor;
  QMap<Button, Light*> m_buttons;

  //defaults
  static const QColor DEFAULT_ARROW_COLOR;
  static const QColor DEFAULT_BACKGROUND_COLOR;
  static const double ARROW_HEIGHT_SCALE; //multiplier for height of the arrow based on widget height
  static const double ARROW_BAR_HEIGHT_SCALE; //multipler for height of bar based on arrow height
  static const double ARROW_HEAD_SCALE; //multipler for width of the arrow head based on arrow bar width
  static const double CIRCLE_SCALE; //multiplier for size of the circle based on size of box between button circles
  static const QMap<Button, QPoint> BUTTON_ROTATION_MAP; //how far the arrow needs to rotate if a certain button is pressed

  //private functions
  void init(const QColor& arrowColor, const QColor& backgroundColor);
  bool allOff();
  bool allOn();

protected:
  //event handlers
  void paintEvent(QPaintEvent* e) override;

public:
  //constructors
  DPad(QWidget* parent = nullptr);
  DPad(const QColor& arrowColor, const QColor& backgroundColor = DEFAULT_BACKGROUND_COLOR, 
       QWidget* parent = nullptr);
  ~DPad();

  //public functions

  //getters
  bool buttonState(Button button) const;
  QColor arrowColor() const;
  QColor backgroundColor() const;
  QColor buttonOnColor() const;
  QColor buttonOffColor() const;

  //setters
  void setButtonState(Button button, bool newState);
  void setArrowColor(const QColor& color);
  void setBackgroundColor(const QColor& color);
  void setButtonOnColor(const QColor& color);
  void setButtonOffColor(const QColor& color);

signals:
  //signals
  void buttonStateChanged(Button button, bool newState);
  void buttonPressed(Button button);
  void buttonReleased(Button button);

public slots:
  //public slots
  void pressButton(Button button);
  void releaseButton(Button button);

};

#endif
