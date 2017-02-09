
#ifndef MENGER_H_
#define MENGER_H_

#include <stdint.h>
#include "bmp.h"

typedef struct          s_square
{
    int                 easterEgg;
    int                 posx;
    int                 posy;
    int                 size;
    uint32_t            color;
    struct  s_square    *children[8];
    void                (*write)(struct s_square *this, File *file);
}                       Square;

void    Square_write(Square *this, File *file);

Square  *Square_new(int posx, int posy, int size, int leftLevels, int easterEgg);

#endif