#include "sate.h"
#include "ui_sate.h"

//int H1=12;
//int S1=136;
//int V1=118;

//int H2=10;
//int S2=121;
//int V2=81;

//int H3=112;
//int S3=32;
//int V3=33;

int lH1=8,hH1=15;
int lS1=88,hS1=185;
int lV1=81,hV1=151;

int lH2=8,hH2=14;
int lS2=96,hS2=191;
int lV2=44,hV2=136;

int lH3=96,hH3=120;
int lS3=15,hS3=54;
int lV3=25,hV3=61;

sate::sate(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::sate)
{
    ui->setupUi(this);
}

sate::~sate()
{
    delete ui;
}

void sate::on_btnFile_clicked()
{
    imgFile = QFileDialog::getOpenFileName(this,"Select Picture","Portable Network Graphic (*.png)");

    if(imgFile.isEmpty()){
        return;
    }

    ui->txtFile->setText(imgFile);

    imgOri = cv::imread(imgFile.toStdString());

    cv::imshow("Ori",imgOri);
}

void sate::on_btnAnalize_clicked()
{
    uint p1,p2,p3;
    p1=get_pixel_count(imgOri,lH1,hH1,lS1,hS1,lV1,hV1,"Cat 1");
    p2=get_pixel_count(imgOri,lH2,hH2,lS2,hS2,lV2,hV2,"Cat 2");
    p3=get_pixel_count(imgOri,lH3,hH3,lS3,hS3,lV3,hV3,"Cat 3");

    ui->lblResult->setText(QString::number(get_pixel_max(p1,p2,p3)));

    QString boxpesan;

    boxpesan += "Cat 1= ";
    boxpesan += QString::number(p1);
    boxpesan += "\n";

    boxpesan += "Cat 2= ";
    boxpesan += QString::number(p3);
    boxpesan += "\n";

    boxpesan += "Cat 3= ";
    boxpesan += QString::number(p3);
    boxpesan += "\n";

    QMessageBox::information(this,"Daftar total Pixel",boxpesan);

}

uint sate::get_pixel_count(cv::Mat imgInput, int lH, int hH, int lS, int hS, int lV, int hV,std::string winname){
    cv::Mat imgHSV;
    cv::Mat imgThresholded;
    cv::Mat imgBiner;
    uint vRow,vCol;
    cv::Mat xval;
    cv::Mat mArea;
    uint Area;
    uint i,j;

    vRow= imgInput.rows;
    vCol= imgInput.cols;

    cv::cvtColor(imgInput, imgHSV, cv::COLOR_BGR2HSV);

    cv::inRange(imgHSV, cv::Scalar(lH, lS, lV), cv::Scalar(hH, hS, hV), imgThresholded);

    cv::imshow(winname,imgThresholded);

    imgBiner = cv::Mat(imgInput.size(),CV_8U,cv::Scalar(0));

    for(i=0;i<vRow;i++){
        for(j=0;j<vCol;j++){
            if(imgThresholded.at<uchar>(i,j)==255){imgBiner.at<uchar>(i,j)=1;}
            else{imgBiner.at<uchar>(i,j)=0;}
        }
    }

    xval=cv::Mat(1,vCol,CV_16U,cv::Scalar(0));
    for(i=0;i<vCol;i++){
        xval.at<ushort>(0,i)=0;
        for(j=0;j<vRow;j++){
            xval.at<ushort>(0,i)=xval.at<ushort>(0,i)+imgBiner.at<uchar>(j,i);
        }
    }

    mArea=cv::Mat(1,1,CV_16U,cv::Scalar(0));
    for(i=0;i<vCol;i++){
        mArea.at<ushort>(0,0)=mArea.at<ushort>(0,0)+xval.at<ushort>(0,i);
    }
    Area=mArea.at<ushort>(0,0);

    return Area;
}

uint sate::get_pixel_max(uint v1, uint v2, uint v3){
    uint vmax;
    uint vindex;

    vmax=v1;
    vindex=1;

    if(vmax<v2){vmax=v2;vindex=2;}
    if(vmax<v3){vmax=v3;vindex=3;}

    if(vindex==1){return 1;}
    else if(vindex==2){return 2;}
    else if(vindex==3){return 3;}

}
