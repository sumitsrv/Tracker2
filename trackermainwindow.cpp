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
    featuresMatcher = FeaturesMatcher();
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
    TrackerFeatures sceneFeatures = TrackerFeatures();

    sceneFeatures.detect(sceneImg);
    sceneFeatures.image = sceneImg;

    featuresMatcher.sceneFeatures = sceneFeatures;

    if(track){
        Mat drawMatch = featuresMatcher.getMatch(captureImg);
        ui->imageViewer->showImage(drawMatch);
    }
    else{
        ui->imageViewer->showImage( captureImg );
    }
}

void TrackerMainWindow::on_actionFileBrowse_triggered()
{
    ImageFileDialog *fileDialog = new ImageFileDialog();
    string objectRelativePath = fileDialog->getFile();

    if(!objectRelativePath.empty()){
        objectImg = cv::imread(objectRelativePath, CV_LOAD_IMAGE_GRAYSCALE);

        TrackerFeatures objectFeatures = TrackerFeatures();
        objectFeatures.detect(objectImg);
        objectFeatures.image = objectImg.clone();

        ui->imageViewer->showImage( objectImg );
        featuresMatcher.prepMatcher(objectFeatures);
    }
}

void TrackerMainWindow::on_actionStart_triggered()
{
    if( !mCapture.isOpened() )
    {
        if( !mCapture.open( CV_CAP_ANY ) )
        {
            return;
        }
        else
        {
            mCapture.set(CV_CAP_PROP_FPS, 30);
            timerId = startTimer(0);
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
