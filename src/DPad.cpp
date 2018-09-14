#include "DPad.h"

//defaults
const QColor DPad::DEFAULT_ARROW_COLOR = QColor(0, 0, 255);
const QColor DPad::DEFAULT_BACKGROUND_COLOR = QColor(109, 109, 109);

//private functions
void DPad::init(const QColor& arrowColor, const QColor& backgroundColor)
{
}

//event handlers
void DPad::paintEvent(QPaintEvent* e)
{
}

//constructors
DPad::DPad(QWidget* parent) :
  QWidget(parent)
{
}
DPad::DPad(const QColor& arrowColor, const QColor& backgroundColor,
           QWidget* parent) :
  QWidget(parent)
{
}
DPad::~DPad()
{
}

//public functions

//getters
bool DPad::buttonState(Button button) const
{
}
QColor DPad::arrowColor() const
{
}
QColor DPad::backgroundColor() const
{
}
QColor DPad::buttonOnColor() const
{
}
QColor DPad::buttonOffColor() const
{
}

//setters
void DPad::setButtonState(Button button, bool newState)
{
}
void DPad::setArrowColor(const QColor& color)
{
}
void DPad::setBackgroundColor(const QColor& color)
{
}
void DPad::setButtonOnColor(const QColor& color)
{
}
void DPad::setButtonOffColor(const QColor& color)
{
}

//public slots
void DPad::pressButton(Button button)
{
}
void DPad::releaseButton(Button button)
{
}
