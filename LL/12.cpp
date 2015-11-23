/*#include "opencv2/imgproc/imgproc.hpp"   
#include "opencv2/highgui/highgui.hpp"   
#include <iostream>   
using namespace cv;  
using namespace std;  
Mat img;  
int threshval = 160;            //轨迹条滑块对应的值，给初值160   

  
static void on_trackbar(int, void*)  
{  
   Mat bw = threshval < 128 ? (img < threshval) : (img > threshval);  //定义点和向量   
   vector<vector<Point> > contours;  
   vector<Vec4i> hierarchy;  //查找轮廓   
    findContours( bw, contours, hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE );  
    //初始化dst   
    Mat dst = Mat::zeros(img.size(), CV_8UC3);  
   //开始处理   
   if( !contours.empty() && !hierarchy.empty() )  
  {  
       //遍历所有顶层轮廓，随机生成颜色值绘制给各连接组成部分   
        int idx = 0;  
      for( ; idx >= 0; idx = hierarchy[idx][0] )  
      {  
          Scalar color( (rand()&255), (rand()&255), (rand()&255) );  
          //绘制填充轮廓   
           drawContours( dst, contours, idx, color, CV_FILLED, 8, hierarchy );  
       }  
   }  
   //显示窗口   
   imshow( "Connected Components", dst );  
}  
   
int main(  )  
{  
    system("color 5F");    
    //载入图片   
    img = imread("d:\\2015.jpg", 0);  
    if( !img.data ) { printf("Oh，no，读取img图片文件错误~！ \n"); return -1; }  
  
    //显示原图   
    namedWindow( "Image", 1 );  
    imshow( "Image", img );  
  
    //创建处理窗口   
    namedWindow( "Connected Components", 1 );  
    //创建轨迹条   
    createTrackbar( "Threshold", "Connected Components", &threshval, 255, on_trackbar );  
    on_trackbar(threshval, 0);//轨迹条回调函数   
   waitKey(0);  
    return 0;  
}*/
/*#include <opencv2/opencv.hpp>   
using namespace std;  
#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")   
IplImage *g_pGrayImage = NULL;  
const char *pstrWindowsBinaryTitle = "二值图(http://blog.csdn.net/MoreWindows)";  
const char *pstrWindowsOutLineTitle = "轮廓图(http://blog.csdn.net/MoreWindows)";  
CvSeq *g_pcvSeq = NULL;  
  
void on_trackbar(int pos)  
	{  
   // 转为二值图   
    IplImage *pBinaryImage = cvCreateImage(cvGetSize(g_pGrayImage), IPL_DEPTH_8U, 1);  
    cvThreshold(g_pGrayImage, pBinaryImage, pos, 255, CV_THRESH_BINARY);  
    // 显示二值图   
    cvShowImage(pstrWindowsBinaryTitle, pBinaryImage);  
  
    CvMemStorage* cvMStorage = cvCreateMemStorage();  
    // 检索轮廓并返回检测到的轮廓的个数   
    cvFindContours(pBinaryImage,cvMStorage, &g_pcvSeq);  
  
    IplImage *pOutlineImage = cvCreateImage(cvGetSize(g_pGrayImage), IPL_DEPTH_8U, 3);  
    int _levels = 5;  
    cvZero(pOutlineImage);  
    cvDrawContours(pOutlineImage, g_pcvSeq, CV_RGB(255,0,0), CV_RGB(0,255,0), _levels);  
    cvShowImage(pstrWindowsOutLineTitle, pOutlineImage);  
  
    cvReleaseMemStorage(&cvMStorage);  
    cvReleaseImage(&pBinaryImage);  
    cvReleaseImage(&pOutlineImage);  
}  
  
int main( int argc, char** argv )  
{     
    const char *pstrWindowsSrcTitle = "原图(http://blog.csdn.net/MoreWindows)";  
    const char *pstrWindowsToolBarName = "二值化";  
  
    // 从文件中加载原图   
    IplImage *pSrcImage = cvLoadImage("d://2015.jpg", CV_LOAD_IMAGE_UNCHANGED);  
    // 显示原图   
   cvNamedWindow(pstrWindowsSrcTitle, CV_WINDOW_AUTOSIZE);  
    cvShowImage(pstrWindowsSrcTitle, pSrcImage);  
  
    // 转为灰度图   
    g_pGrayImage =  cvCreateImage(cvGetSize(pSrcImage), IPL_DEPTH_8U, 1);  
    cvCvtColor(pSrcImage, g_pGrayImage, CV_BGR2GRAY);  
  
    // 创建二值图和轮廓图窗口   
    cvNamedWindow(pstrWindowsBinaryTitle, CV_WINDOW_AUTOSIZE);  
    cvNamedWindow(pstrWindowsOutLineTitle, CV_WINDOW_AUTOSIZE);  
  
  
    // 滑动条     
    int nThreshold = 0;  
    cvCreateTrackbar(pstrWindowsToolBarName, pstrWindowsBinaryTitle, &nThreshold, 254, on_trackbar);  
  
    on_trackbar(1);  
  
    cvWaitKey(0);  
  
    cvDestroyWindow(pstrWindowsSrcTitle);  
    cvDestroyWindow(pstrWindowsBinaryTitle);  
    cvDestroyWindow(pstrWindowsOutLineTitle);  
    cvReleaseImage(&pSrcImage);  
    cvReleaseImage(&g_pGrayImage);  
    return 0;  
}*/
/*#include <opencv2/opencv.hpp>   
using namespace std;  
#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")   
const char *pstrWindowsMouseDrawTitle = "鼠标绘图(http://blog.csdn.net/MoreWindows)";  
// 鼠标消息的回调函数   
void on_mouse(int event, int x, int y, int flags, void* param)  
{  
    static bool s_bMouseLButtonDown = false;  
   static CvPoint s_cvPrePoint = cvPoint(0, 0);  
  
    switch (event)  
    {  
    case CV_EVENT_LBUTTONDOWN:  
       s_bMouseLButtonDown = true;  
       s_cvPrePoint = cvPoint(x, y);  
       break;  
  
    case  CV_EVENT_LBUTTONUP:  
       s_bMouseLButtonDown = false;  
       break;  
  
    case CV_EVENT_MOUSEMOVE:  
        if (s_bMouseLButtonDown)  
       {  
           CvPoint cvCurrPoint = cvPoint(x, y);  
           cvLine((IplImage*)param, s_cvPrePoint, cvCurrPoint, CV_RGB(0, 0, 20), 3);  
           s_cvPrePoint = cvCurrPoint;  
            cvShowImage(pstrWindowsMouseDrawTitle, (IplImage*)param);  
      }  
       break;  
   }  
}  
int main()  
{     
   const int MAX_WIDTH = 500, MAX_HEIGHT = 400;  
    const char *pstrSaveImageName = "MouseDraw.jpg";  
  
    IplImage *pSrcImage =  cvCreateImage(cvSize(MAX_WIDTH, MAX_HEIGHT), IPL_DEPTH_8U, 3);  
    cvSet(pSrcImage, CV_RGB(255, 0, 0)); //可以用cvSet()将图像填充成白色   
   cvNamedWindow(pstrWindowsMouseDrawTitle, CV_WINDOW_AUTOSIZE);  
    cvShowImage(pstrWindowsMouseDrawTitle, pSrcImage);  
 
    cvSetMouseCallback(pstrWindowsMouseDrawTitle, on_mouse, (void*)pSrcImage);  
  
   int c;  
    do{  
        c = cvWaitKey(0);  
        switch ((char)c)  
        {  
       case 'r':  
            cvSet(pSrcImage, CV_RGB(255, 0, 0));  
          cvShowImage(pstrWindowsMouseDrawTitle, pSrcImage);  
            break;  
  
        case 's':  
            cvSaveImage(pstrSaveImageName, pSrcImage);  
            break;  
        }  
  }while (c > 0 && c != 27);  
 
    cvDestroyWindow(pstrWindowsMouseDrawTitle);  
   cvReleaseImage(&pSrcImage);  
    return 0;  
}*/
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
using namespace cv;
int main()
{
	Mat img1=imread("d:\\Desert.jpg");
	Mat img2=imread("d:\\Desert - 副本.jpg");
	imshow("1",img1);
	imshow("2",img2);
	Mat img_result1,img_result2,img_result;
	subtract(img1,img2,img_result1);
	subtract(img2,img1,img_result2);
	add(img_result1,img_result2,img_result);
	imshow("result",img_result1);
	waitKey();
	return 0;
}
