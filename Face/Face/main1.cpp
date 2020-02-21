#include <opencv2/opencv.hpp>
#include <iostream>
#include <math.h>
#include<opencv2/face.hpp>
using namespace  cv;
using namespace cv::face;
using namespace std;

int main(int argc, char *argv[])
{
    VideoCapture v(0);
    Mat src;
    namedWindow("src",CV_WINDOW_AUTOSIZE);
    char c = 0;
    CascadeClassifier c1;
    bool res = c1.load("haarcascade_frontalface_alt.xml");
    if(res == true)
    {
        cout<<"xml ok"<<endl;
    }else{
        cout<<"xml error"<<endl;
        return -1;
    }
    Mat dst;
    Mat dst1;
    vector<Rect> faces;
    int i = 0;
    Mat image;
    Mat imagel;
    int count = 1;
    while(v.read(src)){
        dst = Mat::zeros(src.size(),src.type());
        cvtColor(src,dst,CV_BGR2GRAY);
        dst1 = Mat::zeros(dst.size(),dst.type());
        equalizeHist(dst,dst1);
        c1.detectMultiScale(dst1,faces,1.1,3,0,Size(50,50));
        //cout<<"num :"<<faces.size()<<endl;
        for(i = 0;i < faces.size();i++)
        {
            rectangle(src,faces[i],Scalar(0,0,255),2,LINE_8,0);
            //image = src(Rect(faces[i].x,faces[i].y,faces[i].width, faces[i].height));
            //resize(image,imagel,Size(100,100));
            //imwrite(format("rrr%d.jpg",count),imagel);
            count++;
        }
        imshow("src",src);
        c = waitKey(30);
        if(c == 27)
        {
            break;
        }
    }
    waitKey(0);
    return 0;

}
