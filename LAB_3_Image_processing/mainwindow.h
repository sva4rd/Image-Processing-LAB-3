#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "imageprocessing.h"
#include <QtWidgets/QMainWindow>

using namespace cv;

class MainWindow : public QMainWindow
{
    Q_OBJECT
    friend class ImageProcessing;
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    QString openPath;
    QString saveDirPath;
    QImage originImg;
    QImage binaryImg;
    ImageProcessing *imgProc;

    QToolBar *fileTool;
    QString fileName;
    Mat originImage;
    Mat binaryImage;

    void createAction();
    void read(QString fileName, bool qrc);

private slots :
    void SaveFile();
    void OpenFile();
};


#endif // MAINWINDOW_H
