#ifndef IMAGEPROCESSING_H
#define IMAGEPROCESSING_H

#include <QtWidgets>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

#pragma execution_character_set("utf-8")
class ImageProcessing : public QWidget
{
    Q_OBJECT
    friend class MainWindow;
private:
    explicit ImageProcessing(QWidget *parent = 0);
    ~ImageProcessing();
    QImage origImg;
    QImage procImg;

    QWidget *firstSlider;
    QWidget *secondSlider;

    QLabel *originLabel;
    QLabel *binaryLabel;
    QLabel *imageLabel1;
    QLabel *imageLabel2;

    QLabel *thresLbl;
    QLabel *min_ThresLbl;
    QLabel *max_ThresLbl;
    QSpinBox *thresSpBx;

    QLabel *maxValLbl;
    QLabel *min_MaxValLbl;
    QLabel *max_MaxValLbl;
    QSpinBox *maxValSpBx;

    QSlider *thresSlider;
    QSlider *maxValSlider;

    QRadioButton *globalThres;
    QRadioButton *adaptiveThres;
    QRadioButton *smoothingFilter;

    QComboBox *filterCbBox;
    QComboBox *globCbBox;
    QComboBox *adapCbBox;

    QLabel *kernelLengthLbl;
    QComboBox *kernelLengthCmBx;

    QLabel *blockSizeLbl;
    QLabel *constLbl;
    QComboBox *blockSizeCbBx;
    QSpinBox *constSpBx;

    QGroupBox *globBox;
    QGroupBox *adaptBox;
    QGroupBox *filterBox;

    Mat originMat;
    Mat processedMat;

private slots:
    void globalThreshold();
    void adaptiveThreshold();
    void smoothFilters();
    void sliderChanged();
    void spinBoxChanged();
    void globalCurrent();
    void adaptiveCurrent();
    void FilterCurrent();

private:
    void createSlider(QSlider *&slider, QLabel *&min, QLabel *&max, QSpinBox *&spBox, QHBoxLayout *&layout, int val);
    void processing();
    void setProcessedImage();
};

#endif // IMAGEPROCESSING_H
