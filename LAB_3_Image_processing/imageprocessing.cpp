#include "imageprocessing.h"

ImageProcessing::ImageProcessing(QWidget *parent) :QWidget(parent)
{
    firstSlider = new QWidget;
    secondSlider = new QWidget;

    QFont font;
    font.setBold(true);

    originLabel = new QLabel;
    originLabel->setText ("Original Image");
    originLabel->setAlignment(Qt::AlignCenter);
    originLabel->setFont(font);

    binaryLabel = new QLabel;
    binaryLabel->setText ("Processed Image");
    binaryLabel->setAlignment(Qt::AlignCenter);
    binaryLabel->setFont(font);

    imageLabel1 = new QLabel;
    imageLabel1-> setScaledContents (true);

    imageLabel2 = new QLabel;
    imageLabel2->setScaledContents(true);

    imageLabel1->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    imageLabel2->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    imageLabel1->setMinimumSize(200, 200);
    imageLabel1->setMaximumSize(500, 500);
    imageLabel2->setMinimumSize(200, 200);
    imageLabel2->setMaximumSize(500, 500);

    thresLbl = new QLabel;
    thresLbl->setText("Threshold: ");
    thresLbl->setFont(font);

    maxValLbl = new QLabel;
    maxValLbl->setText("Max Value:");
    maxValLbl->setFont(font);


    QHBoxLayout *slider1 = new QHBoxLayout(firstSlider);
    QHBoxLayout *slider2 = new QHBoxLayout(secondSlider);

    createSlider(thresSlider, min_ThresLbl, max_ThresLbl, thresSpBx, slider1, 127);
    createSlider(maxValSlider, min_MaxValLbl, max_MaxValLbl, maxValSpBx, slider2, 255);

    QVBoxLayout *originLayout = new QVBoxLayout();
    originLayout->addWidget(originLabel);
    originLayout->addWidget(imageLabel1);

    QVBoxLayout *binaryLayout = new QVBoxLayout();
    binaryLayout->addWidget(binaryLabel);
    binaryLayout->addWidget(imageLabel2);

    QVBoxLayout *sliders = new QVBoxLayout();
    sliders->addWidget(firstSlider);
    sliders->addWidget(secondSlider);

    QVBoxLayout *sliderLabels = new QVBoxLayout();
    sliderLabels->addWidget(thresLbl);
    sliderLabels->addWidget(maxValLbl);

    QHBoxLayout *globalSliders = new QHBoxLayout();
    globalSliders->addLayout(sliderLabels);
    globalSliders->addLayout(sliders);

    QGridLayout *imgProcLay = new QGridLayout();
    imgProcLay->addLayout(originLayout, 0,0);
    imgProcLay->addLayout(binaryLayout, 0,1);
    imgProcLay->addLayout(globalSliders, 1, 0, 1, 2);




    globalThres = new QRadioButton("Global Thresholds");
    globalThres->setFont(font);
    adaptiveThres = new QRadioButton("Adaptive Thresholds");
    adaptiveThres->setFont(font);
    smoothingFilter = new QRadioButton("Smoothing Filter");
    smoothingFilter->setFont(font);

    filterCbBox = new QComboBox;
    filterCbBox->addItem("Normalized Box Filter");
    filterCbBox->addItem("Gaussian Filter");
    //filterCbBox->addItem("Median Filter");
    filterCbBox->setFont(font);

    globCbBox = new QComboBox;
    globCbBox->addItem("THRESH_BINARY");
    globCbBox->addItem("THRESH_BINARY_INV");
    globCbBox->addItem("THRESH_TRUNC");
    globCbBox->addItem("THRESH_TOZERO");
    globCbBox->addItem("THRESH_TOZERO_INV");
    globCbBox->addItem("THRESH_OTSU");
    globCbBox->addItem("THRESH_TRIANGLE");
    globCbBox->setFont(font);

    adapCbBox = new QComboBox;
    adapCbBox->addItem("THRESH_MEAN_C");
    adapCbBox->addItem("THRESH_GAUSSIAN_C");
    adapCbBox->setFont(font);

    blockSizeLbl = new QLabel;
    blockSizeLbl->setText("Block Size:");
    blockSizeLbl->setFont(font);

    constLbl = new QLabel;
    constLbl->setText("Constant:");
    constLbl->setFont(font);

    QStringList blockSizes;
    blockSizes << "3" << "5" << "7" << "9" << "11" << "13" << "15" << "17" << "19" << "21"
               << "23" << "25" << "27" << "29";
    blockSizeCbBx = new QComboBox;
    blockSizeCbBx->addItems(blockSizes);

    constSpBx = new QSpinBox;
    constSpBx->setRange(-100, 100);

    QStringList kernels;
    kernels << "1" << "3" << "5" << "7" << "9" << "11" << "13" << "15" << "17" << "19" << "21"
            << "23" << "25" << "27" << "29";
    kernelLengthLbl = new QLabel;
    kernelLengthLbl->setText("Kernel Length:");
    kernelLengthLbl->setFont(font);
    kernelLengthCmBx = new QComboBox();
    kernelLengthCmBx->addItems(kernels);

    globBox = new QGroupBox;
    adaptBox = new QGroupBox;
    filterBox = new QGroupBox;

    QVBoxLayout *globParam = new QVBoxLayout;
    globParam->addWidget(globCbBox);
    globBox->setLayout(globParam);

    QGridLayout *adaptParam = new QGridLayout;
    adaptParam->addWidget(adapCbBox, 0, 0, 1, 2);
    adaptParam->addWidget(blockSizeLbl, 1, 0);
    adaptParam->addWidget(blockSizeCbBx, 1, 1);
    adaptParam->addWidget(constLbl, 2, 0);
    adaptParam->addWidget(constSpBx, 2, 1);
    adaptBox->setLayout(adaptParam);

    QGridLayout *filterParam = new QGridLayout;
    filterParam->addWidget(filterCbBox, 0, 0, 1, 2);
    filterParam->addWidget(kernelLengthLbl, 1, 0);
    filterParam->addWidget(kernelLengthCmBx, 1, 1);
    filterBox->setLayout(filterParam);

    QVBoxLayout *methodsLayout = new QVBoxLayout();
    methodsLayout->addWidget(globalThres);
    methodsLayout->addWidget(globBox);
    methodsLayout->addWidget(adaptiveThres);
    methodsLayout->addWidget(adaptBox);
    methodsLayout->addWidget(smoothingFilter);
    methodsLayout->addWidget(filterBox);
    methodsLayout->addStretch(1);


    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    mainLayout->addLayout(methodsLayout);
    mainLayout->addLayout(imgProcLay);

    connect(globalThres, &QRadioButton::clicked, this, &ImageProcessing::globalCurrent);
    connect(adaptiveThres, &QRadioButton::clicked, this, &ImageProcessing::adaptiveCurrent);
    connect(smoothingFilter, &QRadioButton::clicked, this, &ImageProcessing::FilterCurrent);

    connect(globCbBox, &QComboBox::currentTextChanged, this, &ImageProcessing::globalThreshold);
    connect(adapCbBox, &QComboBox::currentTextChanged, this, &ImageProcessing::adaptiveThreshold);
    connect(filterCbBox, &QComboBox::currentTextChanged, this, &ImageProcessing::smoothFilters);

    connect(blockSizeCbBx, &QComboBox::currentTextChanged, this, &ImageProcessing::adaptiveThreshold);
    connect(constSpBx, &QSpinBox::textChanged, this, &ImageProcessing::adaptiveThreshold);

    connect(kernelLengthCmBx, &QComboBox::currentTextChanged, this, &ImageProcessing::smoothFilters);

    connect(thresSlider, &QSlider::valueChanged, this, &ImageProcessing::sliderChanged);
    connect(maxValSlider, &QSlider::valueChanged, this, &ImageProcessing::sliderChanged);

    connect(thresSpBx, &QSpinBox::textChanged, this, &ImageProcessing::spinBoxChanged);
    connect(maxValSpBx, &QSpinBox::textChanged, this, &ImageProcessing::spinBoxChanged);

    globalThres->setChecked(true);
    emit globalThres->clicked();
}

