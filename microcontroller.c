#include <8051.h>
 
#define FALSE 0
#define TRUE 1
 
__code unsigned char DIGITS[10] = { 0b00111111, 0b00000110, 
    0b01011011, 0b01001111, 0b01100110, 0b01101101, 
    0b01111101, 0b00000111, 0b01111111, 0b01101111 };
 
__code unsigned char POWERS_OF_2[6] = { 0b00000001, 0b00000010, 
    0b00000100, 0b00001000, 0b00010000, 0b00100000 };
 
// > needs manual display.
//  MAIN SCREEN
//  SETTINGS
__code unsigned char M_0_1[30] = { 0x20, 0x4D, 0x41, 0x49, 0x4E, 0x20, 0x53, 
    0x43, 0x52, 0x45, 0x45, 0x4E, 0x20, 0x20, 0x20, 
    0x20, 0x53, 0x45, 0x54, 0x54, 0x49, 0x4E, 
    0x47, 0x53, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20 };
 
// Value needs manual display.
// RAFAL SZULC
// PWM VALUE: 
__code unsigned char M_2[27] = { 0x52, 0x41, 0x46, 0x41, 0x4C, 0x20, 0x53, 0x5A, 
    0x55, 0x4C, 0x43, 0x20, 0x20, 0x20, 0x20, 0x20, 
    0x50, 0x57, 0x4D, 0x20, 0x56, 0x41, 0x4C, 0x55, 
    0x45, 0x3A, 0x20 };
 
// > needs manual display.
//  PWM
//  LED
__code unsigned char M_3_4[30] = { 0x20, 0x50, 0x57, 0x4D, 0x20, 0x20, 0x20, 
    0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 
    0x20, 0x4D, 0x45, 0x44, 0x20, 0x20, 0x20, 
    0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20 };
 
// > needs manual display.
//  OTHER
//  LOAD DEFAULTS
__code unsigned char M_5_6[30] = { 0x20, 0x4F, 0x54, 0x48, 0x45, 0x52, 0x20, 
    0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 
    0x20, 0x4C, 0x4F, 0x41, 0x44, 0x20, 0x44, 
    0x45, 0x46, 0x41, 0x55, 0x4C, 0x54, 0x53, 0x20 };
 
// >, NUMBER and status of STATE need manual display.
//  STATE OFF/ON
//  VALUE NUMBER
__code unsigned char M_7_8[15] = { 0x20, 0x53, 0x54, 0x41, 0x54, 0x45, 0x20, 
    0x4F, 
    0x20, 0x56, 0x41, 0x4C, 0x55, 0x45, 0x20 };
 
// Status of BUZZ needs manual display.
// > BUZZ OFF/ON
// 
__code unsigned char M_15[8] = { 0x3E, 0x20, 0x42, 0x55, 0x5A, 0x5A, 0x20, 0x4F };
 
// count 30 - 75
__code unsigned char TH0_LOW_SMALL[46] = { 186, 
    186, 186, 186, 186, 186, 186, 186, 186, 186, 186, 
    186, 187, 187, 187, 187, 187, 187, 187, 187, 187, 
    187, 187, 187, 187, 187, 188, 188, 188, 188, 188, 
    188, 188, 188, 188, 188, 188, 188, 188, 188, 189, 
    189, 189, 189, 189, 189 };
 
// count 76 - 120
__code unsigned char TH0_LOW_BIG[45] = { 189, 189, 189, 189, 189, 
    189, 189, 189, 190, 190, 190, 190, 190, 190, 190, 
    190, 190, 190, 190, 190, 190, 190, 191, 191, 191, 
    191, 191, 191, 191, 191, 191, 191, 191, 191, 191, 
    191, 192, 192, 192, 192, 192, 192, 192, 192, 192 };
 
// count 30 - 75
__code unsigned char TL0_LOW_SMALL[46] = { 41, 
    59, 78, 96, 115, 133, 152, 170, 188, 207, 225, 
    244, 6, 25, 43, 61, 80, 98, 117, 135, 154, 
    172, 190, 209, 227, 246, 8, 27, 45, 63, 82, 
    100, 119, 137, 156, 174, 193, 211, 229, 248, 10, 
    29, 47, 66, 84, 102 };
 
// count 76 - 120
__code unsigned char TL0_LOW_BIG[45] = { 121, 139, 158, 176, 195, 
    213, 231, 250, 12, 31, 49, 68, 86, 104, 123, 
    141, 160, 178, 197, 215, 233, 252, 14, 33, 51, 
    70, 88, 106, 125, 143, 162, 180, 199, 217, 236, 
    254, 16, 35, 53, 72, 90, 109, 127, 145, 164 };
 
// count 30 - 75
__code unsigned char TH0_HIGH_SMALL[46] = { 253, 
    253, 253, 253, 253, 253, 253, 253, 253, 253, 253, 
    253, 253, 252, 252, 252, 252, 252, 252, 252, 252, 
    252, 252, 252, 252, 252, 251, 251, 251, 251, 251, 
    251, 251, 251, 251, 251, 251, 251, 251, 251, 250, 
    250, 250, 250, 250, 250 };
 
