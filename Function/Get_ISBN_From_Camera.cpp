#include "Get_ISBN_From_Camera.h"

#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <QTextCodec>
#include <string>
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgcodecs/imgcodecs.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/types_c.h>
#include <opencv2/highgui/highgui_c.h>
#include <string>
#include <vector>
#include <QDebug>
#include <zbar.h>
#include <zbar/Decoder.h>
#include <iconv.h>

using namespace std;
using namespace zbar;
using namespace cv;

QString GetISBNFromCamera()
{
    VideoCapture capture(0);
    if (!capture.isOpened()){//没有打开摄像头的话，就返回。
        return NULL;
    }
    // 创建窗口，名为"Scanner"，自动调整大小
    cvNamedWindow("Scanner", CV_WINDOW_AUTOSIZE);
    // 灰度图
    // 创建zbar图像扫描器
    ImageScanner scanner;
    scanner.set_config(ZBAR_ISBN13,ZBAR_CFG_ENABLE,1);
    // 配置zbar图片扫描器，采取13位ISBN

    //scanner.set_config(ZBAR_NONE, ZBAR_CFG_ENABLE, 1);
    while (1)
    {
        // 从摄像头中抓取一帧
        Mat frame;
        capture>>frame;
        // 图像不为空
        if (!frame.empty())
        {
            Mat imageGray;
            imshow("Finally",frame);
            cvtColor(frame,imageGray,CV_RGB2GRAY);

            int width = imageGray.cols;
            int height = imageGray.rows;
            uchar *raw = (uchar*)imageGray.data;
            Image CheckZBar(width,height,"Y800",raw,width*height);
            scanner.scan(CheckZBar);
            Image::SymbolIterator symbol = CheckZBar.symbol_begin();
            int test = 0;
            if(!(CheckZBar.symbol_begin()==CheckZBar.symbol_end())){
                test = 1;
            }
            for(;symbol != CheckZBar.symbol_end();++symbol)
            {
                cout<<"Type:"<<endl<<symbol->get_type_name()<<endl;
                cout<<"Data:"<<endl<<symbol->get_data()<<endl;
                string answer = symbol->get_data();
                QString ans = QString::fromStdString(answer);
                cv::destroyAllWindows();
                return ans;
            }
            if(test){
                cv::destroyAllWindows();
                goto stop;
            }

            // 下一个二维码
        }
        // 按了ESC可退出
        if (cvWaitKey(50) == 27) {
            cv::destroyAllWindows();
            break;
        }
        // 按叉可推出
        if (!cvGetWindowHandle("Scanner"))
        {
            cv::destroyAllWindows();
            break;
        }
    }
stop:
    return "";
}

