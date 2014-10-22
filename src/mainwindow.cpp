#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <qfiledialog.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void
MainWindow::on_pushButton_clicked()
{
	ui->widget->setImage(cv::imread(QFileDialog::getOpenFileName(this, "Select file").toStdString()));
}