
#include "audio.h"
#include "avr-common.h"

void set_buzzer(int on) {
    set_pin_output_value(BUZZER_D_OUT_PIN, D, on);
}
