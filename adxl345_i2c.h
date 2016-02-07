#ifndef ADXL345_I2C_H
#define	ADXL345_I2C_H

#ifdef	__cplusplus
extern "C" {
#endif



#define WR_DATA      0xA6
#define RD_DATA      0xA7
#define BW_RATE      0x2C
#define DATA_FORMAT  0x31
#define PWR_CTL      0x2D
#define X0       0x32
#define X1       0x33
#define Y0       0x34
#define Y1       0x35
#define Z0       0x36
#define Z1       0x37
#define OFSX 0x1E
#define OFSY 0x1F
#define OFSZ 0x20

#define _16G 0b11
#define _8G 0b10
#define _4G 0b01
#define _2G 0b00

#define Hz_3600 0b00001111
#define Hz_1600 0b00001110
#define Hz_800 0b00001101
#define Hz_400 0b00001100
#define Hz_200 0b00001011
#define Hz_100 0b00001010


    void adxl345Write(int add, int data);
    unsigned char adxl345Read(int add);
    void Init_adxl345(int8_t x_offset, int8_t y_offset, int8_t z_offset, int8_t range, unsigned char data_rate);
    void setRange(unsigned char range);
    const char *getX();
    const char *getY();
    const char *getZ();


void adxl345Write(int add, int data)
{
        IdleI2C(); //sprawdzanie, czy magistrala jest w stanie bezczynności
        StartI2C();
        IdleI2C();
        WriteI2C(WR_DATA);
        IdleI2C();
        WriteI2C(add);
        IdleI2C();
        WriteI2C(data);
        IdleI2C();
        StopI2C();

}

unsigned char adxl345Read(int add){
         unsigned char retval;
         IdleI2C();
         StartI2C();
         IdleI2C();
         WriteI2C(WR_DATA);
         IdleI2C();
         WriteI2C(add);
         IdleI2C();
         
         RestartI2C();
         WriteI2C(RD_DATA);
         IdleI2C();
         retval = ReadI2C();
         //AckI2C();
         //data= ReadI2C();
         NotAckI2C();
         StopI2C();
         return retval;
}

void Init_adxl345(int8_t x_offset, int8_t y_offset, int8_t z_offset, int8_t range, unsigned char data_rate){
         setRange(range); //ustawienie zakresu do 16 G, czyli w przybliżeniu 16 * 9.81 m/s2
         __delay_ms(2);
         adxl345Write(PWR_CTL,0x08); //tryb pomiaru
         __delay_ms(2);
         adxl345Write(OFSX, x_offset);
         __delay_ms(2);
         adxl345Write(OFSY, y_offset);
         __delay_ms(2);
         adxl345Write(OFSZ, z_offset);
         __delay_ms(2);
         adxl345Write(BW_RATE, data_rate);
         __delay_ms(2);
}

void setRange(unsigned char range) {
    unsigned char format = adxl345Read(DATA_FORMAT);
    format &= ~0x0F;
    format |= range;
    format |= 0x08;

    adxl345Write(DATA_FORMAT, format);
}

const char *getX()  {
    unsigned char data[2];
    int X;
    float xf;
    char x[10];

    data[0]=adxl345Read(X0); //odczyt młodszego bajtu (LSB) z osi x
    data[1]=adxl345Read(X1); //odczyt starszego bajtu (MSB) z osi x

    X=(int16_t)((((int)data[1]) << 8) | data[0]); //konwersja 2 bajtów do integer

    xf = X*9.81*0.004; //obliczenie warto?ci w m/s2

    sprintf(x,"%.2f", xf); //konwersja zmiennej typu float do string o 2 miejscach po przecinku

    return x; //funkcja getX() zwróci zmienną x typu string
}

const char *getY()  {
    unsigned char data[2];
    int Y;
    float yf;
    char y[10];

    data[0]=adxl345Read(Y0); //odczyt młodszego bajtu (LSB) z osi y
    data[1]=adxl345Read(Y1); //odczyt starszego bajtu (MSB) z osi y

    Y=(int16_t)((((int)data[1]) << 8) | data[0]); //konwersja 2 bajtów do integer

    yf = Y*9.81*0.004; //obliczenie wartości w m/s2

    sprintf(y,"%.2f", yf); //konwersja zmiennej typu float do string o 2 miejscach po przecinku

    return y; //funkcja getY() zwróci zmienną y typu string
}

const char *getZ()  {
    unsigned char data[2];
    int Z;
    float zf;
    char z[10];

    data[0]=adxl345Read(Z0); //odczyt młodszego bajtu (LSB) z osi z
    data[1]=adxl345Read(Z1); //odczyt starszego bajtu (MSB) z osi z

    Z=(int16_t)((((int)data[1]) << 8) | data[0]); //konwersja 2 bajtów do integer

    zf = Z*9.81*0.004; //obliczenie wartości w m/s2

    sprintf(z,"%.2f", zf); //konwersja zmiennej typu float do string o 2 miejscach po przecinku

    return z; //funkcja getZ() zwróci zmienną z typu string
}
#ifdef	__cplusplus
}
#endif

#endif	/* ADXL345_I2C_H */
