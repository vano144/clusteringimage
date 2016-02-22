#ifndef TEST
#define TEST
#include <QDir>
#include <QDebug>
#include <iostream>
#include <QString>
#include <QImage>
#include <vector>
#include <map>
#include <iostream>
#include <iterator>

struct Adress {
    int i;
    int j;
    Adress()
    {
        i=0;
        j=0;
    }
    Adress(int a,int b)
    {
        i=a;
        j=b;
    }
};

struct Imgval
{
    QVector<QString> fileNames;
    int values;
    QVector<int> resultVector;
    Imgval()
    {
        values=0;
    }

    Imgval(QString name,QString name1,int a)
    {
        if (!fileNames.count(name))
        fileNames.insert(fileNames.end(),name);
        if (!fileNames.count(name1))
        fileNames.insert(fileNames.end(),name1);
        values=a;
    }
};
struct Imgvec
{
    QString fileName;
    QVector<int> values;
    Imgvec()
    {
        fileName="";
    }

    Imgvec(QString name,QVector<int> &a)
    {
        fileName=name;
        values=a;
    }
};

Imgvec resize(QString absFilePath,QString fileName,int width,int height)
{
    Imgvec result;
    QImage myimage1;
    myimage1.load(absFilePath);
    QImage k=myimage1.convertToFormat(QImage::Format_RGB888);
    QImage myimage = k.scaled(width, height, Qt::KeepAspectRatio);
    int l=0;
    for (int i=0;i<myimage.height();i++)
        for (int j=0;j<myimage.width();j++)
        {
            int r=qRed(myimage.pixel(j,i));
            if (r<=128) r=0;
            else r=255;
            int g=qRed(myimage.pixel(j,i));
            if (g<=128) g=0;
            else g=255;
            int b=qRed(myimage.pixel(j,i));
            if (b<=128) b=0;
            else b=255;
            if (r==255) l=1;
            else l=0;
            result.values.insert(result.values.end(),l);
            QRgb value = qRgb(r, g, b);
            myimage.setPixel(j,i,value);
        }
    QFile mFile("/Users/v144/Documents/fortest/png/"+fileName);
    mFile.open(QIODevice::ReadWrite);
    mFile.close();
    myimage.save("/Users/v144/Documents/fortest/png/"+fileName);
    result.fileName=fileName;
    return result;
}
QVector<Imgvec> transformPictures(int width,int height)
{
    QVector<Imgvec > result;
    QDir dir("/Users/v144/Documents/fortest");
    QFileInfoList dirContent = dir.entryInfoList(QStringList()<< "*.png",QDir::Dirs | QDir::Files | QDir::NoDotAndDotDot);
    for (int i=0;i<dirContent.size();i++)
    {
        result.insert(result.end(),resize(dirContent[i].absoluteFilePath(),dirContent[i].fileName(),width,height));
    }
    return result;
}
int calcEvclid(QVector<int> A,QVector<int> B)
{
    int result=0;
    int z=0;
    int b=0;
    if (A.size()>=B.size()) b=B.size();
    else b=A.size();
    for (int i=0;i<b;i++)
    {
        z=(A.at(i)-B.at(i))*(A.at(i)-B.at(i));
        result+=z;
    }
    return result;
}
QVector <QVector<Imgval> > calcMatrix(QVector<Imgvec> Matrix)
{
    QVector<Imgval> resultir;
    QVector <QVector<Imgval> > res1;
    for (int i=0;i<Matrix.size();i++)
    {
        for (int j=0;j<Matrix.size();j++)
        {
            resultir.insert(resultir.end(),Imgval(Matrix[i].fileName,Matrix[j].fileName,calcEvclid(Matrix[i].values,Matrix[j].values)));
        }
        res1.insert(res1.end(),resultir);
        resultir.clear();
    }



    return res1;
}

Adress indexMin(QVector <QVector<Imgval> > Date)
{
    int min=INT_MAX;
    Adress minAdress;
    for (int i=0;i<Date.size();i++)
    {
        for (int j=0;j<Date.size();j++)
        {
            if (Date[i].at(j).values<min && i<j && Date[i].at(j).values>=0)
            {
                min=Date[i].at(j).values;
                minAdress.i=i;
                minAdress.j=j;
            }
        }
    }
    return minAdress;
}

bool isMatrixEnd(QVector <QVector<Imgval> > Date)
{
    for (int i=0;i<Date.size();i++)
    {
        for (int j=0;j<Date.size();j++)
        {
            if (Date[i][j].values>=0 && i!=j)
            {
                return false;
            }
        }
    }
    return true;
}
void setMinus(QVector <QVector<Imgval> > &Date,int a)
{
    for (int j=0;j<Date.size();j++)
    {
       Date[a][j].values=-1;
       Date[j][a].values=-1;

    }
}

std::map <QString, QVector <QString> > calcClusters(QVector <QVector<Imgval> > &Date)
{
    std::map <QString, QVector <QString> > result;
    Adress min;
    QVector<QString> temp;
    while(!isMatrixEnd(Date))
    {
        min=indexMin(Date);
        if (Date[min.i][min.j].values<1000)
        {
            if (result.count(Date[min.i].at(min.j).fileNames[0]))
            {
                result[Date[min.i][min.j].fileNames[0]].push_back(Date[min.j][min.i].fileNames[0]);
            }
            else
            {
                temp.insert(temp.end(),Date[min.i].at(min.j).fileNames[0]);
                result.insert(std::pair<QString,QVector<QString> >(Date[min.i].at(min.j).fileNames[0],temp));
                temp.clear();
                result[Date[min.i][min.j].fileNames[0]].push_back(Date[min.i].at(min.j).fileNames[1]);
            }
        }
        else
        {
            temp.insert(temp.end(),Date[min.i].at(min.j).fileNames[0]);
            result.insert(std::pair<QString,QVector<QString> >(Date[min.i].at(min.j).fileNames[0],temp));
            temp.clear();
            temp.insert(temp.end(),Date[min.i].at(min.j).fileNames[1]);
            result.insert(std::pair<QString,QVector<QString> >(Date[min.i].at(min.j).fileNames[1],temp));
            temp.clear();
        }
        setMinus(Date,min.j);
    }
    return result;
}
void concKlust(std::map <QString, QVector <QString> > &result)
{
    for(auto i=result.begin(); i!=result.end(); ++i)
    {
        for(auto j=(i->second).begin(); j!=(i->second).end(); ++j)
        {
            if((i->first)==*j) continue;
            if(result.count(*j)>0)
            {
                for(auto k=result[*j].begin(); k!=result[*j].end(); ++k)
                {
                    result[i->first].push_back(*k);
                }
                result.erase(*j);
            }
        }
    }
}

void outputFileName(std::map <QString, QVector <QString> > result)
{
    for(auto i=result.begin(); i!=result.end(); ++i)
    {
        for(auto j=(i->second).begin(); j!=(i->second).end(); ++j)
        {
            std::cout<<(*j).toStdString()<<" ";
        }
        std::cout<<std::endl;
    }

}

#endif // TEST

