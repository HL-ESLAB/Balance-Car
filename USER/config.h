#ifndef __CONFIG_H
#define __CONFIG_H

#include "sys.h"

#define PI 3.1415926

typedef struct
{
	char x;
	char y;
	char z;
}xyz_char_t;

typedef struct
{
	int16_t x;
	int16_t y;
	int16_t z;
}xyz_int16_t;

typedef struct
{
	float x;
	float	y;
	float z;

}xyz_f_t;

typedef struct
{
	u32 x;
	u32 y;
	u32 z;
}xyz_u32_t;



#endif
