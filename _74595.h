#ifndef _74595_H
#define	_74595_H

//definicja portow
#define DATA LATBbits.LATB7
#define DTtris TRISBbits.TRISB7

#define CLK LATAbits.LATA0
#define CLKtris TRISAbits.TRISA0

#define LATCH LATBbits.LATB6
#define LATCHtris TRISBbits.TRISB6



    void shift_data(unsigned char data);
    void clk();


    void shift_data(unsigned char data) {
        LATCH = 0;
        DATA = (data & 0b00000001);
        clk();

        DATA = (data & 0b00000010) >> 1;
        clk();

        DATA = (data & 0b00000100) >> 2;
        clk();

        DATA = (data & 0b00001000) >> 3;
        clk();

        DATA = (data & 0b00010000) >> 4;
        clk();

        DATA = (data & 0b00100000) >> 5;
        clk();

        DATA = (data & 0b01000000) >> 6;
        clk();

        DATA = (data & 0b10000000) >> 7;
        clk();
        LATCH = 1;
    }

    void clk() {
        CLK = 1;
        CLK = 0;
    }


#endif	/* 74595_H */