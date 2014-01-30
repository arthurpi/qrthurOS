#ifndef INCLUDES_SCREEN_H
# define INCLUDES_SCREEN_H

# define SCREENBASE 0xB8000
# define SCREENSIZE 0xFA0
# define SCREENLIM 0xB8FA0

extern unsigned char kY;

void        kputchar(unsigned char);
void        kputstring(unsigned char *);
void        kscroll(unsigned int);
void        kclearscreen(void);

#endif /* INCLUDES_SCREEN_H */
