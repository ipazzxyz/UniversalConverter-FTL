#pragma once

#include "BigInt.hpp"

#include <QMainWindow>
#include <QTextEdit>
#include <QPushButton>
#include <QSpinBox>

class Window : public QMainWindow
{
    Q_OBJECT

public:
    Window();

private slots:
    void convert();

private:
    QTextEdit *input;
    QSpinBox *initial_base;
    QPushButton *button;
    QTextEdit *output;
    QSpinBox *final_base;
};