ImageProcessing::~ImageProcessing(){}

void ImageProcessing::globalThreshold()
{
    if (globCbBox->currentText() == "THRESH_TRUNC" || globCbBox->currentText() == "THRESH_TOZERO"
            || globCbBox->currentText() == "THRESH_TOZERO_INV")
    {
        firstSlider->setEnabled(true);
        secondSlider->setEnabled(false);
    }
    else if (globCbBox->currentText() == "THRESH_TRIANGLE")
    {
        firstSlider->setEnabled(false);
        secondSlider->setEnabled(true);
    }
    else if (globCbBox->currentText() == "THRESH_OTSU")
    {
        firstSlider->setEnabled(false);
        secondSlider->setEnabled(false);
    }
    else
    {
        firstSlider->setEnabled(true);
        secondSlider->setEnabled(true);
    }



    if (globCbBox->currentText() == "THRESH_BINARY")
        threshold(originMat, processedMat, thresSlider->value(), maxValSlider->value(), THRESH_BINARY);
    else if (globCbBox->currentText() == "THRESH_BINARY_INV")
        threshold(originMat, processedMat, thresSlider->value(), maxValSlider->value(), THRESH_BINARY_INV);
    else if (globCbBox->currentText() == "THRESH_TRUNC")
        threshold(originMat, processedMat, thresSlider->value(), maxValSlider->value(), THRESH_TRUNC);
    else if (globCbBox->currentText() == "THRESH_TOZERO")
        threshold(originMat, processedMat, thresSlider->value(), maxValSlider->value(), THRESH_TOZERO);
    else if (globCbBox->currentText() == "THRESH_TOZERO_INV")
        threshold(originMat, processedMat, thresSlider->value(), maxValSlider->value(), THRESH_TOZERO_INV);
    else if (globCbBox->currentText() == "THRESH_OTSU")
        threshold(originMat, processedMat, thresSlider->value(), maxValSlider->value(), THRESH_BINARY+THRESH_OTSU);
    else
        threshold(originMat, processedMat, thresSlider->value(), maxValSlider->value(), THRESH_BINARY+THRESH_TRIANGLE);
    setProcessedImage();
}

