#include <QtWidgets>

#include <cmath>

#include "Button.h"
#include "Calculator.h"
#include "Settings.h"

Calculator::Calculator(QWidget *parent) {
    options = new Settings();
}

