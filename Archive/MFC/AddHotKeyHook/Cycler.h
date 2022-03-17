#pragma once

template <class T> class Cycler
{
public:
	Cycler(const std::vector<T>& theV) : v(theV), currentIndex(0)
	{
	}
	T forward(void);
	T backward(void);
	void setCurrentIndex(const T srcValue)
	{
		currentIndex = getIndex(srcValue);
	}
private:
	std::vector<T> v;
	int currentIndex;
	const int getIndex(const T srcValue);
};

template <class T> T Cycler<T>::forward(void)
{
	currentIndex++;
	if (currentIndex >= static_cast<int>(v.size()))
	{
		currentIndex = 0;
	}
	return v[currentIndex];
};

template <class T> T Cycler<T>::backward(void)
{
	currentIndex--;
	if (currentIndex < 0)
	{
		currentIndex = static_cast<int>(v.size()) - 1;
	}
	return v[currentIndex];
};

template <class T> const int Cycler<T>::getIndex(const T srcValue)
{
	for (int i = 0; i < static_cast<int>(v.size()); i++)
	{
		T& value = v[i];
		if (srcValue == value)
		{
			return i;
		}
	}
	return -1;
};
