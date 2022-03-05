#ifndef BLYNK_INTERFACE
#define BLYNK_INTERFACE

static struct colorParams_t {
	unsigned int hue = 0;
	unsigned int brightness = 20;
	unsigned int red = 0;
	unsigned int blue = 0;
	unsigned int green = 0;
}colorParams_over, colorParams_amb, colorParams_swing;

#endif