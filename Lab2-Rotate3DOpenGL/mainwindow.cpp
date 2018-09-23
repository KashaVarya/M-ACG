#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "my_paint.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QPixmap myPixmap( ":/vk.jpg" );
    ui->label_image->setPixmap(myPixmap);
    ui->label_image->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    My_Paint *opengl_window = new My_Paint;
    opengl_window->show();
}
