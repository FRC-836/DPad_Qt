#ifndef D_PAD_REPRESENTATION_H
#define D_PAD_REPRESENTATION_H

#include <qwidget.h>
#include <qpainter.h>
#include <qbrush.h>
#include <qpen.h>
#include <qpainterpath.h>
#include <qevent.h>
#include <qcolor.h>

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
  QMap<Button, bool> m_buttonStates;
  QColor m_arrowColor;
  QColor m_buttonColor;
  QColor m_backgroundColor;

  //defaults
  static const QColor DEFAULT_ARROW_COLOR;
  static const QColor DEFAULT_BUTTON_COLOR;
  static const QColor DEFAULT_BACKGROUND_COLOR;

  //private functions
  void init(const QMap<Button, bool>& buttonStates, const QColor& arrowColor, 
            const QColor& buttonColor, const QColor& backgroundColor);

protected:
  //event handlers
  void paintEvent(QPaintEvent* e);

public:
  //constructors
  DPad(QWidget* parent = nullptr);
  DPad(const QMap<Button, bool>& m_buttonStates, 
       const QColor& arrowColor = DEFAULT_ARROW_COLOR, 
       const QColor& buttonColor = DEFAULT_BUTTON_COLOR, 
       const QColor& backgroundColor = DEFAULT_BACKGROUND_COLOR, 
       QWidget* parent = nullptr);
  DPad(const QColor& arrowColor, const QColor& buttonColor = DEFAULT_BUTTON_COLOR,
       const QColor& backgroundColor = DEFAULT_BACKGROUND_COLOR, QWidget* parent = nullptr);
  ~DPad();

  //public functions

  //getters
  bool buttonState(Button toGrab) const;
  QMap<Button, bool> buttonStates() const;
  QColor arrowColor() const;
  QColor buttonColor() const;
  QColor backgroundColor() const;

  //setters
  void setButtonState(Button toSet, bool state);
  void setButtonStates(const QMap<Button, bool>& states);
  void setArrowColor(const QColor& color);
  void setArrowColor(int r, int g, int b);
  void setBackgroundColor(const QColor& color);
  void setArrowColor(int r, int g, int b);

signals:
  void buttonStateChanged(Button changed, bool newState);
  //signals

public slots:
  //public slots

};

#endif