// count 76 - 120
__code unsigned char TH0_HIGH_BIG[45] = { 250, 250, 250, 250, 250, 
    250, 250, 250, 249, 249, 249, 249, 249, 249, 249, 
    249, 249, 249, 249, 249, 249, 249, 248, 248, 248, 
    248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 
    248, 247, 247, 247, 247, 247, 247, 247, 247, 247 };
 
// count 30 - 75
__code unsigned char TL0_HIGH_SMALL[46] = { 215, 
    197, 178, 160, 141, 123, 104, 86, 68, 49, 31, 
    12, 0, 231, 213, 195, 176, 158, 139, 121, 102, 
    84, 66, 47, 29, 10, 248, 229, 211, 193, 174, 
    156, 137, 119, 100, 82, 63, 45, 27, 8, 246, 
    227, 209, 190, 172, 154 };
 
// count 76 - 120
__code unsigned char TL0_HIGH_BIG[45] = { 135, 117, 98, 80, 61,
    43, 25, 6, 244, 225, 207, 188, 170, 152, 133, 
    115, 96, 78, 59, 41, 23, 4, 242, 223, 205, 
    186, 168, 150, 131, 113, 94, 76, 57, 39, 20, 
    2, 240, 221, 203, 184, 166, 147, 129, 111, 92 };
 
__xdata unsigned char * keyboard_left_22 = 
    (__xdata unsigned char *) 0xFF22; // keyboard
 
__xdata unsigned char * CS55B = 
    (__xdata unsigned char *) 0xFF29; // 8255 - registry of port B
__xdata unsigned char * CS55D = 
    (__xdata unsigned char *) 0xFF2B; // 8255 - registry of control port
 
__xdata unsigned char * led_choose = 
    (__xdata unsigned char *) 0xFF30;
__xdata unsigned char * led_led = 
    (__xdata unsigned char *) 0xFF38;
 
__xdata unsigned char * screen_80 = 
    (__xdata unsigned char *) 0xFF80;
__xdata unsigned char * screen_81 = 
    (__xdata unsigned char *) 0xFF81;
__xdata unsigned char * screen_82 = 
    (__xdata unsigned char *) 0xFF82;
 
__bit __at (0x95) buzzer; // P1.5
__bit __at (0x96) seven_segment_display_access; // P1.6
__bit __at (0x97) test; // P1.7
__bit __at (0xB5) keyboard_access; // P3.5
 
__bit t0_flag; // 1 - HIGH
 
unsigned char sending;
unsigned char count;
unsigned char lamps;
__bit state;
unsigned char helper;
unsigned char helper_2;
unsigned char helper_3;
unsigned char helper_4;
unsigned char helper_5;
unsigned char helper_6;
unsigned char helper_7;
unsigned char helper_8;
unsigned char helper_9;
unsigned char delay_helper;
unsigned char delay_helper_2;
unsigned char lcd_package;
unsigned char menu_number;
unsigned char keyboard_left;
unsigned char it;
unsigned char count_delta;
__bit state_delta;
unsigned char lamps_delta;
unsigned char buzzer_delta;
 
void init(void);
void delay(void);
void show_helper(void);
void show(void);
void keyboard_right(void);
void display_nothing(void);
void menu_0_1(void);
void menu_2(void);
void menu_3_6(void);
void menu_7_8(void);
void menu_9_14(void);
void menu_15(void);
void lcd_wait_while_busy(void);
void lcd_cmd_from_package(void);
void lcd_data_from_package(void);
void lcd_init(void);
void count_change(void);
void set_new_count(void);
 
void main(void)
{
    init();
 
    while (TRUE) {
        show();
        
        keyboard_right();
        
        count_change();
        
        //   MAIN SCREEN
        //   SETTINGS
        if (menu_number < 2) {
            menu_0_1();
        }
        else {
            // RAFAL SZULC
            // PWM VALUE: NUMBER
            if (menu_number == 2) {
                menu_2();
            }
            else {
                //   PWM
                //   LED
                //   next page
                //   OTHER
                //   LOAD DEFAULTS
                if (menu_number < 7) {
                    menu_3_6();
                }
                else {
                    //   STATE OFF/ON
                    //   VALUE NUMBER
                    if (menu_number < 9) {
                        menu_7_8();
                    }
                    else {
                        //   LAMP1 OFF/ON
                        //   LAMP2 OFF/ON
                        if (menu_number < 15) {
                            menu_9_14();
                        }
                        // > BUZZ OFF/ON
                        else {
                            menu_15();
                        }
                    }
                }
            }
        }
    }
}
 
void init(void) {
    sending = 0;
    count = 30;
    lamps = 0;
    state = FALSE;
    lamps_delta = 0;
    buzzer = TRUE;
    test = TRUE;
    t0_flag = FALSE;
    helper_9 = 0;
    
    SCON = 0b01010000;
    
    TMOD = 0b00100001;
    
    PCON = PCON & 127;
    
    ET0 = 1; // interruptions
    EA = 1;
    
    TF0 = 0; // clock not full
    TR0 = 1; // start the clock
    
    TH1 = 0xFD; // 9600 bod velocity
    TL1 = 0xFD; // 256 - (1/32) * (921600/9600) = 256 - 3 = 253
    
    TF1 = 0;
    TR1 = 1;
    
    *CS55D = 0x80;
    
    count_delta = 0;
    state_delta = FALSE;
    buzzer_delta = 0;
    
    // #0FF38h
    helper = DIGITS[0];
    *led_led = helper;
    
    // #0FF30h
    helper = 1;
    *led_choose = helper;
    
    seven_segment_display_access = FALSE;
    
    lcd_init();
    menu_number = 0;
}
 
