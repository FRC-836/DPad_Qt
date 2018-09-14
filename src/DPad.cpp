#include "DPad.h"

//defaults
const QColor DPad::DEFAULT_ARROW_COLOR = QColor(0, 0, 255);
const QColor DPad::DEFAULT_BACKGROUND_COLOR = QColor(109, 109, 109);

//private functions
void DPad::init(const QColor& arrowColor, const QColor& backgroundColor)
{
  //create down light
  Light* downLight = new Light(this);
}

//event handlers
void DPad::paintEvent(QPaintEvent* e)
{
}

//constructors
DPad::DPad(QWidget* parent) :
  QWidget(parent)
{
  init(DEFAULT_ARROW_COLOR, DEFAULT_BACKGROUND_COLOR);
}
DPad::DPad(const QColor& arrowColor, const QColor& backgroundColor,
           QWidget* parent) :
  QWidget(parent)
{
  init(arrowColor, backgroundColor);
}
DPad::~DPad()
{
}

//public functions

//getters
bool DPad::buttonState(Button button) const
{
  return m_buttons[button]->on();
}
QColor DPad::arrowColor() const
{
  return m_arrowColor;
}
QColor DPad::backgroundColor() const
{
  return m_backgroundColor;
}
QColor DPad::buttonOnColor() const
{
  return m_buttons[Button::DOWN]->onColor();
}
QColor DPad::buttonOffColor() const
{
  return m_buttons[Button::DOWN]->offColor();
}

//setters
void DPad::setButtonState(Button button, bool newState)
{
  if (newState)
  {
    m_buttons[button]->turnOn();
    emit buttonPressed(button);
  } //end  if (newState)
  else
  {
    m_buttons[button]->turnOff();
    emit buttonReleased(button);
  } //end  else

  emit buttonStateChanged(button, newState);
}
void DPad::setArrowColor(const QColor& color)
{
  m_arrowColor = color;
}
void DPad::setBackgroundColor(const QColor& color)
{
  m_backgroundColor = color;
}
void DPad::setButtonOnColor(const QColor& color)
{
  for (auto button : m_buttons)
  {
    button->setOnColor(color);
  } //end  for (auto button : m_buttons)
}
void DPad::setButtonOffColor(const QColor& color)
{
  for (auto button : m_buttons)
  {
    button->setOffColor(color);
  } //end  for (auto button : m_buttons)
}

//public slots
void DPad::pressButton(Button button)
{
  setButtonState(button, true);
}
void DPad::releaseButton(Button button)
{
  setButtonState(button, false);
}
