#include "mainwindow.hpp"
#include <bigfraction.hpp>
#include <QFile>
#include <QFileDialog>
MainWindow::MainWindow()
{
    setGeometry(0, 0, 610, 260);

    setStyleSheet("* {color: white} QWidget {background-color: #2E3440} QPushButton {background-color: #3B4252} QTextEdit {border: 1px solid; border-radius:5px; background-color: #4C566A} QSpinBox {background-color: #4C566A}");

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
    button->setGeometry(5, 105, 600, 50);
    connect(button, &QPushButton::released, this, &MainWindow::convert);

    fromfile = new QPushButton(this);
    fromfile->setText("Import");
    fromfile->setGeometry(510, 5, 95, 95);
    connect(fromfile, &QPushButton::released, this, &MainWindow::importNumber);

    tofile = new QPushButton(this);
    tofile->setText("Export");
    tofile->setGeometry(510, 160, 95, 95);
    connect(tofile, &QPushButton::released, this, &MainWindow::exportNumber);

    setup();
};

void MainWindow::convert()
{
    std::string s = input->toPlainText().toStdString();
    int i = s.find('.');
    try
    {
        if (i == -1)
        {
            output->setText(QString::fromStdString(BigInt(initial_base->value(), s).toString(final_base->value())));
        }
        else
        {
            std::string fr(BigFraction(initial_base->value(), s.substr(i + 1, s.size() - i - 1)).toString(final_base->value()));
            BigInt z(initial_base->value(), s.substr(0, i));
            if (fr == "+")
            {
                ++z;
                output->setText(QString::fromStdString(z.toString(final_base->value())));
            }
            else
            {
                output->setText(QString::fromStdString(z.toString(final_base->value()) + '.' + fr));
            }
        }
    }
    catch (const std::runtime_error &)
    {
        output->setText(QString::fromStdString("Error"));
    }
}

void MainWindow::setup()
{
    create();
    setWindowTitle("UniversalConverter");
    show();
}
void MainWindow::importNumber()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open file"), "", tr("all Files ()"));
    QFile file(fileName);
    if (file.open(QIODevice::ReadOnly))
    {
        input->setText(QString(file.readAll()));
        file.close();
    }
}
void MainWindow::exportNumber()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open file"), "", tr("all Files ()"));
    QFile file(fileName);
    if (file.open(QIODevice::WriteOnly))
    {
        file.write(output->toPlainText().toUtf8());
        file.close();
    }
}