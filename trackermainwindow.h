#ifndef TRACKERMAINWINDOW_H
#define TRACKERMAINWINDOW_H

#include <QMainWindow>
#include <opencv2/highgui/highgui.hpp>
#include <imagefiledialog.h>
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
    cv::VideoCapture mCapture;
    int timerId;
    string fileRootPath;
    cv::Mat objectImg;
    cv::Mat sceneImg;
    FeaturesMatcher featuresMatcher;
    bool track;

protected:
    void timerEvent(QTimerEvent *event);
};

#endif // TRACKERMAINWINDOW_H
