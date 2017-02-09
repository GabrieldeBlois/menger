#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"
#include "menger.h"

int main(int ac, char **av) {
  if (ac != 5)
    return (fprintf(stderr, "usage: %s [fileName] [size] [level] [easterEgg]\n",
                    av[0]));
  const char *fileName = av[1];
  int size = atoi(av[2]);
  int level = atoi(av[3]);
  int easterEgg = atoi(av[4]);

  easterEgg %= 9;
  File *file = File_new(size, fileName);
  Square *square = Square_new(0, 0, size, level, easterEgg);
  square->write(square, file);
  file->write(file);
}