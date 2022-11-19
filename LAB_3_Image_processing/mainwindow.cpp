#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent)
{
    qApp->setStyle(QStyleFactory::create("Fusion"));
    setWindowTitle ("Image Processing");
    createAction();
    openPath = "D:/";
    saveDirPath = "D:/";

    imgProc = new ImageProcessing(this);
    read(":/testImg.jpg", true);
    setCentralWidget (imgProc);
}

MainWindow::~MainWindow(){}


void MainWindow::createAction()
{
    QAction * openFileAction = new QAction (QIcon (":/open.png"), "Open file", this);
    openFileAction->setShortcut(QKeySequence("Ctrl+O"));

    QAction * saveFileAction = new QAction (QIcon (":/save.png"), "Save file", this);
    saveFileAction->setShortcut(QKeySequence("Ctrl+S"));

    fileTool = addToolBar ("File");
    fileTool->addAction(openFileAction);
    fileTool->addAction(saveFileAction);

    fileTool-> setAllowedAreas (Qt :: TopToolBarArea | Qt :: LeftToolBarArea);
    fileTool->setMovable(false);

    connect(openFileAction, SIGNAL(triggered()), this, SLOT(OpenFile()));
    connect(saveFileAction, SIGNAL(triggered()), this, SLOT(SaveFile()));
}

void MainWindow::read(QString fileName, bool qrc)
{
    if (qrc)
    {
        QFile file(fileName);
        file.open(QIODevice::ReadOnly);
        qint64 sz = file.size();
        std::vector<uchar> buf(sz);
        file.read((char*)buf.data(), sz);

        originImage = imdecode(buf, COLOR_RGB2GRAY);
    }
    else
    {
        string trans = fileName.toLocal8Bit().toStdString();
        const char *FileName = trans.c_str();

        originImage = imread(FileName);
    }

    if (originImage.channels()== 3)
        cvtColor(originImage, originImage, COLOR_RGB2GRAY);

    if (originImage.depth()!=CV_8U)
    {
        QMessageBox::warning(this, "Warning", "The image is not an 8-bit image");
        return;
    }

    QImage originImg = QImage((const unsigned char*)(originImage.data),
                              originImage.cols, originImage.rows, originImage.step, QImage::Format_Grayscale8);

    imgProc->imageLabel1->setPixmap(QPixmap::fromImage(originImg));
    imgProc->originMat = originImage;
    imgProc->processing();
}


void MainWindow::OpenFile()
{
    fileName = QFileDialog::getOpenFileName(this, "Open File", openPath, "Image Files(*.tif *.jpg *.bmp *jpeg *gif *png)");
    if (!fileName.isEmpty())
    {
        QFileInfo fileInfo(fileName);
        openPath = fileInfo.path();
        read(fileName, false);
    }
}

void MainWindow::SaveFile()
{
    QString savePath = QFileDialog::getSaveFileName(this, "Save File", saveDirPath,
                                                    "Image Files(*.tif *.jpg *.bmp *jpeg *gif *png)");
    if (savePath.isEmpty())
        return;

    QFileInfo fileInfo(fileName);
    saveDirPath = fileInfo.path();

    string trans = savePath.toLocal8Bit().toStdString();
    const char *path = trans.c_str();

    imwrite(path, this->binaryImage);
}
