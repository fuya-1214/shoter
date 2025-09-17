#pragma once
#include <Siv3D.hpp>

class b
{
public:
	b() {};

	void draw() const
	{
		Box{ 5.5,0,5,10 }.draw(ColorF{ 0.8, 0.6, 0.4 }.removeSRGBCurve());
		Box{ -5.5,0,5,10 }.draw(ColorF{ 0.8, 0.6, 0.4 }.removeSRGBCurve());
	}
private:

};

