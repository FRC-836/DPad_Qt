#ifndef D_PAD_REPRESENTATION_H
#define D_PAD_REPRESENTATION_H

#include <qwidget.h>
#include <qpainter.h>
#include <qbrush.h>
#include <qpen.h>
#include <qpainterpath.h>
#include <qevent.h>
#include <qcolor.h>

#include "Light.h"

class DPad : public QWidget
{
public:
  //enums and types
  enum class Button
  {
    UP,
    DOWN,
    LEFT,
    RIGHT
  };

private:
  //member data
  QMap<Button, Light*> m_buttons;
  QColor m_arrowColor;
  QColor m_backgroundColor;

  //defaults
  static const QColor DEFAULT_ARROW_COLOR;
  static const QColor DEFAULT_BACKGROUND_COLOR;

  //private functions
  void init(const QColor& arrowColor, const QColor& backgroundColor);

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