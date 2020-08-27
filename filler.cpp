/**
 * @file filler.cpp
 * Implementation of functions in the filler namespace. 
 *
 */
#include "filler.h"


animation filler::fillStripeDFS(PNG& img, int x, int y, HSLAPixel fillColor,
                                int stripeSpacing, double tolerance, int frameFreq)
{
    stripeColorPicker scp = stripeColorPicker(fillColor, stripeSpacing);
    return fill<Stack>(img, x, y, scp, tolerance, frameFreq);
}

animation filler::fillStripeBFS(PNG& img, int x, int y, HSLAPixel fillColor,
                                int stripeSpacing, double tolerance, int frameFreq)
{

    stripeColorPicker scp = stripeColorPicker(fillColor, stripeSpacing);
    return fill<Queue>(img, x, y, scp, tolerance, frameFreq);
}



animation filler::fillBorderDFS(PNG& img, int x, int y,
                                    HSLAPixel borderColor, double tolerance, int frameFreq)
{
    borderColorPicker bcp = borderColorPicker(borderColor, img, tolerance, *(img.getPixel(img.width()/2,  img.height()/2)));
    return fill<Stack>(img, x, y, bcp, tolerance, frameFreq);
}

animation filler::fillBorderBFS(PNG& img, int x, int y,
                                    HSLAPixel borderColor, double tolerance, int frameFreq)
{
    borderColorPicker bcp = borderColorPicker(borderColor, img, tolerance, *(img.getPixel(img.width()/2,  img.height()/2)));
    return fill<Queue>(img, x, y, bcp, tolerance, frameFreq);
}



animation filler::fillConwayDFS(PNG& img, int x, int y, double tolerance, int frameFreq)
{
    conwayColorPicker ccp = conwayColorPicker();
    return fill<Stack>(img, x, y, ccp, tolerance, frameFreq);
}

animation filler::fillConwayBFS(PNG& img, int x, int y, double tolerance, int frameFreq) {   
    conwayColorPicker ccp = conwayColorPicker();
    return fill<Queue>(img, x, y, ccp, tolerance, frameFreq);
}



animation filler::fillGridDFS(PNG& img, int x, int y, HSLAPixel fillColor,
                                int spacing, double tolerance, int frameFreq)
{
    gridColorPicker gcp = gridColorPicker(fillColor, spacing);
    return fill<Stack>(img, x, y, gcp, tolerance, frameFreq);
}

animation filler::fillGridBFS(PNG& img, int x, int y, HSLAPixel fillColor,
                                int spacing, double tolerance, int frameFreq)
{
    gridColorPicker gcp = gridColorPicker(fillColor, spacing);
    return fill<Queue>(img, x, y, gcp, tolerance, frameFreq);
}

template <template <class T> class OrderingStructure>
animation filler::fill(PNG& img, int x, int y, colorPicker& fillColor,
                       double tolerance, int frameFreq)
{
    animation theAnim;
    int freq = 0;
    vector<vector<bool>> visited(img.width(), vector<bool>(img.height(), false)); // path list acc 

    OrderingStructure<HSLAXYPixel> todo;     // todo list acc
    HSLAPixel ctr(*(img.getPixel(x, y)));
    visited[x][y] = true;
    todo.add(HSLAXYPixel(img.getPixel(x, y), x, y));

    while (!todo.isEmpty()) {
        HSLAXYPixel xypxl = todo.remove();
        HSLAPixel *pxlPtr = xypxl.pxptr;
        unsigned crntX = xypxl.x;
        unsigned crntY = xypxl.y;

        *pxlPtr = fillColor(crntX, crntY);

        // South:
        crntY++;
        addPixelIfUnvisited(img, crntX, crntY, ctr, tolerance, todo, visited);

        // East:
        crntY--;
        crntX++;
        addPixelIfUnvisited(img, crntX, crntY, ctr, tolerance, todo, visited);

        // North:
        crntY--;
        crntX--;
        addPixelIfUnvisited(img, crntX, crntY, ctr, tolerance, todo, visited);
        
        // West:
        crntY++;
        crntX--;
        addPixelIfUnvisited(img, crntX, crntY, ctr, tolerance, todo, visited);


        freq++;
        if (freq >= frameFreq) {
            theAnim.addFrame(img);
            freq = 0;
        }
    }
    theAnim.addFrame(img);
    return theAnim;
} 

