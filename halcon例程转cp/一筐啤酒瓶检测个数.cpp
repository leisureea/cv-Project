#include "ha2cp.h"


int main()
{
	ha2cp ha;

	Mat img,img1, region, region1, region2, region3, out, output;

	img = imread("D:/VS2019/[data/images/bottles/bottle_crate_10.png", 0);
	if (img.empty())
	{
		cout << "打开图片失败" << endl;
		return -1;
	}


	ha.threshold(img, img1, 50, 130);

	ha.opening_circle(img1, img1, 3);

	ha.threshold(img, region, 85, 255);
	ha.difference(region, img1, output);

	//大反射区域就是混乱
	ha.select_shape(region, region1, "width", 100, 500);
	ha.select_shape(region, region2, "height", 100, 400);
	bitwise_or(region1, region2, region3);
	ha.opening_circle(region3, region3, 8);

	ha.difference(region, region3, region);

	//ignore noise regions
	ha.select_shape(region, region1, "width", 25, 100);
	ha.select_shape(region, region2, "height", 25, 100);
	bitwise_and(region1, region2, region3);

	ha.fill_up(region3, region3);
	ha.opening_circle(region3, region3, 15);

	////only 'round' reflections are from bottles
	ha.select_shape(region3, region3, "circularity", 0.77, 1);
	//ha.select_shape(region3, region3, "width", 20, 99999);




	double sta = (double)getTickCount();



	cout << "Time:  " << ((double)getTickCount() - sta) * 1000 / getTickFrequency() << "ms" << endl;


	namedWindow("he", WINDOW_AUTOSIZE);
	imshow("he", region3);
	//imwrite("1234.jpg", region);
	waitKey(0);

}

