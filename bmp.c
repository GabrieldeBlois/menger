#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>

#include "bmp.h"
#include "menger.h"

void File_draw(File *this, unsigned int posx, unsigned int posy,
               uint32_t color) {
  if (posx < this->fileWidth && posy < this->fileWidth)
    this->picture[posx + posy * this->fileWidth] = color;
}

void make_bmp_header(t_bmp_header *header, size_t size) {
  uint32_t offset = sizeof(t_bmp_header) + sizeof(t_bmp_info_header);

  header->magic = (uint16_t)((0x424D >> 8) | (0x424D << 8));
  header->size = (uint32_t)(size * size * 4) + offset;
  header->_app1 = 0;
  header->_app2 = 0;
  header->offset = offset;
}

void make_bmp_info_header(t_bmp_info_header *header, size_t size) {
  header->size = 40;
  header->width = (uint32_t)size;
  header->height = size;
  header->planes = 1;
  header->bpp = 32;
  header->compression = 0;
  header->raw_data_size = (uint32_t)(size * size * sizeof(uint32_t));
  header->h_resolution = 0;
  header->v_resolution = 0;
  header->palette_size = 0;
  header->important_colors = 0;
}

File *File_new(unsigned int fileWidth, const char *fileName) {
  File *tmp = malloc(sizeof(*tmp));
  if (!tmp)
    return (NULL);
  tmp->picture = calloc(fileWidth * fileWidth, sizeof(uint32_t));
  printf("allocation de %d * %d * 4 = %d\n", fileWidth, fileWidth,
         fileWidth * fileWidth * 4);
  if (!tmp->picture)
    return (NULL);

  tmp->fileWidth = fileWidth;

  tmp->draw = &File_draw;
  tmp->write = &File_write;

  tmp->fileName = fileName;
  make_bmp_header(&tmp->header, fileWidth);
  make_bmp_info_header(&tmp->info_header, fileWidth);
  return (tmp);
}

void File_del(File *this) {
  if (!this)
    return;
  free(this->picture);
  free(this);
}

void File_write(File *this) {
  int fd = 0;

  if ((fd = open(this->fileName, O_CREAT | O_TRUNC | O_WRONLY, 0644)) < 0)
    exit(84);

  if (write(fd, &this->header, sizeof(this->header)) < 0) {
    perror("write");
    exit(EXIT_FAILURE);
  }

  if (write(fd, &this->info_header, sizeof(this->info_header)) < 0) {
    perror("write");
    exit(EXIT_FAILURE);
  }
  for (unsigned int i = 0; i < this->fileWidth * this->fileWidth; i++) {
    if (write(fd, &this->picture[i], sizeof(uint32_t)) < 0) {
        perror("write");
        exit(EXIT_FAILURE);
    }
  }
  // write(fd, this->picture, this->fileWidth * this->fileWidth *
  // sizeof(uint32_t));
  close(fd);
}