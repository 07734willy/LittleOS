#include "io.h"

/* The I/O ports */
#define FB_COMMAND_PORT         0x3D4
#define FB_DATA_PORT            0x3D5

/* The I/O port commands */
#define FB_HIGH_BYTE_COMMAND    14
#define FB_LOW_BYTE_COMMAND     15

#define FB_ADDRESS 0x000B8000

/** fb_move_cursor:
 *  Moves the cursor of the framebuffer to the given position
 *
 *  @param pos The new position of the cursor
 */
void fb_move_cursor(unsigned short pos)
{
    outb(FB_COMMAND_PORT, FB_HIGH_BYTE_COMMAND);
    outb(FB_DATA_PORT,    ((pos >> 8) & 0x00FF));
    outb(FB_COMMAND_PORT, FB_LOW_BYTE_COMMAND);
    outb(FB_DATA_PORT,    pos & 0x00FF);
}

/** fb_write_cell:
 *  Writes a character with the given foreground and background to position i
 *  in the framebuffer.
 *
 *  @param i  The location in the framebuffer
 *  @param c  The character
 *  @param fg The foreground color
 *  @param bg The background color
 */
void fb_write_cell(unsigned int i, char c, unsigned char fg, unsigned char bg, unsigned char blink) {
    char* fb = (char*)FB_ADDRESS;
    fb[2 * i] = c;
    fb[2 * i + 1] = (fg & 0xF) | ((bg & 7) << 4) | (!!blink << 7);
}

/** write
 * Writes a null-terminated string in the framebuffer. It will
 * automatically advance the cursor and scroll the screen in necessary.
 * 
 * @param s The null-terminated string
 */
/*
void fb_write(const char* s) {
    // TODO
}
*/
