// Lcd pinout settings
sbit LCD_RS at RB0_bit;
sbit LCD_EN at RB1_bit;
sbit LCD_D4 at RB2_bit;
sbit LCD_D5 at RB3_bit;
sbit LCD_D6 at RB4_bit;
sbit LCD_D7 at RB5_bit;

// Pin direction
sbit LCD_RS_Direction at TRISB0_bit;
sbit LCD_EN_Direction at TRISB1_bit;
sbit LCD_D4_Direction at TRISB2_bit;
sbit LCD_D5_Direction at TRISB3_bit;
sbit LCD_D6_Direction at TRISB4_bit;
sbit LCD_D7_Direction at TRISB5_bit;

void main() {
     int temperature, ldr;
     ADC_init();
     LCD_init();
     LCD_CMD(_LCD_CLEAR);
     LCD_CMD(_LCD_CURSOR_OFF);



     trisA.b1 = 0;
     portA.b1 = 0;
     
     trisC.b6 = 1;
     trisC.b5 = 0;
     portC.b5 = 0;

     trisC.b7 = 0;
     portC.b7 = 0;

     trisD = 0;
     portD = 0;

     while (1)
     {
     
          ldr = ADC_read(0);
         if (ldr > 300)
         {
             portD = 0;     //Lights (leds) activate in low light
         }
         else
         {
             portD = 0xff;
         }
     
         temperature = ADC_read(2);
         temperature = temperature * 500 / 1023;
         if (temperature > 50)
         {
             portC.b7 = 1;           // Activate Buzzer (red led) as fire alarm
             LCD_out(2, 1, "Fire detected!!");
         }
         else
         {
             portC.b7 = 0;
             LCD_out(2, 1, "                 ");
         }

         if (temperature > 25)
         {
             portA.b1 = 1;        // DC motor (yellow led) acts as fan or AC
         }
         else
         {
             portA.b1 = 0;
         }




         if (portC.b6 == 0)             //DOORS control   servo replaced with white led
         {
             portC.b5 = 1;
             delay_ms(200);

             portC.b5 = 0;
             delay_ms(180);
             
             LCD_out(1, 2, "Door opened");

         }
         else
         {
             portC.b5 = 1;
             delay_ms(100);
             portC.b5 = 0;
             delay_ms(190);
             LCD_out(1, 2, "Door closed");
         }

     }
}