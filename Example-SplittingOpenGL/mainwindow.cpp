#include "mainwindow.h"
#include "objectgl.h"
#include <QApplication>

//Конструктор головного вікна
//Створіть властивості вікна,  меню тощо ...
MainWindow::MainWindow(QWidget *parent, int w, int h)
    :QMainWindow(parent)
{
    //Встановіть розміри вікна
    this->resize(w,h);
    this->setWindowTitle("Object viewer");

    //Створіть макет у головному вікні
    centralWidget = new QWidget (this);
    gridLayoutWidget = new QWidget (centralWidget);
    gridLayoutWidget->setGeometry(QRect(0,0,this->width(), this->height()));
    gridLayout = new QGridLayout(gridLayoutWidget);

    //Створіть екран openGL для карти
    Object_GL = new ObjectOpenGL(gridLayoutWidget);
    Object_GL -> setObjectName(QString::fromUtf8("ObjectOpenGL"));
    Object_GL -> setGeometry(QRect(0,0, this->width(), this->height()));

    // Вставте відображення openGL в макет
    gridLayout->addWidget(Object_GL,0,0,1,1);
    setCentralWidget(centralWidget);

    //Створіть панель меню
    QMenu *FileMenu = menuBar()->addMenu("&File");
    FileMenu->addSeparator();
    FileMenu->addAction("Quit",qApp, SLOT(quit()),QKeySequence(tr("Ctrl+Q")));

    //Додати елементи меню
    QMenu *ViewMenu = menuBar()->addMenu("&View");
    ViewMenu->addSeparator();
    ViewMenu->addAction("Front", Object_GL, SLOT(FrontView()), QKeySequence(tr("Ctrl+f")));
    ViewMenu->addAction("Rear", Object_GL, SLOT(RearView()), QKeySequence(tr("Ctrl+e")));
    ViewMenu->addAction("Left", Object_GL, SLOT(LeftView()), QKeySequence(tr("Ctrl+l")));
    ViewMenu->addAction("Right", Object_GL, SLOT(RightView()), QKeySequence(tr("Ctrl+r")));
    ViewMenu->addAction("Top", Object_GL, SLOT(TopView()), QKeySequence(tr("Ctrl+t")));
    ViewMenu->addAction("Bottom ", Object_GL, SLOT(BottomView()), QKeySequence(tr("Ctrl+b")));
    ViewMenu->addSeparator();
    ViewMenu->addAction("Isometric", Object_GL, SLOT(IsometricView()), QKeySequence(tr("Ctrl+i")));
    QMenu *AboutMenu=menuBar()->addMenu("?");
    AboutMenu->addAction("About Program",this,SLOT(handleAbout()));

//Таймер (використовується для перемальовування вікон GL  кожні 25 мсек)
    QTimer *timer=new QTimer();
    timer->connect(timer,SIGNAL(timeout()),this,SLOT(onTimer_UpdateDisplay()));
    timer->start(25);
}

// Деструктор
MainWindow::~MainWindow()
{}

// У разі виклику події зміни розміру, розміри об'єктів у вікні змінюються
void MainWindow::resizeEvent(QResizeEvent *)
{
    Object_GL->resize(centralWidget->width(),centralWidget->height());
    gridLayoutWidget->setGeometry(QRect(0, 0, centralWidget->width(), centralWidget->height()));
}

// Подія таймера: перефарбувати вікно Opengl
void MainWindow::onTimer_UpdateDisplay()
{
    Object_GL->updateGL();
}

// Відкрийте діалогове вікно "about"
void MainWindow::handleAbout()
{
    QMessageBox::information(this,"About OpenGL Frame","<H2>OpenGL Frame</H2>2018<BR>Supported by My Mum<BR>ZNTU (Zaporizhzhia,Ukraine)<BR>Designed by Varvara Khokhlova <BR> Contact: varyaxx@gmail.com");
}