void delay(void) {
    delay_helper = TL0;
    delay_helper_2 = TH0;
    
    if (delay_helper < 64) {
        while (TH0 == delay_helper_2 && TL0 < 128) {}
    }
    else {
        if (delay_helper < 128) {
            while (TH0 == delay_helper_2 && TL0 < 192) {}
        }
        else {
            if (delay_helper < 192) {
                while (TH0 == delay_helper_2) {}
            }
            else {
                while (TH0 == delay_helper_2) {}
                
                delay_helper_2 = TH0;
                
                while (TH0 == delay_helper_2 && TL0 < 64) {}
            }
        }
    }
}
 
void show_helper(void) {
    seven_segment_display_access = FALSE;
    delay();
    seven_segment_display_access = TRUE;
}
 
void show(void) {
    // First digit.
    helper = count % 10;
    helper = DIGITS[helper];
    
    // #0FF38h
    *led_led = helper;
    
    // #0FF30h
    helper = 1;
    *led_choose = helper;
    
    
    show_helper();
    
    
    // Second digit.
    helper = ((count % 100) / 10) % 10;
    helper = DIGITS[helper];
    
    // #0FF38h
    *led_led = helper;
    
    // #0FF30h
    helper = 2;
    *led_choose = helper;
    
    
    show_helper();
    
    
    // Third digit.
    helper = count / 100;
    helper = DIGITS[helper];
    
    // #0FF38h
    *led_led = helper;
    
    // #0FF30h
    helper = 4;
    *led_choose = helper;
    
    
    show_helper();
    
    
    // Lamps.
    
    // #0FF38h
    *led_led = lamps;
    
    // #0FF30h
    helper = 64;
    *led_choose = helper;
    
    
    show_helper();
}
 
void keyboard_right(void) {
    // Catching Up Arrow.
    
    // #0FF30h
    helper = 8;
    *led_choose = helper;
    
    if (keyboard_access == TRUE) {
        ++count;
        if (count == 121) {
            count = 30;
        }
        
        do {
            show();
            
            // #0FF30h
            helper = 8;
            *led_choose = helper;
        }
        while (keyboard_access == TRUE);
    }
    
    
    // Catching Down Arrow.
    
    // #0FF30h
    helper = 16;
    *led_choose = helper;
    
    if (keyboard_access == TRUE) {
        --count;
        if (count == 29) {
            count = 120;
        }
        
        do {
            show();
            
            // #0FF30h
            helper = 16;
            *led_choose = helper;
        }
        while (keyboard_access == TRUE);
    }
    
    
    // Catching Right Arrow.
    
    // #0FF30h
    helper = 4;
    *led_choose = helper;
    
    if (keyboard_access == TRUE) {
        count = count + 10;
        if (count > 120) {
            count = count - 91;
        }
        
        do {
            show();
            
            // #0FF30h
            helper = 4;
            *led_choose = helper;
        }
        while (keyboard_access == TRUE);
    }
    
    
    // Catching Left Arrow.
    
    // #0FF30h
    helper = 32;
    *led_choose = helper;
    
    if (keyboard_access == TRUE) {
        count = count - 10;
        if (count < 30) {
            count = count + 91;
        }
        
        do {
            show();
            
            // #0FF30h
            helper = 32;
            *led_choose = helper;
        }
        while (keyboard_access == TRUE);
    }
}
 
void display_nothing(void) {
    it = 0;
    while (it < 24) {
        lcd_package = 0x20;
        lcd_data_from_package();
        ++it;
    }
}
 
void menu_0_1(void) {
    // Display.
    if (menu_number == 0) {
        lcd_package = 0x3E;
    }
    else {
        lcd_package = 0x20;
    }
    lcd_data_from_package();
    
    it = 0;
    while (it < 15) {
        lcd_package = M_0_1[it];
        lcd_data_from_package();
        ++it;
    }
    
    display_nothing();
    
    if (menu_number == 0) {
        lcd_package = 0x20;
    }
    else {
        lcd_package = 0x3E;
    }
    lcd_data_from_package();
    
    it = 15;
    while (it < 30) {
        lcd_package = M_0_1[it];
        lcd_data_from_package();
        ++it;
    }
    
    display_nothing();
    
    // Catching Up Arrow.
    keyboard_left = *keyboard_left_22;          
    keyboard_left = keyboard_left / 16;
    if (keyboard_left % 2 == 0) {
        --menu_number;
        if (menu_number == 255) {
            menu_number = 1;
        }
        
        do {
            show();
            
            keyboard_right();
            
            keyboard_left = *keyboard_left_22;
            keyboard_left = keyboard_left / 16;
        }
        while ((keyboard_left % 2) == 0);
    }
    else {
        // Catching Down Arrow.
        keyboard_left = *keyboard_left_22;          
        keyboard_left = keyboard_left / 32;
        if (keyboard_left % 2 == 0) {
            ++menu_number;
            if (menu_number == 2) {
                menu_number = 0;
            }
            
            do {
                show();
                
                keyboard_right();
                
                keyboard_left = *keyboard_left_22;
                keyboard_left = keyboard_left / 32;
            }
            while ((keyboard_left % 2) == 0);
        }
        else {
            // Catching Enter.
            keyboard_left = *keyboard_left_22;          
            keyboard_left = keyboard_left / 128;
            if (keyboard_left % 2 == 0) {
                if (menu_number == 0) {
                    menu_number = 2;
                }
                else {
                    menu_number = 3;
                }
                
                do {
                    show();
                    
                    keyboard_right();
                    
                    keyboard_left = *keyboard_left_22;
                    keyboard_left = keyboard_left / 128;
                }
                while ((keyboard_left % 2) == 0);
            }   
        }
    }
}
 
