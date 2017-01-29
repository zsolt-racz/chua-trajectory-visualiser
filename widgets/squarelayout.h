#ifndef SQUARELAYOUT_H
#define SQUARELAYOUT_H

#include<QVBoxLayout>

class SquareLayout : public QVBoxLayout
{
public:
    SquareLayout();

    virtual int heightForWidth(int w) const;
    virtual bool hasHeightForWidth() const;
};

#endif // SQUARELAYOUT_H
