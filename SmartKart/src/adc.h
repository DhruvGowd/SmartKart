#include <stdint.h>

void setup_gpiox(void);
void setup_gpioy(void);
void setup_adc(void);
int read_adc_channel(unsigned int channel);
int read_x(void);
int read_y(void);
void displayHome(void);
