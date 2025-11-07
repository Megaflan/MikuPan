#ifndef GRAPHICS_GRAPH2D_SPRT_H
#define GRAPHICS_GRAPH2D_SPRT_H

#include "typedefs.h"

typedef struct {
	u_long tex0;
    /// Shifts the image content within the texture's frame on the x
	u_short u;

    /// Shifts the image content within the texture's frame on the y
	u_short v;
	u_short w; /// Width of the frame for the texture
	u_short h; /// Height of the frame for the texture
	int x; /// Absolute X coordinate of the texture's (upper-left corner) on the screen
	int y; /// Absolute Y coordinate of the texture's (upper-left corner) on the screen
	int pri;
	u_char alpha;
} SPRT_DAT;

typedef struct {
	short int u; /// Shifts the image content within the texture's frame on the x
	short int v; /// Shifts the image content within the texture's frame on the y
	short int w; /// Width of the frame for the texture
	short int h; /// Height of the frame for the texture
	short int x; /// Absolute X coordinate of the texture's (upper-left corner) on the screen
	short int y; /// Absolute Y coordinate of the texture's (upper-left corner) on the screen
	u_char pri;
	u_char alp;
} SPRT_SDAT;

typedef struct {
	short int cx;
	short int cy;
	float rot;
} SPRT_SROT;

typedef struct {
	short int cx;
	short int cy;
	short int sw;
	short int sh;
} SPRT_SSCL;

typedef struct {
	u_int att;

    /// Shifts the image content within the texture's frame on the x
	u_int u;

    /// Shifts the image content within the texture's frame on the y
	u_int v;

    /// Width of the frame for the texture
	u_int w;

    /// Height of the frame for the texture
	u_int h;
	float crx;
	float cry;
	float csx;
	float csy;

    /// Absolute X coordinate of the texture's (upper-left corner) on the screen
	float x;

    /// Absolute Y coordinate of the texture's (upper-left corner) on the screen
	float y;
	u_int z;
	float scw;
	float sch;
	float rot;
	u_long gftg;
	u_long tex0;
	u_long tex1;
	u_long texa;
	u_long alphar;
	u_long zbuf;
	u_long test;
	u_int pri;
	u_char r;
	u_char g;
	u_char b;
	u_char alpha;
	u_char col;
} DISP_SPRT;

#endif // GRAPHICS_GRAPH2D_SPRT_H
