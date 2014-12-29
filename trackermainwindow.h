#ifndef TRACKERMAINWINDOW_H
#define TRACKERMAINWINDOW_H

#include <QMainWindow>
#include <opencv2/highgui/highgui.hpp>
#include <imagefiledialog.h>
//#include <thread>
#include "featuresmatcher.h"

namespace Ui {
    class TrackerMainWindow;
}

class TrackerMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit TrackerMainWindow(QWidget *parent = 0);
    ~TrackerMainWindow();

private slots:
    void on_actionStart_triggered();
    void on_actionFileBrowse_triggered();
    void on_actionStop_triggered();
    void on_actionTrack_triggered();

private:
    Ui::TrackerMainWindow *ui;
    VideoCapture mCapture;
    int timerId;
    string fileRootPath;
    GpuMat objectImg;
    GpuMat sceneImg;
    FeaturesMatcher *featuresMatcher;
    bool track;

    void processFrame(Mat);

protected:
    void timerEvent(QTimerEvent *event);
    void timerEvent();
};

#endif // TRACKERMAINWINDOW_H