void menu_2(void) {
    // Display.             
    it = 0;
    while (it < 16) {
        lcd_package = M_2[it];
        lcd_data_from_package();
        ++it;
    }
    
    display_nothing();
    
    it = 16;
    while (it < 27) {
        lcd_package = M_2[it];
        lcd_data_from_package();
        ++it;
    }
    
    lcd_package = (count / 100) + 48;
    lcd_data_from_package();
    lcd_package = (((count % 100) / 10) % 10) + 48;
    lcd_data_from_package();
    lcd_package = (count % 10) + 48;
    lcd_data_from_package();
    
    lcd_package = 0x20;
    lcd_data_from_package();
    lcd_package = 0x20;
    lcd_data_from_package();
    
    display_nothing();
    
    // Catching Esc.
    keyboard_left = *keyboard_left_22;          
    keyboard_left = keyboard_left / 64;
    if (keyboard_left % 2 == 0) {
        menu_number = 0;
        
        do {
            show();
            
            keyboard_right();
            
            keyboard_left = *keyboard_left_22;
            keyboard_left = keyboard_left / 64;
        }
        while ((keyboard_left % 2) == 0);
    }
}
 
void menu_3_6(void) {
    // Display.
    if ((menu_number % 2) == 1) {
        lcd_package = 0x3E;
    }
    else {
        lcd_package = 0x20;
    }
    lcd_data_from_package();
    
    it = 0;
    while (it < 15) {
        if (menu_number < 5) {
            lcd_package = M_3_4[it];
        }
        else {
            lcd_package = M_5_6[it];
        }
        lcd_data_from_package();
        ++it;
    }
    
    display_nothing();
    
    if ((menu_number % 2) == 1) {
        lcd_package = 0x20;
    }
    else {
        lcd_package = 0x3E;
    }
    lcd_data_from_package();
    
    it = 15;
    while (it < 30) {
        if (menu_number < 5) {
            lcd_package = M_3_4[it];
        }
        else {
            lcd_package = M_5_6[it];
        }
        lcd_data_from_package();
        ++it;
    }
    
    display_nothing();
    
    // Catching Up Arrow.
    keyboard_left = *keyboard_left_22;          
    keyboard_left = keyboard_left / 16;
    if (keyboard_left % 2 == 0) {
        --menu_number;
        if (menu_number == 2) {
            menu_number = 6;
        }
        
        do {
            show();
            
            keyboard_right();
            
            keyboard_left = *keyboard_left_22;
            keyboard_left = keyboard_left / 16;
        }
        while ((keyboard_left % 2) == 0);
    }
    else {
        // Catching Down Arrow.
        keyboard_left = *keyboard_left_22;          
        keyboard_left = keyboard_left / 32;
        if (keyboard_left % 2 == 0) {
            ++menu_number;
            if (menu_number == 7) {
                menu_number = 3;
            }
            
            do {
                show();
                
                keyboard_right();
                
                keyboard_left = *keyboard_left_22;
                keyboard_left = keyboard_left / 32;
            }
            while ((keyboard_left % 2) == 0);
        }
        else {
            // Catching Enter.
            keyboard_left = *keyboard_left_22;          
            keyboard_left = keyboard_left / 128;
            if (keyboard_left % 2 == 0) {
                if (menu_number == 3) {
                    menu_number = 7;
                }
                if (menu_number == 4) {
                    menu_number = 9;
                }
                if (menu_number == 5) {
                    menu_number = 15;
                }
                if (menu_number == 6) {
                    count = 30;
                    lamps = 0;
                    state = FALSE;
                    buzzer = TRUE;
                    menu_number = 1;
                }
                
                do {
                    show();
                    
                    keyboard_right();
                    
                    keyboard_left = *keyboard_left_22;
                    keyboard_left = keyboard_left / 128;
                }
                while ((keyboard_left % 2) == 0);
            }
            else {
                // Catching Esc.
                keyboard_left = *keyboard_left_22;          
                keyboard_left = keyboard_left / 64;
                if (keyboard_left % 2 == 0) {
                    menu_number = 1;
                    
                    do {
                        show();
                        
                        keyboard_right();
                        
                        keyboard_left = *keyboard_left_22;
                        keyboard_left = keyboard_left / 64;
                    }
                    while ((keyboard_left % 2) == 0);
                }
            }
        }
    }
}
 
