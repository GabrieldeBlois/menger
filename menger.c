#include "menger.h"
#include "bmp.h"
#include <stdio.h>
#include <stdlib.h>

typedef union u_color {
  uint32_t colorHex;
  char argb[4];
} Color;

Square *Square_new(int posx, int posy, int size, int leftLevels,
                   int easterEgg) {
  Square *tmp = malloc(sizeof(*tmp));
  if (tmp == NULL)
    return (NULL);
  tmp->posx = posx;
  tmp->posy = posy;
  tmp->size = size;
  tmp->easterEgg = easterEgg;
  Color color;
  color.argb[0] = 255;
  color.argb[1] = 255;
  color.argb[2] = 255;
  color.argb[3] = 255;

  if (leftLevels == 0)
    tmp->color = color.colorHex;
  else {
    for (int i = 1; i < 4; i++)
      color.argb[i] = 255 / (leftLevels);
    tmp->color = color.colorHex;
  }

  if (leftLevels > 0) {
    int newSize = size / 3;
    int newLevel = leftLevels - 1;

    int k = 0;
    for (int i = 0; i < 9; i++) {
      if (i != easterEgg) {
        tmp->children[k] =
            Square_new(posx + (newSize * (i % 3)), posy + newSize * (i / 3),
                       newSize, newLevel, easterEgg);
        k++;
      }
    }
  } else {
    for (int i = 0; i < 8; i++)
      tmp->children[i] = NULL;
  }
  tmp->write = &Square_write;
  return (tmp);
}

void Square_write(Square *this, File *file) {
  unsigned int newSize = this->size / 3;
  unsigned int origX = this->posx + (newSize * (this->easterEgg % 3));
  unsigned int origY = this->posy + (newSize * (this->easterEgg / 3));

  for (unsigned int i = origX; i < origX + newSize; i++) {
    for (unsigned int j = origY; j < origY + newSize; j++) {
      file->picture[j * file->fileWidth + i] = this->color;
    }
  }
  for (int i = 0; i < 8; i++) {
    if (this->children[i])
      this->children[i]->write(this->children[i], file);
  }
}