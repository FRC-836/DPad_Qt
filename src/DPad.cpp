#include "DPad.h"

//defaults
const QColor DPad::DEFAULT_ARROW_COLOR = QColor(0, 0, 255);
const QColor DPad::DEFAULT_BACKGROUND_COLOR = QColor(109, 109, 109);
const double DPad::ARROW_HEIGHT_SCALE = 0.1;
const double DPad::ARROW_BAR_HEIGHT_SCALE = 0.25;
const double DPad::ARROW_HEAD_SCALE = 0.1;
const double DPad::CIRCLE_SCALE = 0.1;
const QMap<DPad::Button, double> DPad::BUTTON_ROTATION_MAP = {
  {Button::DOWN, 270},
  {Button::LEFT, 180},
  {Button::RIGHT, 0},
  {Button::UP, 90}
};

//private functions
void DPad::init(const QColor& arrowColor, const QColor& backgroundColor)
{
  //setup UI
  m_ui = new Ui_DPad();
  m_ui->setupUi(this);

  //set member variables
  setArrowColor(arrowColor);
  setBackgroundColor(backgroundColor);

  //setup button map
  m_buttons[Button::DOWN] = m_ui->lightBottom;
  m_buttons[Button::UP] = m_ui->lightTop;
  m_buttons[Button::LEFT] = m_ui->lightLeft;
  m_buttons[Button::RIGHT] = m_ui->lightRight;
}
bool DPad::allOff()
{
  for (auto light : m_buttons)
  {
    if (light->on())
    {
      return false;
    } //end  if (!light->on())
  } //end  for (auto light : m_buttons)
  return true;
}

//event handlers
void DPad::paintEvent(QPaintEvent* e)
{
  //calculate points for the polygon of the background cross
  auto xOne = width() / 3;
  auto xTwo = 2 * width() / 3;
  auto yOne = height() / 3;
  auto yTwo = 2 * height() / 3;

  //create the cross
  QPainterPath background;
  background.moveTo(xOne, 0);
  background.lineTo(xTwo, 0);
  background.lineTo(xTwo, yOne);
  background.lineTo(width(), yOne);
  background.lineTo(width(), yTwo);
  background.lineTo(xTwo, yTwo);
  background.lineTo(xTwo, height());
  background.lineTo(xOne, height());
  background.lineTo(xOne, yTwo);
  background.lineTo(0, yTwo);
  background.lineTo(0, yOne);
  background.lineTo(xOne, yOne);
  background.closeSubpath();

  //create arrow
  QPainterPath arrow;
  int rotation = 0; //angle to rotate the arrow
  QPoint translation; //different depending on a button is pressed or not
  if (allOff())
  {
    auto circleWidth = (xTwo - xOne) * CIRCLE_SCALE;
    auto circleHeight = (yTwo - yOne) * CIRCLE_SCALE;
    auto circleX = (width() / 2) - (circleWidth / 2);
    auto circleY = (height() / 2) - (circleHeight / 2);
    arrow.addEllipse(circleX, circleY, circleWidth, circleHeight);
    translation.setX(0);
    translation.setY(0);
  } //end  if (allOff())
  else
  {
    //if at least one button is on, draw the arrow
    auto halfHeight = height() / 2;
    auto halfWidth = width() / 2;
    auto arrowHeight = height() * ARROW_HEIGHT_SCALE;
    auto barHeight = arrowHeight * ARROW_BAR_HEIGHT_SCALE;
    auto arrowWidth = (xTwo - xOne) * ARROW_HEAD_SCALE;
    auto barWidth = (xTwo - xOne) - arrowWidth;
    auto barY = halfHeight - (barHeight / 2);
    arrow.addRect(xOne - halfWidth, barY - halfHeight, barWidth, barHeight);
    arrow.moveTo(xOne + barWidth - halfWidth, 0);
    arrow.lineTo(xOne + barWidth - halfWidth, arrowHeight / 2);
    arrow.lineTo(xTwo - halfWidth, 0);
    arrow.lineTo(xOne + barWidth - halfWidth, -(arrowHeight / 2));
    arrow.closeSubpath();

    //calculate angle to rotate
    int numOn = 0;
    for (auto button : BUTTON_ROTATION_MAP.toStdMap())
    {
      if (m_buttons[button.first]->on())
      {
        rotation += button.second;
        numOn++;
      } //end  if (m_buttons[button.first]->on())
    } //end  for (auto button : BUTTON_ROTATION_MAP.toStdMap())
    rotation /= numOn;

    //set translation to make the points centered on the center of the widget
    translation.setX(halfWidth);
    translation.setY(halfHeight);
  } //end  else


  //create painter and painting equipment
  QPainter painter(this);
  QBrush brush(m_backgroundColor);
  QPen pen(m_backgroundColor);

  //paint background
  painter.setBrush(brush);
  painter.setPen(pen);
  painter.drawPath(background);

  //paint arrow
  brush.setColor(m_arrowColor);
  pen.setColor(m_arrowColor);
  painter.setBrush(brush);
  painter.setPen(pen);
  painter.translate(translation);
  painter.rotate(-rotation);
  painter.drawPath(arrow);
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
  delete m_ui;
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

  repaint();
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
