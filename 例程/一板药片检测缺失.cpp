#include "ha2cp.h"


int main()
{
	ha2cp ha;

	Mat img, img1, region, out, output;

	img = imread("D:/VS2019/[data/images/blister/blister_02.png", 1);
	if (img.empty())
	{
		cout << "打开图片失败" << endl;
		return -1;
	}

	//定位一版药的重心，然后根据相对位置画出下面的模板
	double Area1 = 0.0;
	int Row1 = 0, Column1 = 0;
	ha.access_channel(img, img1, 1);
	ha.threshold(img1, img1, 90, 255);
	ha.select_shape(img1, img1, "area", 10000, 999999);
	ha.shape_trans(img1, img1, "convex");
	ha.area_center(img1, Area1, Row1, Column1);
	//cout << "area:" << Area1 << "\t" << "row:" << Row1 << "\t" << "col:" << Column1 << endl;
	Mat temimage;
	temimage = Mat::zeros(img.rows, img.cols, CV_8UC1);//延展图像  

	int Row = 0, Column = 0;
	for (int i = 0; i < 5; i++)
	{
		Row = Row1 - 140 + i * 70;
		for (int j = 0; j < 3; j++)
		{
			Column = Column1 - 157 + j * 150;
			rectangle(temimage, Point(Column - 64, Row - 30), Point(Column + 64, Row + 30), 255, -1);

		}
	}

	Mat bai; //白框框
	bitwise_not(temimage, bai);


	ha.access_channel(img, region, 3);
	ha.reduce_domain(region, temimage, region);

	bitwise_or(region, bai, bai);

	ha.var_threshold(bai, out, 7, 7, 0.2, 2, "dark");


	//ha.opening_circle(out, out, 1);
	ha.fill_up(out, out);
	ha.select_shape(out, out, "area", 1000, 99999);

	Mat element = getStructuringElement(MORPH_RECT, Size(3, 3));
	morphologyEx(out, out, MORPH_CLOSE, element);

	ha.fill_up(out, out);
	ha.opening_circle(out, out, 5);
	ha.select_shape(out, out, "area", 1000, 99999);
	ha.shape_trans(out, out, "convex");

	//遍历原图的每个药丸区域，面积等于0就表示缺失，
	//面积小于3800或者最小灰度值小于60就表示缺陷


	double sta = (double)getTickCount();

	cout << "Time:  " << ((double)getTickCount() - sta) * 1000 / getTickFrequency() << "ms" << endl;


	namedWindow("he", WINDOW_AUTOSIZE);
	imshow("he", out);
	//imwrite("1234.jpg", out);
	waitKey(0);

}