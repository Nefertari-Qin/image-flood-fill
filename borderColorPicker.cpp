#include <cmath>
#include "borderColorPicker.h"

borderColorPicker::borderColorPicker(HSLAPixel fillColor, PNG & img, double tolerance, HSLAPixel center) {   
	color = fillColor;
    im = img;
    tol = tolerance;
    ctr = center;
}

HSLAPixel borderColorPicker::operator()(int x, int y) {
    if (isBorderOfIMG(im, x, y)) return color;    // the border of the image

	for (int i = x - 3; i <= x + 3; i++) {
        for (int j = y - 3; j <= y + 3; j++) {
            if (pow((double) (i - x), 2) + pow((double) (j - y), 2) <= 9.0 &&    // within 3 pixel
                isInsideIMG(im, i, j)) { 
                if (ctr.dist(*(im.getPixel((unsigned int) i, (unsigned int) j))) > tol) // if any near pixel is out of tol
                    return color;                                                       // return fillColor
            }
        }
    }

	return *(im.getPixel((unsigned int) x, (unsigned int) y)); //the current color of (x,y) will be returned.
}

bool borderColorPicker::isInsideIMG(PNG& img, int x, int y) {
    return ((0 <= (unsigned) x && (unsigned) x < img.width()) &&
            (0 <= (unsigned) y && (unsigned) y < img.height()));
}

bool borderColorPicker::isBorderOfIMG(PNG& img, int x, int y) {    
    return (0 <= x && x <3) || (0 <= y && y <3) ||
    (img.width() - 3 <= (unsigned) x && (unsigned) x < img.width()) ||
    (img.width() - 3 <= (unsigned) y && (unsigned) y < img.width());
}
