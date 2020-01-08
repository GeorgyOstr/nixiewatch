#include "mcc_generated_files/mcc.h"

#define SDA   TRISCbits.TRISC1
#define SCL   TRISCbits.TRISC0
#define I2C_VCC   LATAbits.LATA6 
#define SDA_W  LATCbits.LATC1    //
#define SCL_W  LATCbits.LATC0    //
#define SDA_R  PORTCbits.RC1    //
#define SCL_R  PORTCbits.RC0    //

#define Button TRISBbits.TRISB3
#define Button_R PORTBbits.RB3
#define Button_W LATBbits.LATB3

void pwm()
{
    //40khz, 95% warm...
    //PR2 = 0b00110001 ;
    //T2CON = 0b00000101 ;
    //CCPR1L = 0b00101111 ;
    //CCP1CON = 0b00011100 ;
    //48khz, 90%
    PR2 = 0b10100110 ;
    T2CON = 0b00000100 ;
    CCPR1L = 0b10010110 ;
    CCP1CON = 0b00011100 ;
}

void pwm_on()
{ 

            TRISCbits.TRISC2 = 1;
            pwm();
            TRISCbits.TRISC2 = 0;

}

void pwm_off()
{

            TRISCbits.TRISC2 = 1;
            //32khz, 80%
            PR2 =       0x00 ;
            T2CON =     0x00 ;
            CCPR1L =    0x00 ;
            CCP1CON =   0x00 ;
            TRISCbits.TRISC2 = 0;

}


void i2c_dly(void)
{
    __delay_us(20);
}

void i2c_init(void)
{
  SDA = 0;
  i2c_dly();
  SCL = 0;
  i2c_dly();
  SCL_W = 0;
  i2c_dly();
  SDA_W = 0;
  i2c_dly();
 
  I2C_VCC = 1;//power for rtc    
  i2c_dly();
  __delay_ms(100); //additional delay for idle

}

void i2c_start(void)
{
  
  SCL_W = 1;
  i2c_dly();
  SDA = 1;
  i2c_dly();
  SDA = 0;
  i2c_dly();
  SCL_W = 0;
  i2c_dly();
}

void i2c_stop(void)
{
  SCL_W = 1;
  i2c_dly();
  SDA = 0;
  i2c_dly();
  SDA = 1;
  i2c_dly();
  SCL_W = 0;
  i2c_dly();

}

unsigned char i2c_rx(char ack)
{
  char x, d=0;
  SDA = 1; 
  i2c_dly();
  
  for(x=0; x<8; x++) {
    d <<= 1;
    SCL_W = 1;
    i2c_dly();
    if(SDA_R) d |= 1;
    i2c_dly();
    SCL_W = 0;
    i2c_dly();
  } 
  
  if(ack){SDA = 0;}
  i2c_dly();
  
  SCL_W = 1;
  i2c_dly();
  SCL_W = 0;
  i2c_dly();
  return d;
}

int i2c_tx(unsigned char d)
{
  char x;
  static int b = 0;
  
  for(x=8; x; x--) {
    if(d&0x80) SDA = 1;
    else SDA = 0;
    i2c_dly();
    SCL_W = 1; 
    i2c_dly();
    SCL_W = 0;
    i2c_dly();
    d <<= 1;
    i2c_dly();
  }
  
  SDA = 1;
  i2c_dly();
  SCL_W = 1;
  i2c_dly();
  if( SDA_R ) {b=1;};
  i2c_dly();
  SCL_W = 0;
  i2c_dly();
  return b;
}



void delay_ms(int time)
{
    __delay_us(1000);
}

void showRight(unsigned char i, long time)
{
    switch(i)
    {
        case 0: LATCbits.LATC7 = 1; delay_ms(time); LATCbits.LATC7 = 0; break; //18
        case 1: LATBbits.LATB2 = 1; delay_ms(time); LATBbits.LATB2 = 0; break; //23
        case 2: LATCbits.LATC6 = 1; delay_ms(time); LATCbits.LATC6 = 0; break; //17
        case 3: LATBbits.LATB5 = 1; delay_ms(time); LATBbits.LATB5 = 0; break; //26
        case 4: LATBbits.LATB4 = 1; delay_ms(time); LATBbits.LATB4 = 0; break; //25
        case 5: LATBbits.LATB6 = 1; delay_ms(time); LATBbits.LATB6 = 0; break; //27
        case 6: LATBbits.LATB7 = 1; delay_ms(time); LATBbits.LATB7 = 0; break; //28
        case 7: LATBbits.LATB1 = 1; delay_ms(time); LATBbits.LATB1 = 0; break; //22
        case 8: LATCbits.LATC5 = 1; delay_ms(time); LATCbits.LATC5 = 0; break; //16
        case 9: LATBbits.LATB0 = 1; delay_ms(time); LATBbits.LATB0 = 0; break; //21
    }
}

