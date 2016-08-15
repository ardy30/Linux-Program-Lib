#ifndef __BASIC_STRUCT_H__
#define __BASIC_STRUCT_H__

#include <stdint.h>

typedef struct tag_Header 
{
	uint32_t cmd;
	uint32_t length;
	uint32_t error;
	uint32_t para1;
	uint32_t para2;
} Header;


#endif