void menu_7_8(void) {
    // Display.
    if (menu_number == 7) {
        lcd_package = 0x3E;
    }
    else {
        lcd_package = 0x20;
    }
    lcd_data_from_package();
    
    it = 0;
    while (it < 8) {
        lcd_package = M_7_8[it];
        lcd_data_from_package();
        ++it;
    }
    
    if ((state == FALSE && state_delta == FALSE) ||
        (state == TRUE && state_delta == TRUE)) {
        
        lcd_package = 0x46;
        lcd_data_from_package();
        lcd_package = 0x46;
        lcd_data_from_package();
    }
    else {
        lcd_package = 0x4E;
        lcd_data_from_package();
        lcd_package = 0x20;
        lcd_data_from_package();
    }
    
    it = 0;
    while (it < 5) {
        lcd_package = 0x20;
        lcd_data_from_package();
        ++it;
    }
    
    display_nothing();
    
    if (menu_number == 7) {
        lcd_package = 0x20;
    }
    else {
        lcd_package = 0x3E;
    }
    lcd_data_from_package();
    
    it = 8;
    while (it < 15) {
        lcd_package = M_7_8[it];
        lcd_data_from_package();
        ++it;
    }
    
    helper_2 = count + count_delta;
    if (helper_2 > 120) {
        helper_2 = helper_2 - 91;
    }
    lcd_package = (helper_2 / 100) + 48;
    lcd_data_from_package();
    lcd_package = (((helper_2 % 100) / 10) % 10) + 48;
    lcd_data_from_package();
    lcd_package = (helper_2 % 10) + 48;
    lcd_data_from_package();
    
    it = 0;
    while (it < 5) {
        lcd_package = 0x20;
        lcd_data_from_package();
        ++it;
    }
    
    display_nothing();
    
    // Catching Right Arrow.
    keyboard_left = *keyboard_left_22;          
    keyboard_left = keyboard_left / 8;
    if (keyboard_left % 2 == 0) {
        if (menu_number == 7) {
            state_delta = !state_delta;
        }
        else {
            count_delta = count_delta + 10;
            if (count_delta > 90) {
                count_delta = count_delta - 91;
            }
        }
        
        do {
            show();
            
            keyboard_right();
            
            keyboard_left = *keyboard_left_22;
            keyboard_left = keyboard_left / 8;
        }
        while ((keyboard_left % 2) == 0);
    }
    else {
        // Catching Left Arrow.
        keyboard_left = *keyboard_left_22;          
        keyboard_left = keyboard_left / 4;
        if (keyboard_left % 2 == 0) {
            if (menu_number == 7) {
                state_delta = !state_delta;
            }
            else {
                if (count_delta > 9) {
                    count_delta = count_delta - 10;
                }
                else {
                    count_delta = count_delta + 81; 
                }
            }
            
            do {
                show();
                
                keyboard_right();
                
                keyboard_left = *keyboard_left_22;
                keyboard_left = keyboard_left / 4;
            }
            while ((keyboard_left % 2) == 0);
        }
        else {
            // Catching Enter.
            keyboard_left = *keyboard_left_22;          
            keyboard_left = keyboard_left / 128;
            if (keyboard_left % 2 == 0) {
                if (state_delta == TRUE) {
                    state = !state;
                }
                state_delta = FALSE;
                
                count = count + count_delta;
                if (count > 120) {
                    count = count - 91;
                }
                count_delta = 0;
                menu_number = 3;
                
                do {
                    show();
                    
                    keyboard_right();
                    
                    keyboard_left = *keyboard_left_22;
                    keyboard_left = keyboard_left / 128;
                }
                while ((keyboard_left % 2) == 0);
            }
            else {
                // Catching Esc.
                keyboard_left = *keyboard_left_22;          
                keyboard_left = keyboard_left / 64;
                if (keyboard_left % 2 == 0) {
                    state_delta = FALSE;
                    count_delta = 0;
                    menu_number = 3;
                    
                    do {
                        show();
                        
                        keyboard_right();
                        
                        keyboard_left = *keyboard_left_22;
                        keyboard_left = keyboard_left / 64;
                    }
                    while ((keyboard_left % 2) == 0);
                }
                else {
                    // Catching Up Arrow.
                    keyboard_left = *keyboard_left_22;          
                    keyboard_left = keyboard_left / 16;
                    if (keyboard_left % 2 == 0) {
                        --menu_number;
                        if (menu_number == 6) {
                            menu_number = 8;
                        }
                        
                        do {
                            show();
                            
                            keyboard_right();
                            
                            keyboard_left = *keyboard_left_22;
                            keyboard_left = keyboard_left / 16;
                        }
                        while ((keyboard_left % 2) == 0);
                    }
                    else {
                        // Catching Down Arrow.
                        keyboard_left = *keyboard_left_22;          
                        keyboard_left = keyboard_left / 32;
                        if (keyboard_left % 2 == 0) {
                            ++menu_number;
                            if (menu_number == 9) {
                                menu_number = 7;
                            }
                            
                            do {
                                show();
                                
                                keyboard_right();
                                
                                keyboard_left = *keyboard_left_22;
                                keyboard_left = keyboard_left / 32;
                            }
                            while ((keyboard_left % 2) == 0);
                        }
                    }
                }
            }
        }
    }
}
 
