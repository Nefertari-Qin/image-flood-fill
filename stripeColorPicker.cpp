#include "stripeColorPicker.h"

stripeColorPicker::stripeColorPicker(HSLAPixel fillColor, int stripeSpacing)
{
	color = fillColor;
	spacing = stripeSpacing;
}

HSLAPixel stripeColorPicker::operator()(int x, int y) {
	HSLAPixel ret;
	if(x % spacing == 0){
		ret = color;
	} else {
		ret = HSLAPixel(0, 0, 1);
	}

	return ret;
}
