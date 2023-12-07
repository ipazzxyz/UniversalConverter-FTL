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
    QTextEdit *output;
    QPushButton *button;
    QSpinBox *final_base;
    QSpinBox *initial_base;

    void createAndShowWindow();
};