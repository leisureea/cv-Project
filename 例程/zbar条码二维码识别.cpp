#include <iostream>
#include <zbar.h>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace zbar;
using namespace cv;

int main()

{
	ImageScanner scanner;

	scanner.set_config(ZBAR_NONE, ZBAR_CFG_ENABLE, 1);

	Mat img = imread("D:\\Halcon\\É¨Âë\\12.jpg");

	Mat imgGray;
	cvtColor(img, imgGray, CV_BGR2GRAY);

	int width = imgGray.cols;

	int height = imgGray.rows;

	Image image(width, height, "Y800", imgGray.data, width * height);

	int n = scanner.scan(image);  //É¨ÃèÌõÂë

	if (image.symbol_begin() == image.symbol_end())
	{
		cout << "²éÑ¯ÌõÂëÊ§°Ü£¬Çë¼ì²éÍ¼Æ¬£¡" << endl;
	}
	for (Image::SymbolIterator symbol = image.symbol_begin(); symbol != image.symbol_end(); ++symbol) 
	{

		cout << "ÀàĞÍ£º " << symbol->get_type_name()<<endl

			<< "ÌõÂë£º \"" << symbol->get_data() << '"' << endl;

	}

	image.set_data(NULL, 0);


	return(0);

}

