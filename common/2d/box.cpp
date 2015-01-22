/*
 * Portions of this file are copyright Rebirth contributors and licensed as
 * described in COPYING.txt.
 * Portions of this file are copyright Parallax Software and licensed
 * according to the Parallax license below.
 * See COPYING.txt for license details.

THE COMPUTER CODE CONTAINED HEREIN IS THE SOLE PROPERTY OF PARALLAX
SOFTWARE CORPORATION ("PARALLAX").  PARALLAX, IN DISTRIBUTING THE CODE TO
END-USERS, AND SUBJECT TO ALL OF THE TERMS AND CONDITIONS HEREIN, GRANTS A
ROYALTY-FREE, PERPETUAL LICENSE TO SUCH END-USERS FOR USE BY SUCH END-USERS
IN USING, DISPLAYING,  AND CREATING DERIVATIVE WORKS THEREOF, SO LONG AS
SUCH USE, DISPLAY OR CREATION IS FOR NON-COMMERCIAL, ROYALTY OR REVENUE
FREE PURPOSES.  IN NO EVENT SHALL THE END-USER USE THE COMPUTER CODE
CONTAINED HEREIN FOR REVENUE-BEARING PURPOSES.  THE END-USER UNDERSTANDS
AND AGREES TO THE TERMS HEREIN AND ACCEPTS THE SAME BY USE OF THIS FILE.
COPYRIGHT 1993-1998 PARALLAX SOFTWARE CORPORATION.  ALL RIGHTS RESERVED.
*/

#include <algorithm>
#include "u_mem.h"


#include "gr.h"
#include "grdef.h"

static void gr_ubox0(int left,int top,int right,int bot)
{
	int d;
	unsigned char * ptr2;
	auto ptr1 = &grd_curcanv->cv_bitmap.get_bitmap_data()[ROWSIZE *top+left];
	ptr2 = ptr1;
	d = right - left;

	for (int i=top; i<=bot; i++ )
	{
		ptr2[0] = (unsigned char) COLOR;
		ptr2[d] = (unsigned char) COLOR;
		ptr2 += ROWSIZE;
	}

	ptr2 = ptr1;
	d = (bot - top)*ROWSIZE;

	std::fill_n(ptr2 + 1, (right - left) - 1, COLOR);
	std::fill_n(ptr2 + 1 + d, (right - left) - 1, COLOR);
}

static void gr_box0(int left,int top,int right,int bot)
{
	if (top > MAXY ) return;
    if (bot < MINY ) return;
    if (left > MAXX ) return;
    if (right < MINX ) return;
    
	if (top < MINY) top = MINY;
    if (bot > MAXY ) bot = MAXY;
	if (left < MINX) left = MINX;
    if (right > MAXX ) right = MAXX;

	gr_ubox0(left,top,right,bot);

}


static void gr_ubox12(int left,int top,int right,int bot)
{
#if 0	// the following shifts the box up 1 unit in OpenGL
	for (int i=top; i<=bot; i++ )
	{
		gr_upixel( left, i );
		gr_upixel( right, i );
	}

	for (int i=left; i<=right; i++ )
	{
		gr_upixel( i, top );
		gr_upixel( i, bot );
	}
#endif
	gr_uline(i2f(left), i2f(top), i2f(right), i2f(top));
	gr_uline(i2f(right), i2f(top), i2f(right), i2f(bot));
	gr_uline(i2f(left), i2f(top), i2f(left), i2f(bot));
	gr_uline(i2f(left), i2f(bot), i2f(right), i2f(bot));
}

static void gr_box12(int left,int top,int right,int bot)
{
    if (top > MAXY ) return;
    if (bot < MINY ) return;
    if (left > MAXX ) return;
    if (right < MINX ) return;
    
	if (top < MINY) top = MINY;
    if (bot > MAXY ) bot = MAXY;
	if (left < MINX) left = MINX;
    if (right > MAXX ) right = MAXX;
        
	gr_ubox12(left, top, right, bot );
    
}

void gr_ubox(int left,int top,int right,int bot)
{
	if (TYPE==BM_LINEAR)
		gr_ubox0( left, top, right, bot );
    else
		gr_ubox12( left, top, right, bot );
}

void gr_box(int left,int top,int right,int bot)
{
	if (TYPE==BM_LINEAR)
		gr_box0( left, top, right, bot );
	else
		gr_box12( left, top, right, bot );
}