void ImageProcessing::adaptiveThreshold()
{
    firstSlider->setEnabled(false);
    secondSlider->setEnabled(true);

    if (adapCbBox->currentText() == "THRESH_GAUSSIAN_C")
        cv::adaptiveThreshold(originMat, processedMat, maxValSlider->value(), ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY,
                              blockSizeCbBx->currentText().toInt(), constSpBx->value());
    else
        cv::adaptiveThreshold(originMat, processedMat, maxValSlider->value(), ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY,
                              blockSizeCbBx->currentText().toInt(), constSpBx->value());
    setProcessedImage();
}

void ImageProcessing::smoothFilters()
{
    firstSlider->setEnabled(false);
    secondSlider->setEnabled(false);

    int kernel = kernelLengthCmBx->currentText().toInt();
    if (filterCbBox->currentText() == "Normalized Box Filter")
        blur(originMat, processedMat, Size(kernel, kernel), Point(-1, -1));
    else if (filterCbBox->currentText() == "Gaussian Filter")
        GaussianBlur(originMat, processedMat, Size(kernel, kernel), 0);
    //else
        //medianBlur(originMat, processedMat, kernel);
    setProcessedImage();
}

void ImageProcessing::sliderChanged()
{
    int thres = thresSlider->value();
    thresSpBx->setValue(thres);

    int maxVal = maxValSlider->value();
    maxValSpBx->setValue(maxVal);

    if (globBox->isVisible())
        globalThreshold();
    else
        adaptiveThreshold();
}

void ImageProcessing::spinBoxChanged()
{
    int thres = thresSpBx->value();
    thresSlider->setValue(thres);

    int maxVal = maxValSpBx->value();
    maxValSlider->setValue(maxVal);

    if (globBox->isVisible())
        globalThreshold();
    else
        adaptiveThreshold();
}

void ImageProcessing::globalCurrent()
{
    globBox->show();
    adaptBox->hide();
    filterBox->hide();
    globalThreshold();
}

void ImageProcessing::adaptiveCurrent()
{
    globBox->hide();
    adaptBox->show();
    filterBox->hide();
    adaptiveThreshold();
}

void ImageProcessing::FilterCurrent()
{
    globBox->hide();
    adaptBox->hide();
    filterBox->show();
    smoothFilters();
}

void ImageProcessing::createSlider(QSlider *&slider, QLabel *&min, QLabel *&max, QSpinBox *&spBox,
                                   QHBoxLayout *&layout, int val)
{
    slider = new QSlider;

    slider->setOrientation (Qt::Horizontal);
    slider->setMinimum (0);
    slider->setMaximum (255);
    slider->setSingleStep (1);
    slider->setValue (val);

    spBox = new QSpinBox(this);
    spBox->setMinimum(0);
    spBox->setMaximum(255);
    spBox->setSingleStep(1);
    spBox->setValue(val);

    min = new QLabel;
    max = new QLabel;

    min->setText("0");
    max->setText("255");

    layout->addWidget (spBox);
    layout->addWidget(min);
    layout->addWidget(slider);
    layout->addWidget(max);
}

void ImageProcessing::processing()
{
    if (globalThres->isChecked())
        globalThreshold();
    else if (adaptiveThres->isChecked())
        adaptiveThreshold();
    else
        smoothFilters();
}

void ImageProcessing::setProcessedImage()
{
    procImg = QImage((const unsigned char*)(processedMat.data),
                     processedMat.cols, processedMat.rows, processedMat.step, QImage::Format_Grayscale8);

    imageLabel2->setPixmap(QPixmap::fromImage(procImg));
}

