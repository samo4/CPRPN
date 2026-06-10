#include "u8g2.h"

int main(void) {
    u8g2_t u8g2;

    // SDL simulation constructor
    u8g2_SetupBuffer_SDL_128x64(&u8g2, &u8g2_cb_r0);
    u8g2_InitDisplay(&u8g2);
    u8g2_SetPowerSave(&u8g2, 0);

    for (;;) {
        u8g2_FirstPage(&u8g2);
        do {
            u8g2_SetFont(&u8g2, u8g2_font_ncenB08_tr);
            u8g2_DrawStr(&u8g2, 2, 20, "Hello CPRPN!");

            u8g2_SetFont(&u8g2, u8g2_font_5x7_tr);
            u8g2_DrawStr(&u8g2, 2, 36, "128x64 sim");
        } while (u8g2_NextPage(&u8g2));

        // q to quit
        int k = u8g_sdl_get_key();
        if (k == 'q') break;
    }

    return 0;
}
