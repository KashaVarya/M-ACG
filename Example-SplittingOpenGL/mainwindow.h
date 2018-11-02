#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets/QMainWindow>
#include <qgridlayout.h>
#include <objectgl.h>
#include <QMenuBar>
#include <QMessageBox>
#include <QTimer>

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    // Конструктор і деструктор
    MainWindow(QWidget *parent = nullptr, int w=600, int h=400);
    ~MainWindow();

protected slots:
    // Оновлення сцени
    void onTimer_UpdateDisplay();

    // Відкрийте діалогове вікно “about”
    void handleAbout();
protected:
    void resizeEvent(QResizeEvent *);
private:
    // Макет вікна
    QGridLayout *gridLayout;
    QWidget *gridLayoutWidget;
    // Центральний віджет (де намальовано вікно openGL)
    QWidget *centralWidget;
    // OpenGL object
    ObjectOpenGL *Object_GL;
};
#endif // MAINWINDOW_H