void menu_9_14(void) {
    // Display.
    if ((menu_number % 2) == 1) {
        lcd_package = 0x3E;
        lcd_data_from_package();
    }
    else {
        lcd_package = 0x20;
        lcd_data_from_package();
    }
    
    lcd_package = 0x20;
    lcd_data_from_package();
    
    if (menu_number == 9 || menu_number == 10) {
        lcd_package = 0x46;
        lcd_data_from_package();
        lcd_package = 0x31;
        lcd_data_from_package();
    }
    
    if (menu_number == 11 || menu_number == 12) {
        lcd_package = 0x46;
        lcd_data_from_package();
        lcd_package = 0x33;
        lcd_data_from_package();
    }
    
    if (menu_number == 13 || menu_number == 14) {
        lcd_package = 0x4F;
        lcd_data_from_package();
        lcd_package = 0x4B;
        lcd_data_from_package();
    }
    
    lcd_package = 0x20;
    lcd_data_from_package();
    
    lcd_package = 0x4F;
    lcd_data_from_package();
    
    helper_2 = lamps;
    helper_3 = lamps_delta;
    if (menu_number == 9 || menu_number == 10) {
        if ((helper_2 % 2) == (helper_3 % 2)) {
            lcd_package = 0x46;
            lcd_data_from_package();
            lcd_package = 0x46;
            lcd_data_from_package();
        }
        else {
            lcd_package = 0x4E;
            lcd_data_from_package();
            lcd_package = 0x20;
            lcd_data_from_package();
        }
    }
    
    helper_2 = helper_2 / 4;
    helper_3 = helper_3 / 4;
    if (menu_number == 11 || menu_number == 12) {
        if ((helper_2 % 2) == (helper_3 % 2)) {
            lcd_package = 0x46;
            lcd_data_from_package();
            lcd_package = 0x46;
            lcd_data_from_package();
        }
        else {
            lcd_package = 0x4E;
            lcd_data_from_package();
            lcd_package = 0x20;
            lcd_data_from_package();
        }
    }
    
    helper_2 = helper_2 / 4;
    helper_3 = helper_3 / 4;
    if (menu_number == 13 || menu_number == 14) {
        if ((helper_2 % 2) == (helper_3 % 2)) {
            lcd_package = 0x46;
            lcd_data_from_package();
            lcd_package = 0x46;
            lcd_data_from_package();
        }
        else {
            lcd_package = 0x4E;
            lcd_data_from_package();
            lcd_package = 0x20;
            lcd_data_from_package();
        }
    }
    
    it = 0;
    while (it < 8) {
        lcd_package = 0x20;
        lcd_data_from_package();
        ++it;
    }
    
    display_nothing();
    
    if ((menu_number % 2) == 1) {
        lcd_package = 0x20;
        lcd_data_from_package();
    }
    else {
        lcd_package = 0x3E;
        lcd_data_from_package();
    }
    
    lcd_package = 0x20;
    lcd_data_from_package();
    
    if (menu_number == 9 || menu_number == 10) {
        lcd_package = 0x46;
        lcd_data_from_package();
        lcd_package = 0x32;
        lcd_data_from_package();
    }
    
    if (menu_number == 11 || menu_number == 12) {
        lcd_package = 0x46;
        lcd_data_from_package();
        lcd_package = 0x34;
        lcd_data_from_package();
    }
    
    if (menu_number == 13 || menu_number == 14) {
        lcd_package = 0x45;
        lcd_data_from_package();
        lcd_package = 0x52;
        lcd_data_from_package();
    }
    
    lcd_package = 0x20;
    lcd_data_from_package();
    
    lcd_package = 0x4F;
    lcd_data_from_package();
    
    helper_2 = lamps / 2;
    helper_3 = lamps_delta / 2;
    if (menu_number == 9 || menu_number == 10) {
        if ((helper_2 % 2) == (helper_3 % 2)) {
            lcd_package = 0x46;
            lcd_data_from_package();
            lcd_package = 0x46;
            lcd_data_from_package();
        }
        else {
            lcd_package = 0x4E;
            lcd_data_from_package();
            lcd_package = 0x20;
            lcd_data_from_package();
        }
    }
    
    helper_2 = helper_2 / 4;
    helper_3 = helper_3 / 4;
    if (menu_number == 11 || menu_number == 12) {
        if ((helper_2 % 2) == (helper_3 % 2)) {
            lcd_package = 0x46;
            lcd_data_from_package();
            lcd_package = 0x46;
            lcd_data_from_package();
        }
        else {
            lcd_package = 0x4E;
            lcd_data_from_package();
            lcd_package = 0x20;
            lcd_data_from_package();
        }
    }
    
    helper_2 = helper_2 / 4;
    helper_3 = helper_3 / 4;
    if (menu_number == 13 || menu_number == 14) {
        if ((helper_2 % 2) == (helper_3 % 2)) {
            lcd_package = 0x46;
            lcd_data_from_package();
            lcd_package = 0x46;
            lcd_data_from_package();
        }
        else {
            lcd_package = 0x4E;
            lcd_data_from_package();
            lcd_package = 0x20;
            lcd_data_from_package();
        }
    }
    
    it = 0;
    while (it < 8) {
        lcd_package = 0x20;
        lcd_data_from_package();
        ++it;
    }
    
    display_nothing();
    
    // Catching Right Arrow.
    keyboard_left = *keyboard_left_22;          
    keyboard_left = keyboard_left / 8;
    if (keyboard_left % 2 == 0) {
        helper_2 = lamps_delta;
        helper_2 = helper_2 / POWERS_OF_2[menu_number - 9];
        
        if ((helper_2 % 2) == 0) {
            lamps_delta = lamps_delta + POWERS_OF_2[menu_number - 9];
        }
        else {
            lamps_delta = lamps_delta - POWERS_OF_2[menu_number - 9];
        }
        
        do {
            show();
            
            keyboard_right();
            
            keyboard_left = *keyboard_left_22;
            keyboard_left = keyboard_left / 8;
        }
        while ((keyboard_left % 2) == 0);
    }
    else {
        // Catching Left Arrow.
        keyboard_left = *keyboard_left_22;          
        keyboard_left = keyboard_left / 4;
        if (keyboard_left % 2 == 0) {
            helper_2 = lamps_delta;
            helper_2 = helper_2 / POWERS_OF_2[menu_number - 9];
            
            if ((helper_2 % 2) == 0) {
                lamps_delta = lamps_delta + POWERS_OF_2[menu_number - 9];
            }
            else {
                lamps_delta = lamps_delta - POWERS_OF_2[menu_number - 9];
            }
            
            do {
                show();
                
                keyboard_right();
                
                keyboard_left = *keyboard_left_22;
                keyboard_left = keyboard_left / 4;
            }
            while ((keyboard_left % 2) == 0);
        }
        else {
            // Catching Enter.
            keyboard_left = *keyboard_left_22;          
            keyboard_left = keyboard_left / 128;
            if (keyboard_left % 2 == 0) {
                lamps = lamps ^ lamps_delta;
                
                lamps_delta = 0;
                menu_number = 4;
                
                do {
                    show();
                    
                    keyboard_right();
                    
                    keyboard_left = *keyboard_left_22;
                    keyboard_left = keyboard_left / 128;
                }
                while ((keyboard_left % 2) == 0);
            }
            else {
                // Catching Esc.
                keyboard_left = *keyboard_left_22;          
                keyboard_left = keyboard_left / 64;
                if (keyboard_left % 2 == 0) {
                    lamps_delta = 0;
                    menu_number = 4;
                    
                    do {
                        show();
                        
                        keyboard_right();
                        
                        keyboard_left = *keyboard_left_22;
                        keyboard_left = keyboard_left / 64;
                    }
                    while ((keyboard_left % 2) == 0);
                }
                else {
                    // Catching Up Arrow.
                    keyboard_left = *keyboard_left_22;          
                    keyboard_left = keyboard_left / 16;
                    if (keyboard_left % 2 == 0) {
                        --menu_number;
                        if (menu_number == 8) {
                            menu_number = 14;
                        }
                        
                        do {
                            show();
                            
                            keyboard_right();
                            
                            keyboard_left = *keyboard_left_22;
                            keyboard_left = keyboard_left / 16;
                        }
                        while ((keyboard_left % 2) == 0);
                    }
                    else {
                        // Catching Down Arrow.
                        keyboard_left = *keyboard_left_22;          
                        keyboard_left = keyboard_left / 32;
                        if (keyboard_left % 2 == 0) {
                            ++menu_number;
                            if (menu_number == 15) {
                                menu_number = 9;
                            }
                            
                            do {
                                show();
                                
                                keyboard_right();
                                
                                keyboard_left = *keyboard_left_22;
                                keyboard_left = keyboard_left / 32;
                            }
                            while ((keyboard_left % 2) == 0);
                        }
                    }
                }
            }
        }
    }
}
 
