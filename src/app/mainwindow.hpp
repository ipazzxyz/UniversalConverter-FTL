#pragma once
#include <QMainWindow>
#include <QTextEdit>
#include <QPushButton>
#include <QSpinBox>
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();

private slots:
    void convert();
    void importNumber();
    void exportNumber();

private:
    QTextEdit *input;
    QTextEdit *output;
    QPushButton *button;
    QPushButton *fromfile;
    QPushButton *tofile;
    QSpinBox *final_base;
    QSpinBox *initial_base;

    void setup();
};
