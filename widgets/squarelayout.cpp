#include "squarelayout.h"

SquareLayout::SquareLayout()
{

}


int SquareLayout::heightForWidth(int w) const{
    return w;
}
bool SquareLayout::hasHeightForWidth() const{
    return true;
}
