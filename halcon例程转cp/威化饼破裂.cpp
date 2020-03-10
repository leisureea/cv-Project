#include "ha2cp.h"


int main()
{
	ha2cp ha;

	Mat img,img1, region, region1, region2, region3, out, output;

	img = imread("D:/VS2019/[data/images/food/hazelnut_wafer_08.png", 0);
	if (img.empty())
	{
		cout << "打开图片失败" << endl;
		return -1;
	}

	double UsedThreshold = 0.0;
	ha.binary_threshold(img, img1, "smooth_histo", "light", UsedThreshold);

	ha.opening_circle(img1, img1, 8);

	//孔洞面积和矩形度AreaHoles > 300 or Rectangularity < 0.92不合格
	double AreaHoles = 0.0;
	ha.area_holes(img1, AreaHoles);
	cout << AreaHoles << endl;

	double Rectangularity;
	ha.rectangularity(img1, Rectangularity);
	cout << Rectangularity << endl;





	double sta = (double)getTickCount();

	cout << "Time:  " << ((double)getTickCount() - sta) * 1000 / getTickFrequency() << "ms" << endl;

	namedWindow("he", WINDOW_AUTOSIZE);
	imshow("he", img1);
	//imwrite("1234.jpg", region);
	waitKey(0);

}

