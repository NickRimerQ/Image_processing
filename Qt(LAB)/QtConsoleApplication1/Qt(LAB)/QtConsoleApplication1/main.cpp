#include <QtCore/QCoreApplication>
#include <QImage>
#include "Filter.h"
#include <iostream>

using namespace std;

struct pixel
{
	int x;
	int y;
	int rgb;
};

template <class T>
T clampp(T value, T max, T min)
{
	if (value > max)
		return max;
	if (value < min)
		return min;
	return value;
}

void Dilation(const QImage& source, QImage& result)
{
	// Width, Height – размеры исходного и результирующего изображений
	// MW, MH – размеры структурного множества
	int MW, MH;
	bool* mask;
	cout << "Enter MW" << endl;
	cin >> MW;
	MH = MW;
	/*cout << "Enter MH" << endl;
	cin >> MH;*/
	system("cls");
	mask = new bool[MW * MH];
	for (int i = 0; i < MW * MH; i++)
	{
		mask[i] = 0;
	}

	char elemOfMask;
	for (int i = 0; i < MW * MH; i++)
	{
		cout << "Enter 1 or 0" << endl;
		for (int j = 0; j < MW * MH; j++)
		{
			if (j == i)
			{
				cout << "[" << mask[j] << "]" << " ";
			}
			else
			{
				cout << mask[j] << " ";
			}
			if (j % MW == MW - 1 && j > 0)
			{
				cout << endl;
			}
		}
		cin >> elemOfMask;
		if (elemOfMask == '0' || elemOfMask == '1')
		{
			mask[i] = elemOfMask - '0';
		}
		system("cls");

	}
	result = source;

	if (MH * MW % 2 == 1)
	{
		for (int y = MH / 2; y < source.height() - MH / 2; y++)
		{
			for (int x = MW / 2; x < source.width() - MW / 2; x++)
			{
				QColor max;
				max.setRgb(0, 0, 0);
				for (int j = -MH / 2, jj = 0; j <= MH / 2; j++, jj++)
				{
					for (int i = -MW / 2, ii = 0; i <= MW / 2; i++, ii++)
					{
						if ((mask[ii + MH * jj]) && (source.pixelColor(clampp(x + i, source.width() - 1, 0), clampp(y - j, source.height() - 1, 0)).red() > max.red() || source.pixelColor(clampp(x + i, source.width() - 1, 0), clampp(y - j, source.height() - 1, 0)).green() > max.green() || source.pixelColor(clampp(x + i, source.width() - 1, 0), clampp(y - j, source.height() - 1, 0)).blue() > max.blue()))
						{
							max.setRgb(source.pixelColor(clampp(x + i, source.width() - 1, 0), clampp(y - j, source.height() - 1, 0)).red(), source.pixelColor(clampp(x + i, source.width() - 1, 0), clampp(y - j, source.height() - 1, 0)).green(), source.pixelColor(clampp(x + i, source.width() - 1, 0), clampp(y - j, source.height() - 1, 0)).blue());
						}
					}
				}

				if (max.red() > 0 || max.green() > 0 || max.blue() > 0)
				{
					result.setPixelColor(x, y, max);
				}
			}
		}
	}
	else
	{
		for (int y = MH / 2; y < source.height() - MH / 2; y++)
		{
			for (int x = MW / 2; x < source.width() - MW / 2; x++)
			{
				QColor max;
				max.setRgb(0, 0, 0);
				for (int j = -MH / 2, jj = 0; j < MH / 2; j++, jj++)
				{
					for (int i = -MW / 2, ii = 0; i < MW / 2; i++, ii++)
					{
						if ((mask[ii + MH * jj]) && (source.pixelColor(clampp(x + i, source.width() - 1, 0), clampp(y - j, source.height() - 1, 0)).red() + source.pixelColor(clampp(x + i, source.width() - 1, 0), clampp(y - j, source.height() - 1, 0)).green() + source.pixelColor(clampp(x + i, source.width() - 1, 0), clampp(y - j, source.height() - 1, 0)).blue() > max.red() + max.green() + max.blue()))
						{
							max.setRgb(source.pixelColor(clampp(x + i, source.width() - 1, 0), clampp(y - j, source.height() - 1, 0)).red(), source.pixelColor(clampp(x + i, source.width() - 1, 0), clampp(y - j, source.height() - 1, 0)).green(), source.pixelColor(clampp(x + i, source.width() - 1, 0), clampp(y - j, source.height() - 1, 0)).blue());
						}
					}
				}

				if (max.red() > 0 || max.green() > 0 || max.blue() > 0)
				{
					result.setPixelColor(x, y, max);
				}
			}
		}
	}
}


