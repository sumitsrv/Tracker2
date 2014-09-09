#include "imagefiledialog.h"

using namespace std;

ImageFileDialog::ImageFileDialog(QWidget *parent) :
    QDialog(parent)
{
}

ImageFileDialog::~ImageFileDialog(){
}

string ImageFileDialog::getFile(){
    QFileDialog dialog(this);
    dialog.setNameFilter(tr("Images (*.png *.xpm *.jpg *.jpeg)"));
    dialog.setViewMode(QFileDialog::List);
    dialog.setOption(QFileDialog::ReadOnly, true);

    string filename = "";
    QStringList fileNames;
    if (dialog.exec())
        fileNames = dialog.selectedFiles();

    if(fileNames.size() > 0)
        filename = fileNames.at(0).toUtf8().constData();

    return filename;
}
