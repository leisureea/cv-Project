#include "ha2cp.h"


int main()
{
	ha2cp ha;
	mycv mc;
	Mat img,img1, region, region1, region2, region3, out, output;

	img = imread("D:/VS2019/[data/images/food/fish_sticks_raw_03.png", 0);
	if (img.empty())
	{
		cout << "打开图片失败" << endl;
		return -1;
	}

	//筛选生鱼片
	ha.threshold(img, img1, 50, 255);
	ha.fill_up(img1, img1);
	ha.select_shape(img1, img1, "area", 1000, 99999);

	//选择不与图像边框相交的区域

	mc.select_region_no_frame(img1, img1);

	//根据每个像素实际尺寸计算生鱼片尺寸，进而筛选


	double sta = (double)getTickCount();


	cout << "Time:  " << ((double)getTickCount() - sta) * 1000 / getTickFrequency() << "ms" << endl;

	namedWindow("he", WINDOW_AUTOSIZE);
	imshow("he", img1);
	//imwrite("1234.jpg", region);
	waitKey(0);

}

