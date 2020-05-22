#include "ha2cp.h"


int main()
{
	ha2cp ha;
	mycv mc;
	Mat img,img1, region, region1, region2, region3, out, output;

	img = imread("D:/VS2019/[data/images/food/fish_sticks_raw_03.png", 0);
	if (img.empty())
	{
		cout << "��ͼƬʧ��" << endl;
		return -1;
	}

	//ɸѡ����Ƭ
	ha.threshold(img, img1, 50, 255);
	ha.fill_up(img1, img1);
	ha.select_shape(img1, img1, "area", 1000, 99999);

	//ѡ����ͼ��߿��ཻ������

	mc.select_region_no_frame(img1, img1);

	//����ÿ������ʵ�ʳߴ��������Ƭ�ߴ磬����ɸѡ


	double sta = (double)getTickCount();


	cout << "Time:  " << ((double)getTickCount() - sta) * 1000 / getTickFrequency() << "ms" << endl;

	namedWindow("he", WINDOW_AUTOSIZE);
	imshow("he", img1);
	//imwrite("1234.jpg", region);
	waitKey(0);

}

