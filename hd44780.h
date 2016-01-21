#ifndef HD44780_H
#define	HD44780_H

//przypisanie nazw dla portów
#define DB7tris TRISBbits.TRISB7 /*przypisanie nazwy DB7tris dla RB7 jako TRISBbits.TRISB7 aby można było ustawić,
czy ma pracować jako wejście lub wyjście*/
#define DB7 LATBbits.LATB7 //przypisanie nazwy DB7 dla RB7 jako LATBbits.LATB7 aby wystawiać na nim stan logiczny
#define DB6tris TRISBbits.TRISB6
#define DB6 LATBbits.LATB6
#define DB5tris TRISBbits.TRISB5
#define DB5 LATBbits.LATB5
#define DB4tris TRISBbits.TRISB4
#define DB4 LATBbits.LATB4
#define Etris TRISBbits.TRISB3
#define E LATBbits.LATB3 //Enable
#define RStris TRISBbits.TRISB2
#define RS LATBbits.LATB2

//definicja komend
#define LCD_CLEAR 1
#define DISP_OFF 8
#define DISP_ON_CURSOR_OFF_BLINK_OFF 12
#define DISP_ON_CURSOR_ON_BLINK_ON 15
#define DISP_ON_CUROSOR_ON_BLINK_OFF 14
#define DISP_ON_CUROSOR_OFF_BLINK_ON 13
#define _4_BIT_2_LINES_FONT_5X8 40
#define _2_ROW 192
#define RETURN_HOME 2
#define CURSOR_RIGHT 20
#define CURSOR_LEFT 16
#define SHIFT_LCD_RIGHT 28
#define SHIFT_LCD_LEFT 24

void Init_lcd();
void LcdCmd(unsigned char command);
void LcdData(char data);
void LcdText(unsigned char x, unsigned char y, const char *text);
void LcdClr(void);
void SetCursor(unsigned char x, unsigned char y);
void znaki_pl_i_stopien();




    void Init_lcd() {

        //ustawnienie portów jako wyjścia
        DB7tris = 0;
        DB6tris = 0;
        DB5tris = 0;
        DB4tris = 0;
        Etris = 0;
        RStris = 0;

        //wystawienie stanów niskich na wszystkich użytych wyprowadzeniach
        DB7 = 0;
        DB6 = 0;
        DB5 = 0;
        DB4 = 0;
        E = 0;
        RS = 0;


/******************************************************************************/


//Ustawniwnie wy?wietlacza w tryb 4 bitowy
        E = 1;
        DB7 = 0;
        DB6 = 0;
        DB5 = 1;
        DB4 = 0;
        E = 0;
        __delay_ms(5);

    }

    void LcdCmd(unsigned char command) {
        RS = 0;
        E = 1;
        DB7 = (command & 0b10000000) >> 7; //wyodrebnienie bitu nr 7
        DB6 = (command & 0b01000000) >> 6; //wyodrebnienie bitu nr 6
        DB5 = (command & 0b00100000) >> 5;
        DB4 = (command & 0b00010000) >> 4;
        E = 0;

        E = 1;
        DB7 = (command & 0b00001000) >> 3;
        DB6 = (command & 0b00000100) >> 2;
        DB5 = (command & 0b00000010) >> 1;
        DB4 = (command & 0b00000001);
        E = 0;
        __delay_ms(5);

    }

    void LcdData(const char data) {
        RS = 1;
        E = 1;
        DB7 = (data & 0b10000000) >> 7; //wyodrebnienie bitu nr 7
        DB6 = (data & 0b01000000) >> 6; //wyodrebnienie bitu nr 6
        DB5 = (data & 0b00100000) >> 5;
        DB4 = (data & 0b00010000) >> 4;
        E = 0;

        E = 1;
        DB7 = (data & 0b00001000) >> 3;
        DB6 = (data & 0b00000100) >> 2;
        DB5 = (data & 0b00000010) >> 1;
        DB4 = (data & 0b00000001);
        E = 0;
        RS = 0;
        __delay_ms(5);
    }

    void LcdText(unsigned char x, unsigned char y, const char *text) {
        LcdCmd(RETURN_HOME);
        if (y == 2) { //jesli y=2 przejdz do 2 linii
            LcdCmd(_2_ROW);
        }
        else {
            LcdCmd(RETURN_HOME);
        }
        
        for (int i=0; i<x; i++) { //przesuwaj kursor w prawo o tyle pol ile wynosi x
            LcdCmd(CURSOR_RIGHT);
        }

        while (*text) { //wysylanie tekstu
        LcdData(*text);
        text++;
        __delay_ms(2);
        }
    }

    void LcdClr(void) {
        LcdCmd(LCD_CLEAR);
        LcdCmd(DISP_ON_CURSOR_OFF_BLINK_OFF);
    }

    void SetCursor(unsigned char x, unsigned char y) {
        LcdCmd(RETURN_HOME);
        if (y == 2) { //jesli y=2 przejdz do 2 linii
            LcdCmd(_2_ROW);
        }
        else {
            LcdCmd(RETURN_HOME);
        }

        for (int i=0; i<x; i++) { //przesuwaj kursor w prawo o tyle pol ile wynosi x
            LcdCmd(CURSOR_RIGHT);
        }
    }

    void znaki_pl_i_stopien() {
/*LcdData();  znak
  0x00       °
  0x01       ą
  0x02       ę
  0x03       ć 
  0x04       ł
  0x05       ń
  0x06       ó
  0x07       ś  
  */
        
        //pamiec cg ram moze pomiescic 8 znakow, czyli 64 bajty
        char data1[8]    = {12,18,18,12,0,0,0,0}; //°
        char data2[8]    = {0,0,14,1,15,17,15,2}; //ą
        char data3[8]    = {0,0,14,17,31,16,14,2}; //ę
        char data4[8]    = {2,4,14,16,16,17,14,0}; //ć
        char data5[8]    = {12,4,6,12,4,4,14,0}; //ł
        char data6[8]    = {2,4,22,25,17,17,17,0}; //ń
        char data7[8]    = {2,4,14,17,17,17,14,0}; //ó
        char data8[8]    = {2,4,14,16,14,1,30,0}; //ś

        LcdCmd(64); //adres pamieci cg ram musi byc ustawiony na 0 (komenda o war. 64)
        for (unsigned char i=0; i<8; i++) {
            LcdData(data1[i]);
        }
        LcdCmd(72); //kazdy nastepny adres wpisywania kolejnego znaku musi miec wartosc wieksza o 8 od poprzedniego; kazdy kolejny tego samego znaku jest inkrementowany automatycznie
        for (unsigned char i=0; i<8; i++) {
            LcdData(data2[i]);
        }
        LcdCmd(80);
        for (unsigned char i=0; i<8; i++) {
            LcdData(data3[i]);
        }
        LcdCmd(88);
        for (unsigned char i=0; i<8; i++) {
            LcdData(data4[i]);
        }
        LcdCmd(96);
        for (unsigned char i=0; i<8; i++) {
            LcdData(data5[i]);
        }
        LcdCmd(104);
        for (unsigned char i=0; i<8; i++) {
            LcdData(data6[i]);
        }
        LcdCmd(112);
        for (unsigned char i=0; i<8; i++) {
            LcdData(data7[i]);
        }
        LcdCmd(120);
        for (unsigned char i=0; i<8; i++) {
            LcdData(data8[i]);
        }   
    }

#endif	/* HD44780_H */
