#pragma once
#include <QImage>


class Filter
{
protected:
	virtual QColor calcNewPixelColor(const QImage& img, int x, int y) const = 0;
public:
	virtual ~Filter() = default;
	virtual QImage process(const QImage& img) const;
};

//------------------------------------------------------------------------------\\

class InvertFilter : public Filter
{
	QColor calcNewPixelColor(const QImage& img, int x, int y) const override;
};

//------------------------------------------------------------------------------\\
//Оттенки серого

class GrayScaleFilter : public Filter
{
	QColor calcNewPixelColor(const QImage& img, int x, int y) const override;
};

//------------------------------------------------------------------------------\\
//Сепия(песочно-коричневый оттенок)

class SepiyaFilter : public Filter
{
	QColor calcNewPixelColor(const QImage& img, int x, int y) const override;
};

//------------------------------------------------------------------------------\\
//Яркость

class BrightnessFilter : public Filter
{
	QColor calcNewPixelColor(const QImage& img, int x, int y) const override;
};

//------------------------------------------------------------------------------\\
//Серый мир

class GrayWorldFilter : public Filter
{
	QColor calcNewPixelColor(const QImage& img, int x, int y) const override;
};

//------------------------------------------------------------------------------\\
//Линейное растяжение

class LinearTensionFilter : public Filter
{
	QColor calcNewPixelColor(const QImage& img, int x, int y) const override;
public:
	virtual QImage process(const QImage& img) const override;
};

//------------------------------------------------------------------------------\\
//Поворот

class TurnFilter : public Filter
{
	QColor calcNewPixelColor(const QImage& img, int x, int y) const override;
};

//------------------------------------------------------------------------------\\
//Волны

class WavesFilter : public Filter
{
	QColor calcNewPixelColor(const QImage& img, int x, int y) const override;
};

//------------------------------------------------------------------------------\\
//Стекло

class GlassFilter : public Filter
{
	QColor calcNewPixelColor(const QImage& img, int x, int y) const override;
};








class Kernel
{
protected:
	// данные ядра
	std::unique_ptr<float[] > data;
	// радиус ядра
	std::size_t radius;
	// размер памяти ядра
	std::size_t getLen() const 
	{
		return getSize() * getSize();
	}

public:
	// конструктор пустого ядра
	Kernel(std::size_t radius) : radius(radius)
	{
		// выделение памяти под массив
		data = std::make_unique<float[] >(getLen());
	}

	// конструктор копирования
	Kernel(const Kernel& other): Kernel(other.radius)
	{
		std::copy(other.data.get(), other.data.get() + getLen(), data.get());
	}

	//аксессора
	std::size_t getRadius() const
	{
		return radius;
	}
	std::size_t getSize() const
	{
		return 2 * radius + 1;
	}
	float operator [] (std::size_t id) const
	{
		return data[id];
	}
	float& operator [] (std::size_t id)
	{
		return data[id];
	}
};

class MatrixFilter : public Filter
{
protected:
	// хранится по значению, потому что внутри Kernel содержится указатель
	Kernel mKernel;
	QColor calcNewPixelColor(const QImage& img, int x, int y) const override;

public:
	MatrixFilter(const Kernel& kernel) : mKernel(kernel) {};
	virtual ~MatrixFilter() = default;
};

//------------------------------------------------------------------------------\\
//Размытие

class BlurKernel : public Kernel
{
public:
	using Kernel::Kernel;
	BlurKernel(std::size_t radius = 2) : Kernel(radius)
	{
		for (std::size_t i = 0; i < getLen(); i++)
			data[i] = 1.0f / getLen();
	}
};

class BlurFilter : public MatrixFilter
{
public:
	BlurFilter(std::size_t radius = 1) : MatrixFilter(BlurKernel(radius)) {}
};

//------------------------------------------------------------------------------\\
//Гаусс

class GaussianKernel: public Kernel
{
public:
	//Наследование конструкторов
	using Kernel::Kernel;
	GaussianKernel(std::size_t radius = 2, float sigma = 3.f) : Kernel(radius)
	{
		//коэффициент нормировки ядра
		float norm = 0;
		int signed_radius = static_cast<int>(radius);
		//расситываем ядро линейного фильтра
		for (int x = -signed_radius; x <= signed_radius; x++)
			for (int y = -signed_radius; y <= signed_radius; y++)
			{
				std::size_t idx = (x + radius) * getSize() + (y + radius);
				data[idx] = std::exp(-(x * x + y * y) / (sigma * sigma));
				norm += data[idx];
			}

		//нормируем ядро
		for (std::size_t i = 0; i < getLen(); i++)
		{
			data[i] /= norm;
		}
	}
};

