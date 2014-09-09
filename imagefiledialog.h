#ifndef IMAGEFILEDIALOG_H
#define IMAGEFILEDIALOG_H

#include <QFileDialog>

using namespace std;

class ImageFileDialog : public QDialog
{
    Q_OBJECT
public:
    explicit ImageFileDialog(QWidget *parent = 0);
    ~ImageFileDialog();

signals:

public slots:
    string getFile();

};

#endif // IMAGEFILEDIALOG_H