void menu_15(void) {
    // Display.
    it = 0;
    while (it < 8) {
        lcd_package = M_15[it];
        lcd_data_from_package();
        ++it;
    }
    
    if ((buzzer == TRUE && buzzer_delta == 0) ||
        (buzzer == FALSE && buzzer_delta == 1)) {
        
        lcd_package = 0x46;
        lcd_data_from_package();
        lcd_package = 0x46;
        lcd_data_from_package();
    }
    else {
        lcd_package = 0x4E;
        lcd_data_from_package();
        lcd_package = 0x20;
        lcd_data_from_package();
    }
    
    it = 0;
    while (it < 6) {
        lcd_package = 0x20;
        lcd_data_from_package();
        ++it;
    }
    
    display_nothing();
    
    it = 0;
    while (it < 16) {
        lcd_package = 0x20;
        lcd_data_from_package();
        ++it;
    }
    
    display_nothing();
    
    // Catching Right Arrow.
    keyboard_left = *keyboard_left_22;          
    keyboard_left = keyboard_left / 8;
    if (keyboard_left % 2 == 0) {
        ++buzzer_delta;
        if (buzzer_delta == 2) {
            buzzer_delta = 0;
        }
        
        do {
            show();
            
            keyboard_right();
            
            keyboard_left = *keyboard_left_22;
            keyboard_left = keyboard_left / 8;
        }
        while ((keyboard_left % 2) == 0);
    }
    else {
        // Catching Left Arrow.
        keyboard_left = *keyboard_left_22;          
        keyboard_left = keyboard_left / 4;
        if (keyboard_left % 2 == 0) {
            ++buzzer_delta;
            if (buzzer_delta == 2) {
                buzzer_delta = 0;
            }
            
            do {
                show();
                
                keyboard_right();
                
                keyboard_left = *keyboard_left_22;
                keyboard_left = keyboard_left / 4;
            }
            while ((keyboard_left % 2) == 0);
        }
        else {
            // Catching Enter.
            keyboard_left = *keyboard_left_22;          
            keyboard_left = keyboard_left / 128;
            if (keyboard_left % 2 == 0) {
                if (buzzer_delta == 1) {
                    if (buzzer == TRUE) {
                        buzzer = FALSE;
                    }
                    else {
                        buzzer = TRUE;
                    }
                }
                buzzer_delta = 0;
                menu_number = 5;
                
                do {
                    show();
                    
                    keyboard_right();
                    
                    keyboard_left = *keyboard_left_22;
                    keyboard_left = keyboard_left / 128;
                }
                while ((keyboard_left % 2) == 0);
            }
            else {
                // Catching Esc.
                keyboard_left = *keyboard_left_22;          
                keyboard_left = keyboard_left / 64;
                if (keyboard_left % 2 == 0) {
                    buzzer_delta = 0;
                    menu_number = 5;
                    
                    do {
                        show();
                        
                        keyboard_right();
                        
                        keyboard_left = *keyboard_left_22;
                        keyboard_left = keyboard_left / 64;
                    }
                    while ((keyboard_left % 2) == 0);
                }
            }
        }
    }
}
 
