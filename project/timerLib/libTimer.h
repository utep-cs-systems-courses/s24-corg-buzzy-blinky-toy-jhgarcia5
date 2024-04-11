#ifndef libTimer_included
#define libTimer_included

void configureClocks();
void enableWDTInterruptss();
void timerAUpmode();

unsigned char gert_sr();
void set_r(), or_sr(), and_sr();

#endif
