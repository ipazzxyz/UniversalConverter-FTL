#include "../inc/Interface.hpp"

Window::Window()
{
    setGeometry(0, 0, 275, 150);
    input = new QTextEdit(this);
    input->setGeometry(0, 0, 200, 50);

    initial_base = new QSpinBox(this);
    initial_base->setGeometry(200, 0, 75, 50);
    initial_base->setMinimum(2);
    initial_base->setMaximum(256);

    final_base = new QSpinBox(this);
    final_base->setGeometry(200, 100, 75, 50);
    final_base->setMinimum(2);
    final_base->setMaximum(256);

    button = new QPushButton(this);
    button->setText("Convert");
    button->setGeometry(0, 50, 275, 50);
    connect(button, &QPushButton::released, this, &Window::convert);

    output = new QTextEdit(this);
    output->setGeometry(0, 100, 200, 50);
    output->setPlaceholderText("Output");
    output->setReadOnly(true);
    this->create();
    this->setWindowTitle("UniversalConverter");
    this->show();
};

void Window::convert()
{
    output->setText(QString::fromStdString(BigInt(initial_base->value(), input->toPlainText().toStdString()).to_string(final_base->value())));
}