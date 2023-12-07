#include "../inc/Interface.hpp"

Window::Window()
{
    setGeometry(0, 0, 510, 260);

    setStyleSheet("* {color: white;} QMainWindow {background-color: #2E3440;} QPushButton {background-color: #3B4252;} QTextEdit {border: 1px solid; border-radius:5px; background-color: #4C566A;} QSpinBox {background-color: #4C566A;}");

    input = new QTextEdit(this);
    input->setGeometry(5, 5, 500, 95);
    input->setPlaceholderText("Input");

    output = new QTextEdit(this);
    output->setGeometry(5, 160, 500, 95);
    output->setPlaceholderText("Output");
    output->setReadOnly(true);

    initial_base = new QSpinBox(this);
    initial_base->setGeometry(443, 57, 60, 40);
    initial_base->setMinimum(2);
    initial_base->setMaximum(256);

    final_base = new QSpinBox(this);
    final_base->setGeometry(443, 213, 60, 40);
    final_base->setMinimum(2);
    final_base->setMaximum(256);

    button = new QPushButton(this);
    button->setText("Convert");
    button->setGeometry(5, 105, 500, 50);
    connect(button, &QPushButton::released, this, &Window::convert);

    createAndShowWindow();
};

void Window::convert()
{
    std::string s = input->toPlainText().toStdString();
    int i = s.find('.');
    try
    {
        if (i == -1)
        {
            output->setText(QString::fromStdString(BigInt(initial_base->value(), s).to_string(final_base->value())));
        }
        else
        {
            output->setText(QString::fromStdString(BigInt(initial_base->value(), s.substr(0, i)).to_string(final_base->value()) + '.' + BigInt(initial_base->value(), s.substr(i + 1, s.size() - i - 1)).to_string(final_base->value())));
        }
    }
    catch (const std::runtime_error &)
    {
        output->setText(QString::fromStdString("Error"));
    }
}

void Window::createAndShowWindow()
{
    create();
    setWindowTitle("UniversalConverter");
    show();
}