bool filler::isInsideIMG(PNG& img, int x, int y) {
    return ((0 <= (unsigned) x && (unsigned) x < img.width()) &&
            (0 <= (unsigned) y && (unsigned) y < img.height()));
}

bool filler::isWithinTolerance(PNG& img, HSLAPixel & ctr, int i, int j, double tol) {
    return (ctr.dist(*(img.getPixel((unsigned int) i, (unsigned int) j))) <= tol);
}

void filler::addPixelIfUnvisited(PNG& img, int x, int y, HSLAPixel & ctr, 
                                    double tol, OrderingStructure<HSLAXYPixel>& todo, 
                                    vector<vector<bool>>& visited)
{
    if (isInsideIMG(img, x, y) && !visited[x][y] && isWithinTolerance(img, ctr, x, y, tol)){
            visited[x][y] = true;
            todo.add(HSLAXYPixel(img.getPixel(x, y), x, y));
        }
}
    /** FOR ABOVE fill
     * @todo You need to implement this function!
     *
     * This is the basic description of a flood-fill algorithm: Every fill
     * algorithm requires an ordering structure, which is passed to this
     * function via its template parameter. For a breadth-first-search
     * fill, that structure is a QUEUE, for a depth-first-search, that
     * structure is a STACK.
     * To begin the algorithm, you simply place the
     * given point in the ordering structure, marking it processed
     * (the way you mark it is a design decision you'll make yourself).
     * We have a choice to either change the color, if appropriate, when we
     * add the point to the OS, or when we take it off. In our test cases,
     * we have assumed that you will change the color when a point is REMOVED
     * from the structure.
     *
     * Until the structure is empty, you do the following:
     *
     * 1.     Remove a point from the ordering structure, and then...
     *
     *        1.    add its unprocessed neighbors whose color values are 
     *              within (or equal to) tolerance distance from the center, 
     *              to the ordering structure, marking each as processed.
     *        2.    use the colorPicker to set the new color of the point.
     *        3.    if it is an appropriate frame, send the current PNG to the
     *              animation (as described below).
     *
     * 2.     When implementing your breadth-first-search and
     *        depth-first-search fills, you will need to explore neighboring
     *        pixels in some order.
     *
     *        For this assignment, each pixel p has 4 neighbors, consisting of 
     *        the 4 pixels who share an edge or corner with p. (We leave it to
     *        you to describe those 4 pixel locations, relative to the location
     *        of p.)
     *
     *        While the order in which you examine neighbors does not matter
     *        for a proper fill, you must use the same order as we do for
     *        your animations to come out like ours! 
     *
     *        The order you should put
     *        neighboring pixels **ONTO** the ordering structure (queue or stack) 
     *        is as follows: 
     *          >>> South (y + 1), East (x + 1), North (y - 1), West (x -1) <<<
     *
     *        If you do them in a different order, your fill may
     *        still work correctly, but your animations will be different
     *        from the grading scripts!
     *
     *        IMPORTANT NOTE: *UP*
     *        here means towards the top of the image, so since an image has
     *        smaller y coordinates at the top, this is in the *negative y*
     *        direction. Similarly, *DOWN* means in the *positive y*
     *        direction.  
     *
     * 3.     For every k pixels filled, **starting at the kth pixel**, you
     *        must add a frame to the animation, where k = frameFreq.
     *
     *        For example, if frameFreq is 4, then after the 4th pixel has
     *        been filled you should add a frame to the animation, then again
     *        after the 8th pixel, etc.  You must only add frames for the
     *        number of pixels that have been filled, not the number that
     *        have been checked. So if frameFreq is set to 1, a pixel should
     *        be filled every frame.
     * 4.     Finally, as you leave the function, send one last frame to the
     *        animation. This frame will be the final result of the fill, and 
     *        it will be the one we test against.
     */