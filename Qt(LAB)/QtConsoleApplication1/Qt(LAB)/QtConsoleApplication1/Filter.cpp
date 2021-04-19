#include "Filter.h"
#define PI 3.14159265

template <class T>
T clamp(T value, T max, T min)
{
	if (value > max)
		return max;
	if (value < min)
		return min;
	return value;
}

QImage Filter::process(const QImage& img) const
{
	QImage result(img);

	for (int x = 0; x < img.width(); x++)
		for (int y = 0; y < img.height(); y++)
		{
			QColor color = calcNewPixelColor(img, x, y);
			result.setPixelColor(x, y, color);
		}
	return result;
}

QColor InvertFilter::calcNewPixelColor(const QImage& img, int x, int y) const
{
	QColor color = img.pixelColor(x, y);
	color.setRgb(255 - color.red(), 255 - color.green(), 255 - color.blue());
	return color;
}

QColor GrayScaleFilter::calcNewPixelColor(const QImage& img, int x, int y) const
{
	QColor color = img.pixelColor(x, y);
	color.setRgb(0.299 * color.red() + 0.587 * color.green() + 0.114 * color.blue(), 0.299 * color.red() + 0.587 * color.green() + 0.114 * color.blue(), 0.299 * color.red() + 0.587 * color.green() + 0.114 * color.blue());
	return color;
}

QColor SepiyaFilter::calcNewPixelColor(const QImage& img, int x, int y) const
{
	QColor color = img.pixelColor(x, y);
	int k = 30;
	color.setRgb(clamp((0.299 * color.red() + 0.587 * color.green() + 0.114 * color.blue()) + 2 * k, 255. ,0.), clamp((0.299 * color.red() + 0.587 * color.green() + 0.114 * color.blue()) + 0.5 * k, 255., 0.), clamp(((0.299 * color.red() + 0.587 * color.green() + 0.114 * color.blue()) - 1 * k), 255., 0.));
	return color;
}

QColor BrightnessFilter::calcNewPixelColor(const QImage& img, int x, int y) const
{
	QColor color = img.pixelColor(x, y);
	int k = 70;
	color.setRgb(clamp(color.red() + k, 255, 0), clamp(color.green() + k, 255, 0), clamp(color.blue() + k, 255, 0));
	return color;
}

QColor GrayWorldFilter::calcNewPixelColor(const QImage& img, int x, int y) const
{
	QColor color = img.pixelColor(x, y);
	color.setRgb((color.red() + color.green() + color.blue()) / 3, (color.red() + color.green() + color.blue()) / 3, (color.red() + color.green() + color.blue()) / 3);
	return color;
}


QColor LinearTensionFilter::calcNewPixelColor(const QImage& img, int x, int y) const
{
    return QColor();
}

QImage LinearTensionFilter::process(const QImage& img) const
{
    QImage result(img);
    int RedMax = 0, GreenMax = 0, BlueMax = 0;
    int RedMin = 255, GreenMin = 255, BlueMin = 255;
    for (int x = 0; x < img.width(); x++)
    {
        for (int y = 0; y < img.height(); y++)
        {
            QColor color = img.pixelColor(x, y);
            if (color.red() > RedMax)
            {
                RedMax = color.red();
            }
            if (color.green() > GreenMax)
            {
                GreenMax = color.green();
            }
            if (color.blue() > BlueMax)
            {
                BlueMax = color.blue();
            }

            if (color.red() < RedMin)
            {
                RedMin = color.red();
            }
            if (color.green() < GreenMin)
            {
                GreenMin = color.green();
            }
            if (color.blue() < BlueMin)
            {
                BlueMin = color.blue();
            }
        }
    }

    for (int x = 0; x < img.width(); x++)
    {
        for (int y = 0; y < img.height(); y++)
        {
            QColor color = img.pixelColor(x, y);

            color.setRgb(clamp((color.red() - RedMin) * (255 - 0)/(RedMax - RedMin), 255, 0), clamp((color.green() - GreenMin) * (255 - 0) / (GreenMax - GreenMin), 255, 0), clamp((color.blue() - BlueMin) * (255 - 0) / (BlueMax - BlueMin), 255, 0));

            result.setPixelColor(x, y, color);
        }
    }
    return result;

}


QColor TurnFilter::calcNewPixelColor(const QImage& img, int x, int y) const
{
	//Центр поворота
	int xCenter = img.width() / 2;
	int yCenter = img.height() / 2;
	//угол поворота
	float u = PI / 6;
	int newX = (x - xCenter) * cos(u) - (y - yCenter) * sin(u) + xCenter;
	int newY = (x - xCenter) * sin(u) + (y - yCenter) * cos(u) + yCenter;

	if (newX < img.width() && newX > 0 && newY < img.height() && newY > 0)
	{
		return img.pixelColor(newX, newY);
	}
	else
	{
		return QColor(0, 0, 0);
	}
}

QColor WavesFilter::calcNewPixelColor(const QImage& img, int x, int y) const
{
	//1
	float u = 2 * PI * y / 60;
	int newX = clamp((int)(x + 20 * sin(u)), img.height() - 1, 0);
	int newY = y;
	return img.pixelColor(newX, newY);

	//2
	//float u = 2*PI*x / 30;
	//int newX = clamp((int)(x + 20 * sin(u)), img.width() - 1, 0);
	//int newY = y;
	//return img.pixelColor(newX, newY);
}

QColor GlassFilter::calcNewPixelColor(const QImage& img, int x, int y) const
{
	double random_0_to_1 = rand() % 11 / 10.f;

	int newX = clamp((float)(x + (random_0_to_1 - 0.5) * 10), (float)(img.width() - 1), 0.f);
	int newY = clamp((float)(y + (random_0_to_1 - 0.5) * 10), (float)(img.height() - 1), 0.f);

	return img.pixelColor(newX, newY);
}


QColor MatrixFilter::calcNewPixelColor(const QImage& img, int x, int y) const
{
	float returnR = 0;
	float returnG = 0;
	float returnB = 0;
	int size = mKernel.getSize();
	int radius = mKernel.getRadius();
	for (int i =  -radius; i <= radius; i++)
		for (int j = -radius; j <= radius; j++)
		{
			int idx = (i + radius) * size + j + radius;

			QColor color = img.pixelColor(clamp(x + j, img.width() - 1, 0), clamp(y + i, img.height() - 1, 0));

			returnR += color.red() * mKernel[idx];
			returnG += color.green() * mKernel[idx];
			returnB += color.blue() * mKernel[idx];
		}

	return QColor(clamp(returnR, 255.f, 0.f), clamp(returnG, 255.f, 0.f), clamp(returnB, 255.f, 0.f));
}
