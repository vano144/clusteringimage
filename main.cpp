#include "mainwindow.h"
#include <QApplication>
#include <QImage>
#include <QLabel>
#include <QDir>
#include <QDebug>
#include <iostream>
#include <QString>
#include "test.h"
#include <QVector>
#include <QRgb>
#include <QColor>
#include <vector>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    //w.show();
        QVector <Imgvec> test=transformPictures(100,77);
        QVector <QVector<Imgval> > test1=calcMatrix(test);
        auto res=calcClusters(test1);
        concKlust(res);
        outputFileName(res);
        QLabel myLabel;
            //myLabel.setPixmap(QPixmap::fromImage(myimage));

            myLabel.show();

    return a.exec();
}
