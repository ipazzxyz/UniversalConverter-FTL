#pragma once
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
    void import_num();
    void export_num();

private:
    QTextEdit *input;
    QTextEdit *output;
    QPushButton *button;
    QPushButton *fromfile;
    QPushButton *tofile;
    QSpinBox *final_base;
    QSpinBox *initial_base;

    void createAndShowWindow();
};