void lcd_wait_while_busy(void) {
    do {
        show();
        
        helper = *screen_82;
    } while ((helper / 128) == 1);
}
 
void lcd_cmd_from_package(void) {
    lcd_wait_while_busy();
    
    *screen_80 = lcd_package;
}
 
void lcd_data_from_package(void) {
    lcd_wait_while_busy();
    
    *screen_81 = lcd_package;
}
 
void lcd_init(void) {
    lcd_package = 56;
    lcd_cmd_from_package();
    
    lcd_package = 2;
    lcd_cmd_from_package();
    
    lcd_package = 12;
    lcd_cmd_from_package();
    
    lcd_package = 6;
    lcd_cmd_from_package();
    
    lcd_package = 1;
    lcd_cmd_from_package();
}
 
void count_change(void) {
    if (RI == 1 && helper_9 == 2) {
        RI = 0;
        helper_7 = SBUF;
        ++helper_9;
    }
    
    if (RI == 1 && helper_9 == 1) {
        RI = 0;
        helper_6 = SBUF;
        ++helper_9;
    }
    
    if (RI == 1 && helper_9 == 0) {
        RI = 0;
        helper_5 = SBUF;
        ++helper_9;
    }
    
    if (helper_9 == 3) {
        set_new_count();
        helper_9 = 0;
    }
}
 
void set_new_count(void) {
    // 48 is 0 in ASCII.
    helper_5 = helper_5 - 48;
    helper_6 = helper_6 - 48;
    helper_7 = helper_7 - 48;
    
    if (helper_5 < 2) {
        helper_8 = helper_5 * 100 + helper_6 * 10 + helper_7;
        
        if (helper_8 < 121 && helper_8 > 29) {
            count = helper_8;
        }
    }
}
 
void t0_interrupt(void) __interrupt(1) {
    t0_flag = !t0_flag;
    
    TF0 = 0;
    
    if (state == TRUE && t0_flag == TRUE) {
        *CS55B = 0xFF;
        test = FALSE;
        
        if (count < 76) {
            TL0 = TL0_HIGH_SMALL[count - 30];
            TH0 = TH0_HIGH_SMALL[count - 30];
        }
        else {
            TL0 = TL0_HIGH_BIG[count - 76];
            TH0 = TH0_HIGH_BIG[count - 76];
        }
    }
    else {
        *CS55B = 0x00;
        test = TRUE;
        
        if (state == TRUE) {
            if (count < 76) {
                TL0 = TL0_LOW_SMALL[count - 30];
                TH0 = TH0_LOW_SMALL[count - 30];
            }
            else {
                TL0 = TL0_LOW_BIG[count - 76];
                TH0 = TH0_LOW_BIG[count - 76];
            }
        }
        else {
            // 47104, so 50Hz, because 2^16 - 47104 = 18432
            TL0 = 184;
            TH0 = 0;
        }
    }
    
    ++sending;
    // 50 Hz, but interruption itself takes some time.
    if (sending == 92 || (state == FALSE && sending == 14)) {
        sending = 0;
        
        // Finished sending - negation.
        TI = 0;
        // 48 is 0 in ASCII.
        helper_4 = count / 100 + 48;
        SBUF = helper_4;
        // Finishing sending.
        while (TI == 0) {}
        
        TI = 0;
        helper_4 = ((count % 100) / 10) % 10 + 48;
        SBUF = helper_4;
        while (TI == 0) {}
        
        TI = 0;
        helper_4 = count % 10 + 48;
        SBUF = helper_4;
        while (TI == 0) {}
        
        TI = 0;
        helper_4 = 32; // Space.
        SBUF = helper_4;
        while (TI == 0) {}
    }
}