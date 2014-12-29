#include "trackermainwindow.h"
#include "ui_qtglwebcamdemo.h"
#include "features.h"
#include "featuresmatcher.h"

using namespace std;

TrackerMainWindow::TrackerMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TrackerMainWindow)
{
#ifdef ANDROID
    fileRootPath = getenv("EXTERNAL_STORAGE");
#else
    fileRootPath = "";
#endif
    featuresMatcher = new FeaturesMatcher();
    track = false;
    ui->setupUi(this);
}

TrackerMainWindow::~TrackerMainWindow()
{
    delete ui;
}

void TrackerMainWindow::timerEvent(QTimerEvent *event)
{
    Mat captureImg;
    mCapture >> captureImg;

    cvtColor(captureImg, sceneImg, CV_BGR2GRAY, 1);
    TrackerFeatures *sceneFeatures = new TrackerFeatures();

    sceneFeatures->detect(sceneImg);
    sceneFeatures->image = sceneImg;

    featuresMatcher->sceneFeatures = sceneFeatures;

    processFrame(captureImg);
//    std::thread first (&TrackerMainWindow::processFrame, this, captureImg);
//    first.detach();
}

void TrackerMainWindow::on_actionFileBrowse_triggered()
{
    ImageFileDialog *fileDialog = new ImageFileDialog();
    string objectRelativePath = fileDialog->getFile();

    if(!objectRelativePath.empty()){
        objectImg.upload(cv::imread(objectRelativePath, CV_LOAD_IMAGE_GRAYSCALE));

        TrackerFeatures *objectFeatures = new TrackerFeatures();
        objectFeatures->detect(objectImg);
        objectFeatures->image = objectImg.clone();

        Mat imgV;
        objectImg.download(imgV);
        ui->imageViewer->showImage( imgV );
        featuresMatcher->prepMatcher(objectFeatures);
    }
}

void TrackerMainWindow::on_actionStart_triggered()
{
    if( !mCapture.isOpened() )
    {
        mCapture.set(CV_CAP_PROP_FPS, 30.0);
        mCapture.set(CV_CAP_PROP_FRAME_HEIGHT, 480.0);
        mCapture.set(CV_CAP_PROP_FRAME_WIDTH, 640.0);

        if( !mCapture.open( CV_CAP_ANY ) )
        {
            return;
        }
        else
        {
            timerId = startTimer(10);
        }
    }

    if(ui->imageViewer->isHidden()){
        ui->imageViewer->show();
    }
}

void TrackerMainWindow::on_actionStop_triggered()
{
    mCapture.release();
    killTimer(timerId);
    track = false;
    ui->imageViewer->hide();
}

void TrackerMainWindow::on_actionTrack_triggered()
{
    track = true;
}

void TrackerMainWindow::processFrame(Mat captureImg)
{
    if(track){
        Mat drawMatch = featuresMatcher->getMatch(captureImg);
        ui->imageViewer->showImage(drawMatch);
    }
    else{
        ui->imageViewer->showImage( captureImg );
    }
}