void showLeft(unsigned char i, long time)
{
    switch(i)
    {
        case 0: LATAbits.LATA3 = 1; delay_ms(time); LATAbits.LATA3 = 0; break; //5
        case 1: LATAbits.LATA4 = 1; delay_ms(time); LATAbits.LATA4 = 0; break; //6
        case 2: LATAbits.LATA7 = 1; delay_ms(time); LATAbits.LATA7 = 0; break; //9
        case 3: LATAbits.LATA1 = 1; delay_ms(time); LATAbits.LATA1 = 0; break; //3
        case 4: LATAbits.LATA2 = 1; delay_ms(time); LATAbits.LATA2 = 0; break; //4
        case 5: LATAbits.LATA5 = 1; delay_ms(time); LATAbits.LATA5 = 0; break; //7 
    }
}

void show(unsigned char i, long time)
{
    for( ; time; time--)// no initial condition, while time is >0, decrement time each loop
    {
        showLeft((i>>4)&0x0F, 1);
        showRight(i&0x0F, 1);
    }
}


void i2c_setreg(unsigned char address, unsigned char value)
{
    i2c_start();
    
    int debug4 = i2c_tx(0xD0);
    if (debug4==1) { show(13, 1000); }
    
    int debug5 = i2c_tx(address);
    if (debug5==1) { show(24, 1000); }

    int debug6 = i2c_tx(value);
    if (debug6==1) { show(24, 1000); }
  
    i2c_stop();
}

unsigned char i2c_getreg(unsigned char address)
{
        i2c_start();              // send start sequence
        
        int debug1 = i2c_tx(0xD0);             // I2C address with R/W bit clear
        if (debug1==1) { show(11, 1000); }
        
        int debug2 = i2c_tx(address);             // seconds register address
        if (debug2==1) { show(22, 1000); }
        
        i2c_start();              // send start sequence
        
        int debug3 = i2c_tx(0xD1);             // I2C address with R/W bit full
        if (debug3==1) { show(33, 1000); }
        
        char data=0;
        data = i2c_rx(0); 
        
        i2c_stop();              // send stop sequence
        return data;
}

void antiPoison()
{
    show(0x59, 40);
    show(0x48, 30);
    show(0x37, 30);
    show(0x26, 20);
    show(0x15, 20);
    
    show(0x04, 20);
    show(0x13, 20);
    show(0x22, 30);
    show(0x31, 30);
    show(0x40, 40);
}

unsigned char hour_inc(unsigned char hour)
{
    if (hour==0x23){ hour = 0x00; }
    else if(hour == 0x19){hour = 0x20;}
    else if(hour == 0x09){hour = 0x10;}
    else{ hour += 0x01; }
    
    return hour;
}

unsigned char minute_inc(unsigned char minute)
{
    if (minute==0x59){ minute = 0x00; }
    else if(minute == 0x49){minute = 0x50;}
    else if(minute == 0x39){minute = 0x40;}
    else if(minute == 0x29){minute = 0x30;}
    else if(minute == 0x19){minute = 0x20;}
    else if(minute == 0x09){minute = 0x10;}
    else{ minute += 0x01; }
    return minute;
}

void main(void)
{
    
    SYSTEM_Initialize();

    uint16_t adc_value;
    unsigned char adc_mapped;
    
    pwm_on();
    show(0, 1000);
    pwm_off();
    
    Button_W = 1;
    __delay_ms(20);
        
    i2c_init();
    
    // Set time...  
    i2c_setreg(0x01, 0x00);
    i2c_setreg(0x02, 0x30);
    i2c_setreg(0x03, 0x14);
    
    //start clock
    i2c_setreg(0x0C, 0x00);
    
    while(1)
    {
        if((!Button_R)||RE3)
        {
            pwm_on();
            __delay_ms(50);
            char dataSeconds = i2c_getreg(0x01);
            char dataMinutes = i2c_getreg(0x02);
            char dataHours = i2c_getreg(0x03);
            antiPoison();

            show(dataHours, 1000);
            while(!Button_R)
            {
                dataHours = hour_inc(dataHours);
                i2c_setreg(0x03, dataHours);
                show(dataHours, 100);
            }

            show(dataMinutes, 1000);
            while(!Button_R)
            {
                dataMinutes = minute_inc(dataMinutes);
                i2c_setreg(0x02, dataMinutes);
                show(dataMinutes, 100);
            }

            //ADC_SelectChannel(0x00);
            //ADC_StartConversion();
            //adc_value = ADC_GetConversionResult()/18;

            //adc_mapped = (unsigned char)(adc_value/10)<<4 + (unsigned char)(adc_value%10);

            //show(adc_mapped, 1000);

            pwm_off();
        }
        else
        {
            pwm_off();
        }
    }
}