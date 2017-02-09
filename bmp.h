/*
** bitmap.h for bitmap in /home/gaby/Documents/dev/
**
** Made by John Doe
** Login   <login_x@epitech.eu>
**
** Started on  Wed Jan  4 15:28:12 2017 John Doe
** Last update Wed Jan  4 16:37:38 2017 John Doe
*/

#ifndef BITMAP_H_
#define BITMAP_H_

#include <stdint.h>
#include <stdlib.h>

typedef struct __attribute__((packed)) s_bmp_header {
  uint16_t magic;
  uint32_t size;
  int16_t _app1;
  int16_t _app2;
  uint32_t offset;
} t_bmp_header;

typedef struct __attribute__((packed)) s_bmp_info_header {
  uint32_t size;
  int32_t width;
  int32_t height;
  uint16_t planes;
  uint16_t bpp;
  uint32_t compression;
  uint32_t raw_data_size;
  int32_t h_resolution;
  int32_t v_resolution;
  uint32_t palette_size;
  uint32_t important_colors;
} t_bmp_info_header;

void make_bmp_header(t_bmp_header *header, size_t size);

void make_bmp_info_header(t_bmp_info_header *header, size_t size);

typedef struct s_file {
  const char *fileName;
  unsigned int fileWidth;
  uint32_t *picture;
  t_bmp_header header;
  t_bmp_info_header info_header;
  void (*draw)(struct s_file *this, unsigned int posx, unsigned int posy,
               uint32_t color);
  void (*write)(struct s_file *this);
} File;

void File_draw(File *this, unsigned int posx, unsigned int posy,
               uint32_t color);

File *File_new(unsigned int fileWidth, const char *fileName);

void File_del(File *this);

void File_write(File *this);

#endif
