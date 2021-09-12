#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class Calculator; }
using namespace std;
QT_END_NAMESPACE

class Calculator : public QMainWindow
{
    Q_OBJECT

public:
    Calculator(QWidget *parent = nullptr);
    ~Calculator();

private:
    Ui::Calculator *ui;
    bool isNumber(const string str);

private slots:
    void numPressed();
    void mathButtonPressed();
    void equalsButtonPressed();
    void eraseButtonPressed();
    void clearButtonPressed();
    double calculate();
};
#endif // CALCULATOR_H