void Erosion(const QImage& source, QImage& result)
{
	// Width, Height – размеры исходного и результирующего изображений
	// MW, MH – размеры структурного множества
	int MW, MH;
	bool* mask;
	cout << "Enter MW" << endl;
	cin >> MW;
	MH = MW;
	/*cout << "Enter MH" << endl;
	cin >> MH;*/
	system("cls");
	mask = new bool[MW * MH];
	for (int i = 0; i < MW * MH; i++)
	{
		mask[i] = 0;
	}

	char elemOfMask;
	for (int i = 0; i < MW * MH; i++)
	{
		cout << "Enter 1 or 0" << endl;
		for (int j = 0; j < MW * MH; j++)
		{
			if (j == i)
			{
				cout << "[" << mask[j] << "]" << " ";
			}
			else
			{
				cout << mask[j] << " ";
			}
			if (j % MW == MW - 1 && j > 0)
			{
				cout << endl;
			}
		}
		cin >> elemOfMask;
		if (elemOfMask == '0' || elemOfMask == '1')
		{
			mask[i] = elemOfMask - '0';
		}
		system("cls");

	}

	result = source;

	if (MH * MW % 2 == 1) {
		for (int y = MH / 2; y < source.height() - MH / 2; y++)
		{
			for (int x = MW / 2; x < source.width() - MW / 2; x++)
			{
				QColor min;
				min.setRgb(255, 255, 255);
				for (int j = -MH / 2, jj = 0; j <= MH / 2; j++, jj++)
				{
					for (int i = -MW / 2, ii = 0; i <= MW / 2; i++, ii++)
					{
						if ((mask[ii + MH * jj]) && (source.pixelColor(clampp(x + i, source.width() - 1, 0), clampp(y - j, source.height() - 1, 0)).red() + source.pixelColor(clampp(x + i, source.width() - 1, 0), clampp(y - j, source.height() - 1, 0)).green() + source.pixelColor(clampp(x + i, source.width() - 1, 0), clampp(y - j, source.height() - 1, 0)).blue() < min.red() + min.green() + min.blue()))
						{
							min.setRgb(source.pixelColor(clampp(x + i, source.width() - 1, 0), clampp(y - j, source.height() - 1, 0)).red(), source.pixelColor(clampp(x + i, source.width() - 1, 0), clampp(y - j, source.height() - 1, 0)).green(), source.pixelColor(clampp(x + i, source.width() - 1, 0), clampp(y - j, source.height() - 1, 0)).blue());
						}
					}
				}

				if (min.red() < 255 || min.green() < 255 || min.blue() < 255)
				{
					result.setPixelColor(x, y, min);
				}
			}
		}
	}
	else
	{
		for (int y = MH / 2; y < source.height() - MH / 2; y++)
		{
			for (int x = MW / 2; x < source.width() - MW / 2; x++)
			{
				QColor min;
				min.setRgb(255, 255, 255);
				for (int j = -MH / 2, jj = 0; j < MH / 2; j++, jj++)
				{
					for (int i = -MW / 2, ii = 0; i < MW / 2; i++, ii++)
					{
						if ((mask[ii + MH * jj]) && (source.pixelColor(clampp(x + i, source.width() - 1, 0), clampp(y - j, source.height() - 1, 0)).red() < min.red() || source.pixelColor(clampp(x + i, source.width() - 1, 0), clampp(y - j, source.height() - 1, 0)).green() < min.green() || source.pixelColor(clampp(x + i, source.width() - 1, 0), clampp(y - j, source.height() - 1, 0)).blue() < min.blue()))
						{
							min.setRgb(source.pixelColor(clampp(x + i, source.width() - 1, 0), clampp(y - j, source.height() - 1, 0)).red(), source.pixelColor(clampp(x + i, source.width() - 1, 0), clampp(y - j, source.height() - 1, 0)).green(), source.pixelColor(clampp(x + i, source.width() - 1, 0), clampp(y - j, source.height() - 1, 0)).blue());
						}
					}
				}

				if (min.red() < 255 || min.green() < 255 || min.blue() < 255)
				{
					result.setPixelColor(x, y, min);
				}
			}
		}
	}
}


void Opening(const QImage& source, QImage& result)
{
	QImage helper;
	Erosion(source, helper);

	Dilation(helper, result);
}

void Closing(const QImage& source, QImage& result)
{
	QImage helper;
	Dilation(source, helper);

	Erosion(helper, result);
}

void Grad(const QImage& source, QImage& result)
{
	result = source;

	QImage helper1;
	QImage helper2;
	QColor color;

	Dilation(source, helper1);
	Erosion(source, helper2);

	for (int y = 0; y < helper1.height(); y++)
	{
		for (int x = 0; x < helper1.width(); x++)
		{
			int red, green, blue;
			red = clampp(helper1.pixelColor(x, y).red() - helper2.pixelColor(x, y).red(), 255, 0);
			green = clampp(helper1.pixelColor(x, y).green() - helper2.pixelColor(x, y).green(), 255, 0);
			blue = clampp(helper1.pixelColor(x, y).blue() - helper2.pixelColor(x, y).blue(), 255, 0);

			color.setRgb(red, green, blue);

			result.setPixelColor(x, y, color);
		}
	}
}

