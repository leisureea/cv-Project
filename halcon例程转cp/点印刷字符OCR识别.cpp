#include "ha2cp.h"

////�ָ���ַ���ȡregion1��Ӧ����Ȼ��ʶ��
void partition_rectangle(const Mat _src, const Mat _src1, int Width, int Height);


int main()
{
	ha2cp ha;
	mycv mc;

	Mat img,img1, region, region1, region2, out, output;

	img = imread("D:/VS2019/[data/images/needle1.png", 0);
	if (img.empty())
	{
		cout << "��ͼƬʧ��" << endl;
		return -1;
	}


	ha.sobel_amp(img, img1, "thin_sum_abs", 3);
	ha.threshold(img1, region, 35, 255);
	
	vector<Vec4i> lines;   //���ֱ��
	HoughLinesP(region, lines, 1, CV_PI / 180, 260, 260, 35);

	vector<float> angles;   //��ȡÿ���߽Ƕ�
	mc.get_lines_arctan(lines, angles); 
	//��ǶȾ�ֵ
	float sum = 0.0;
	for (int i = 0; i < angles.size(); i++)
		sum = sum + angles[i];
	
	float mean = sum / angles.size(); //��ֵ  
	mc.rotate(img, region1, mean);  //��ת

	ha.threshold(region1, region1, 0, 105);
	
	ha.select_shape(region1, region1, "area", 6, 99999);  //�Ƴ�����
	ha.rectangle1_domain(region1, region1, 53, 75, 260, 356);

	ha.closing_circle(region1, region2, 5);

	ha.opening_rectangle1(region2, region2, 1, 4);
	ha.select_shape(region2, region2, "area", 150, 5999);
	ha.shape_trans(region2, region2, "rectangle1");

	//ha.partition_rectangle(region2, region2, 25, 100);

	ha.closing_circle(region1, region1, 2);

	//�ָ���ַ�����region1��Ȼ��ʶ��
	//_src��Ҫ�ָ��ͼ��_src1��Ҫ��ͼ����ʶ���ͼ��
	partition_rectangle(region2, region1, 25, 100);


	double sta = (double)getTickCount();

	cout << "Time:  " << ((double)getTickCount() - sta) * 1000 / getTickFrequency() << "ms" << endl;

	//namedWindow("he", WINDOW_AUTOSIZE);
	//imshow("he", out);
	//imwrite("1234.jpg", img1);
	waitKey(0);

}


////�ָ���ַ���ȡregion1��Ӧ����Ȼ��ʶ��
//_src��Ҫ�ָ��ͼ��_src1��Ҫ��ͼ����ʶ���ͼ��
void partition_rectangle(const Mat _src, const Mat _src1, int Width, int Height)
{
	mycv mc;

	vector< vector< Point> > contours;
	findContours(_src, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);//�������������


	Rect boundRect;
	for (int i = 0; i < contours.size(); i++)
	{
		boundRect = boundingRect(Mat(contours[i]));
		if (boundRect.width > (int)(Width * 1.5))
		{
			//vector< Rect> aveRect;
			int a = boundRect.width / Width;  //�ֳ�a��
			int wid = boundRect.width / a;    //ÿ�γ�
			for (int j = 0; j < a; j++)
			{
				Rect boundRect1(boundRect.tl().x + wid * j-1, boundRect.tl().y-1, wid + 1, boundRect.height+1);
				//aveRect.push_back(boundRect1);
				//rectangle(_dst, boundRect1.tl(), boundRect1.br(), 255, -1);
				Mat roi1;
				_src1(boundRect1).copyTo(roi1);
				//����opencv textʶ�𵥸���ĸ����ҪԤѵ���� .gz �ļ�
				//mc.character_recognition(roi1);
				auto text = mc.identifyText(roi1, "eng");
				cout << text << endl;
				namedWindow("he", WINDOW_AUTOSIZE);
				imshow("he", roi1);
				waitKey(0);
				destroyWindow("he");

			}

		}
		else
		{
			//rectangle(_dst, boundRect.tl(), boundRect.br(), 255, -1);
			Mat roi1;
			_src1(boundRect).copyTo(roi1);
			//����opencv textʶ�𵥸���ĸ����ҪԤѵ���� .gz �ļ�
			//mc.character_recognition(roi1);
			auto text = mc.identifyText(roi1, "eng");
			cout << text << endl;
			namedWindow("he", WINDOW_AUTOSIZE);
			imshow("he", roi1);
			waitKey(0);
			destroyWindow("he");
		}
	}



}
