#include <QtCore/QCoreApplication>
#include <QImage>
using namespace std;
#include "Filter.h"

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
}