void TopHat(const QImage& source, QImage& result)
{
	result = source;

	QImage helper;
	QColor color;
	Closing(source, helper);

	for (int y = 0; y < helper.height(); y++)
	{
		for (int x = 0; x < helper.width(); x++)
		{
			int red, green, blue;
			red = clampp(source.pixelColor(x, y).red() - helper.pixelColor(x, y).red(), 255, 0);
			green = clampp(source.pixelColor(x, y).green() - helper.pixelColor(x, y).green(), 255, 0);
			blue = clampp(source.pixelColor(x, y).blue() - helper.pixelColor(x, y).blue(), 255, 0);

			color.setRgb(red, green, blue);

			result.setPixelColor(x, y, color);
		}
	}
}

void BlackHat(const QImage& source, QImage& result)
{
	result = source;

	QImage helper;
	QColor color;
	Closing(source, helper);

	for (int y = 0; y < helper.height(); y++)
	{
		for (int x = 0; x < helper.width(); x++)
		{
			int red, green, blue;
			red = clampp(helper.pixelColor(x, y).red() - source.pixelColor(x, y).red(), 255, 0);
			green = clampp(helper.pixelColor(x, y).green() - source.pixelColor(x, y).green(), 255, 0);
			blue = clampp(helper.pixelColor(x, y).blue() - source.pixelColor(x, y).blue(), 255, 0);

			color.setRgb(red, green, blue);

			result.setPixelColor(x, y, color);
		}
	}
}

void MedianFilter(const QImage& source, QImage& result, int radius = 5)
{
	result = source;
	int xx, yy, bright;
	//QColor color;
	for (int y = radius / 2; y < source.height() - radius / 2; y++)
	{
		for (int x = radius / 2; x < source.width() - radius / 2; x++)
		{
			std::vector<pixel> pixels;
			for (int j = -radius / 2; j <= radius / 2; j++)
			{
				for (int i = -radius / 2; i <= radius / 2; i++)
				{
					xx = clampp(x + i, source.width() - 1, 0);
					yy = clampp(y - j, source.height() - 1, 0);
					bright = source.pixelColor(xx, yy).red() + source.pixelColor(xx, yy).green() + source.pixelColor(xx, yy).blue();
					pixels.push_back({ xx, yy, bright });
				}
			}
			std::sort(pixels.begin(), pixels.end(), [](pixel a, pixel b) {return a.rgb < b.rgb; });
			pixel mediana = pixels[(radius * radius) / 2];

			result.setPixelColor(x, y, source.pixelColor(mediana.x, mediana.y));
		}
	}
}



void main(int argc, char* argv[])
{
	string s;
	QImage img;

	for (int i = 0; i < argc; i++)
	{
		if (!strcmp(argv[i], "-p") && (i + 1 < argc))
		{
			s = argv[i + 1];
		}
	}
	img.load(QString(s.c_str()));
	img.save("Images/Source.png");

	QImage result;


	//InvertFilter invert;
	//invert.process(img).save("Images/Invert.png");

	//BlurFilter bl(10);
	//bl.process(img).save("Images/bl.png");

	//GaussianFilter Gauss(10,12);
	//Gauss.process(img).save("Images/Gauss.png");

	//GrayScaleFilter Gray;
	//Gray.process(img).save("Images/Gray.png");

	//SepiyaFilter Sep;
	//Sep.process(img).save("Images/Sep.png");

	//BrightnessFilter Bright;
	//Bright.process(img).save("Images/Bright.png");

	//SobelFilter Sobel;
	//Sobel.process(img).save("Images/Sobel.png");

	//SharpnessFilter Sharp;
	//Sharp.process(img).save("Images/Sharp.png");

	//GrayWorldFilter GrayW;
	//GrayW.process(img).save("Images/GrayW.png");

	//LinearTensionFilter Linear;
	//Linear.process(img).save("Images/Linear.png");

	//TurnFilter Turn;
	//Turn.process(img).save("Images/Turn.png");

	//WavesFilter Waves;
	//Waves.process(img).save("Images/Waves.png");

	//GlassFilter Glass;
	//Glass.process(img).save("Images/Glass.png");

	//MotionBlurFilter MotBlur(10);
	//MotBlur.process(img).save("Images/MotBlur.png");

	//SharpnessLastFilter SharpLast;
	//SharpLast.process(img).save("Images/SharpLast.png");

	//SharraFilter Sharra;
	//Sharra.process(img).save("Images/Sharra.png");

	//PrewittaFilter Prewitta;
	//Prewitta.process(img).save("Images/Prewitta.png");

	//Dilation(img, result);
	//result.save("Images/Dilation.png");

	//Erosion(img, result);
	//result.save("Images/Erosion.png");

	//Opening(img, result);
	//result.save("Images/Opening.png");
	
	//Closing(img, result);
	//result.save("Images/Closing.png");

	//Grad(img, result);
	//result.save("Images/Grad.png");

	//TopHat(img, result);
	//result.save("Images/TopHat.png");

	//BlackHat(img, result);
	//result.save("Images/BlackHat.png");

}
