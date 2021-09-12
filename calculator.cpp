#include "calculator.h"
#include "ui_calculator.h"

double currentValue = 0.0;

bool addPressed = false;
bool subPressed = false;
bool multPressed = false;
bool divPressed = false;

bool firstRound = true;
bool justCalculated = false;
bool mathButPressed = false;
bool firstDigit = true;

QString lastButValue = "XX";

bool equalsPressed = false;

Calculator::Calculator(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Calculator)
{
    ui->setupUi(this);

    ui->Display->setText(QString::number(currentValue));

    QPushButton *numButtons[10];
    for(int i =0; i< 10; i++)
    {
        QString buttonName = "Button" + QString::number(i);
        numButtons[i] = Calculator::findChild<QPushButton*>(buttonName);
        connect(numButtons[i], SIGNAL(released()), this, SLOT(numPressed()));
    }
    connect(ui->Button00, SIGNAL(released()), this, SLOT(numPressed()));
    connect(ui->ButtonDot, SIGNAL(released()), this, SLOT(numPressed()));

    connect(ui->ButtonErase, SIGNAL(released()), this, SLOT(eraseButtonPressed()));

    connect(ui->ButtonPlus, SIGNAL(released()), this, SLOT(mathButtonPressed()));
    connect(ui->ButtonDivide, SIGNAL(released()), this, SLOT(mathButtonPressed()));
    connect(ui->ButtonMinus, SIGNAL(released()), this, SLOT(mathButtonPressed()));
    connect(ui->ButtonMultiply, SIGNAL(released()), this, SLOT(mathButtonPressed()));
    connect(ui->ButtonEquals, SIGNAL(released()), this, SLOT(equalsButtonPressed()));
    connect(ui->ButtonClear, SIGNAL(released()), this, SLOT(clearButtonPressed()));
     connect(ui->ButtonSignChange, SIGNAL(released()), this, SLOT(signChangeButtonPressed()));
}

Calculator::~Calculator()
{
    delete ui;
}

void Calculator::numPressed()
{
    if(equalsPressed)
    {
        firstRound = true;
        firstDigit = true;
        currentValue = 0.0;
        equalsPressed = false;
    }

    if(firstDigit) ui->ExpressionDisplay->setText("");
    QPushButton *button = (QPushButton *)sender();
    QString butVal = button->text();
    QString displayVal = ui->Display->text();
    QString newVal = displayVal + butVal;

    if(justCalculated || firstDigit){
        ui->Display->setText(butVal);
        justCalculated = false;
        firstDigit = false;
    }
    else if(QString::compare(butVal, ".", Qt::CaseInsensitive) == 0)
    {
         ui->Display->setText(displayVal + butVal);
    }
    else ui->Display->setText(QString::number(newVal.toDouble(), 'g', 16));
}

void Calculator::mathButtonPressed()
{
    QString displayVal = ui->Display->text();

    if(mathButPressed){
        double result = calculate();
        ui->Display->setText(QString::number(result));
    }

    addPressed = false;
    subPressed = false;
    multPressed = false;
    divPressed = false;
    equalsPressed = false;

    QString displayValue = ui->Display->text();
    currentValue = displayValue.toDouble();

    QPushButton *button = (QPushButton *)sender();
    QString butVal = button->text();

    QString oldExpression = ui->ExpressionDisplay->text();
    QString newExpression;

    if(firstRound) newExpression = displayVal;
    else newExpression = oldExpression + lastButValue + displayVal;

    ui->ExpressionDisplay->setText(newExpression);
    if(QString::compare(butVal, "+", Qt::CaseInsensitive) == 0)
    {
        addPressed = true;
        lastButValue = "+";
    }
    else if(QString::compare(butVal, "-", Qt::CaseInsensitive) == 0)
    {
        subPressed = true;
        lastButValue = "-";
    }
    else if(QString::compare(butVal, "/", Qt::CaseInsensitive) == 0)
    {
        divPressed = true;
        lastButValue = "/";
    }
    else
    {
        multPressed = true;
        lastButValue = "*";
    }

    justCalculated = true;
    mathButPressed = true;
    firstRound = false;
}

void Calculator::equalsButtonPressed()
{
    if(QString::compare(lastButValue, "XX", Qt::CaseInsensitive) != 0){
    QString oldExpression = ui->ExpressionDisplay->text();
    QString newExpression = oldExpression + lastButValue + ui->Display->text();
    ui->ExpressionDisplay->setText(newExpression);

    mathButPressed = false;
    double result = calculate();
    ui->Display->setText(QString::number(result));

    equalsPressed = true;
    }
}

double Calculator::calculate()
{
    double result = 0.0;
    double displayVal = ui->Display->text().toDouble();
    if(addPressed || subPressed || multPressed || divPressed)
    {
        if(addPressed) result = currentValue + displayVal;
        else if(subPressed) result = currentValue - displayVal;
        else if(divPressed) result = currentValue / displayVal;
        else result = currentValue * displayVal;
    }
    return result;
}

void Calculator::clearButtonPressed()
{
    currentValue = 0.0;
    ui->Display->setText(QString::number(currentValue));
    ui->ExpressionDisplay->setText("");
    firstRound = true;
    firstDigit = true;
}

void Calculator::eraseButtonPressed()
{
    QString mainDisplay = ui->Display->text();
    mainDisplay.remove(mainDisplay.length()-1,mainDisplay.length());
    ui->Display->setText(mainDisplay);
}

void Calculator::signChangeButtonPressed()
{
    double value = ui->Display->text().toDouble();
    value = value * -1;
    ui->Display->setText(QString::number(value));
}
