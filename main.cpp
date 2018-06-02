#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <iostream>
#define VIDEO_WIDTH         176
#define VIDEO_HEIGHT        144


#define BGR_BUFF_SIZE       VIDEO_WIDTH*VIDEO_HEIGHT*3
#define YUV_BUFF_SIZE       BGR_BUFF_SIZE/2

static bool YUV420ToBGR24_OpenCV(unsigned char* pYUV,unsigned char* pBGR,int width,int height)
{
    if (width < 1 || height < 1 || pYUV == NULL || pBGR == NULL)
        return false;
    cv::Mat dst(height,width,CV_8UC3,pBGR);
    cv::Mat src(height + height/2,width,CV_8UC1,pYUV);
    cv::cvtColor(src,dst,CV_YUV420p2RGB);
    return true;
}


typedef unsigned char BYTE;
 inline BYTE valueCorrection(int i)
{
    if(i<0)
        return 0;
    else if(i>255)
        return 255;
    else
        return i;
}
 //B = Y + 1.772 (U-128)
 //G = Y - 0.34414 (U-128) - 0.71414 (V-128)
 //R = Y + 1.402 (V-128)
static void YUV420ToBGR(const BYTE *yuvBuffer,BYTE *pBGR,int width,int height)
{
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            int index = y * width + x;

            int indexY = y * width + x;
            int indexU = width * height + y / 2 * width / 2 + x / 2;
            int indexV = width * height + width * height / 4 + y / 2 * width / 2 + x / 2;

            BYTE Y = yuvBuffer[indexY];
            BYTE U = yuvBuffer[indexU];
            BYTE V = yuvBuffer[indexV];

            int B = Y + 1.772*(U-128);
            int G = Y - 0.34413 * (U-128) - 0.71414*(V-128);
            int R = Y + 1.402 * (V-128);

            pBGR[index*3] = valueCorrection(B);
            pBGR[index*3+1] = valueCorrection(G);
            pBGR[index*3+2] = valueCorrection(R);
        }
    }
}
int main(int argc, char *argv[])
{
    unsigned char yuvBuf[YUV_BUFF_SIZE];
    unsigned char bgrBuf[BGR_BUFF_SIZE];

    FILE *file, *bgrFile;
    if(!(file = fopen("D:\\work\\study\\examination\\C\\demo\\medium2\\medium2\\data\\news_qcif_176\\news_qcif.yuv","rb")))
    {
        printf("file open error!");
        exit(0);
    }
    if((bgrFile = fopen("test.bgr","wb")) == NULL)
    {
        printf("bgrfile open error!");
        exit(0);
    }
    else
    {
        // 计算总帧数
        fseek(file, 0, SEEK_END);
        int frame_count = 0;
        long file_size = 0;
        frame_count = (int) ((int)ftell(file)/(YUV_BUFF_SIZE));  // ftell 用于求文件大小
        printf("frame num is %d \n", frame_count);
        printf("file length is   %d",ftell(file));
        fseek(file, 0, SEEK_SET);//文件内位置定位到文件头

        //测试-显示yuv视频
        cvNamedWindow("a");
//        IplImage *yimg = cvCreateImage(cvSize(VIDEO_WIDTH, VIDEO_HEIGHT),IPL_DEPTH_8U,1);
//        int pos = 0;
//        for(int i = 0; i<frame_count-1; i++ )
//        {
//             fseek(file, pos, SEEK_SET);
//             fread(yuvBuf,1 , YUV_BUFF_SIZE, file );
//             cvSetData(yimg, yuvBuf, VIDEO_WIDTH);
//             cvNamedWindow("a");
//             cvShowImage("a", yimg);
//             cvWaitKey( 33 );
//             pos += YUV_BUFF_SIZE;
//        }

        //yuv-bgr  save
        int pos = 0;
        for(int i = 0; i<frame_count-1; i++ )
        {
         fseek(file, pos, SEEK_SET);
         fread(yuvBuf,1 , YUV_BUFF_SIZE, file);
         //软实现
         YUV420ToBGR(yuvBuf, bgrBuf, VIDEO_WIDTH, VIDEO_HEIGHT);
         //opencv实现
         //YUV420ToBGR24_OpenCV(yuvBuf, bgrBuf, VIDEO_WIDTH, VIDEO_HEIGHT);


        //调试，bgr显示、写成图片
         cv::Mat mat(VIDEO_HEIGHT, VIDEO_WIDTH, CV_8UC3, bgrBuf);
         cvNamedWindow("a");
         cv::imshow("a", mat);
         cvWaitKey( 33 );
//         std::ostringstream ostr;
//         ostr << i << ".jpg";
//         cv::imwrite(ostr.str(), mat);

         //写BGR文件
         fwrite(bgrBuf, BGR_BUFF_SIZE, 1, bgrFile);

         //读偏移
         pos += YUV_BUFF_SIZE;
        }

        cvDestroyWindow("a");
        //cvReleaseImage(&yimg);
        fclose(file);
        fclose(bgrFile);
    }


}
