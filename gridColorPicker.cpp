#include "gridColorPicker.h"

gridColorPicker::gridColorPicker(HSLAPixel gridColor, int gridSpacing) {
    color = gridColor;
    spacing = gridSpacing;
}

HSLAPixel gridColorPicker::operator()(int x, int y) {
    if ((x - y) % spacing == 0 || (x + y) % spacing == 0) 
    	return color;
    return HSLAPixel(0, 0, 1);
}