class GaussianFilter: public MatrixFilter
{
public:
	GaussianFilter(std::size_t radius = 1, float sigma = 3.f) : MatrixFilter(GaussianKernel(radius, sigma)) {}
};

//------------------------------------------------------------------------------\\
//Собель

class SobelKernal : public Kernel
{
public:
	using Kernel::Kernel;
	SobelKernal(std::size_t radius = 1) : Kernel(radius)
	{
		data[0] = -1;
		data[1] = -2;
		data[2] = -1;

		data[3] = 0;
		data[4] = 0;
		data[5] = 0;

		data[6] = 1;
		data[7] = 2;
		data[8] = 1;
	}
};

class SobelFilter : public MatrixFilter
{
public:
	SobelFilter(std::size_t radius = 1) : MatrixFilter(SobelKernal(radius)) {}
};

//------------------------------------------------------------------------------\\
//Резкость

class SharpnessKernal : public Kernel
{
public:
	using Kernel::Kernel;
	SharpnessKernal(std::size_t radius = 2) : Kernel(radius)
	{
		data[0] = 0;
		data[1] = -1;
		data[2] = 0;

		data[3] = -1;
		data[4] = 5;
		data[5] = -1;

		data[6] = 0;
		data[7] = -1;
		data[8] = 0;
	}
};

class SharpnessFilter : public MatrixFilter
{
public:
	SharpnessFilter(std::size_t radius = 1) : MatrixFilter(SharpnessKernal(radius)) {}
};

//------------------------------------------------------------------------------\\
//Размытие в движении

class MotionBlurKernal : public Kernel
{
public:
	using Kernel::Kernel;
	MotionBlurKernal(std::size_t radius = 2) : Kernel(radius)
	{
		data[0] = (float)1 / 5;
		data[1] = 0;
		data[2] = 0;
		data[3] = 0;
		data[4] = 0;

		data[5] = 0;
		data[6] = (float)1 / 5;
		data[7] = 0;
		data[8] = 0;
		data[9] = 0;

		data[10] = 0;
		data[11] = 0;
		data[12] = (float)1 / 5;
		data[13] = 0;
		data[14] = 0;

		data[15] = 0;
		data[16] = 0;
		data[17] = 0;
		data[18] = (float)1 / 5;
		data[19] = 0;

		data[20] = 0;
		data[21] = 0;
		data[22] = 0;
		data[23] = 0;
		data[24] = (float)1 / 5;
	}
};

class MotionBlurFilter : public MatrixFilter
{
public:
	MotionBlurFilter(std::size_t radius = 2) : MatrixFilter(MotionBlurKernal(radius)) {}
};

//------------------------------------------------------------------------------\\
//Резкость Последняя

class SharpnessLastKernal : public Kernel
{
public:
	using Kernel::Kernel;
	SharpnessLastKernal(std::size_t radius = 2) : Kernel(radius)
	{
		data[0] = -1;
		data[1] = -1;
		data[2] = -1;

		data[3] = -1;
		data[4] = 9;
		data[5] = -1;

		data[6] = -1;
		data[7] = -1;
		data[8] = -1;
	}
};

class SharpnessLastFilter : public MatrixFilter
{
public:
	SharpnessLastFilter(std::size_t radius = 1) : MatrixFilter(SharpnessLastKernal(radius)) {}
};

//------------------------------------------------------------------------------\\
//Выделение границ(оператор Щарра)

class SharraKernal : public Kernel
{
public:
	using Kernel::Kernel;
	SharraKernal(std::size_t radius = 2) : Kernel(radius)
	{
		data[0] = 3;
		data[1] = 10;
		data[2] = 3;

		data[3] = 0;
		data[4] = 0;
		data[5] = 0;

		data[6] = -3;
		data[7] = -10;
		data[8] = -3;
	}
};

class SharraFilter : public MatrixFilter
{
public:
	SharraFilter(std::size_t radius = 1) : MatrixFilter(SharraKernal(radius)) {}
};

//------------------------------------------------------------------------------\\
//Выделение границ(оператор Прюитта)

class PrewittaKernal : public Kernel
{
public:
	using Kernel::Kernel;
	PrewittaKernal(std::size_t radius = 2) : Kernel(radius)
	{
		data[0] = -1;
		data[1] = -1;
		data[2] = -1;

		data[3] = 0;
		data[4] = 0;
		data[5] = 0;

		data[6] = 1;
		data[7] = 1;
		data[8] = 1;
	}
};

class PrewittaFilter : public MatrixFilter
{
public:
	PrewittaFilter(std::size_t radius = 1) : MatrixFilter(PrewittaKernal(radius)) {}
};