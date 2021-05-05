
unsigned int xx = 0;
  
void Interrupt(){
  if (TMR0IF_bit){
    TMR0IF_bit = 0;
    TMR0       = 101;
    RB4_BIT =1;
    Delay_ms(2);
    RB4_BIT = 0;

  }
}


void main() {
       volatile unsigned int x;
       volatile unsigned int y;
       volatile unsigned int Read_potentiometer = 0;
       volatile unsigned char Duty1;
       
       OSCCON = 0b00110000;              //BITS 6,5 and 4 =  111 = 8 MHz   101 = 2 MHz   011 = 500 kHz    page 64
       
       TRISA = 0b00000001;
       PORTA = 0;
       TRISB = 0;
       PORTB = 0;
       TRISC = 0;
       PORTC = 0;
       TRISE = 0;
       PORTE = 0;
       
   //    OPTION_REG.RBPU           //PAGE 77  RBPU IS MISSING in Mikro C!  OPTION REGISTER
       OPTION_REG = 0b10000000;     // 1 = PORTB pull-ups are disabled
       OPTION_REG.T0CS = 0;        // bit 5 T0CS: TMR0 Clock Source Select bit  0 = Internal instruction cycle clock (FOSC/4)   OR INPUT FROM T0CKI PIN WHICH IS RA4 PIN 6 ON MY CHIP PAGE 5 & PAGE 75
       OPTION_REG.PS2 = 0;         // Prescaler Rate Select bits
       OPTION_REG.PS1 = 1;         // Prescaler Rate Select bits
       OPTION_REG.PS0 = 1;         // Prescaler    page 77
       TMR0           = 100;
       INTCON.GIE    = 1;           //PAGE 220  Global Interrupt Enable bit, GIE
       INTCON.TMR0IE = 1;           //Timer0 Overflow Interrupt Enable Bit

       
      // 500'000 Hz / 4 = 125'000 Hz
      // 125'000 / 16 =  7812.5 Hz
      // 1/ 7812.5 shows a period of  0.000128   128 us
      // 8 bit timer   256 * 0.000128 =   0.032768
      // We want 50 Hz which is 20ms
      // 0.02 /  0.000128 =  156.25 COUNTS OF OUR TIMER
      // OUR TIMER ROLLS OVER AT 256 COUNTS SO SUBTRACT 156 FROM 256 = 100
      // PRE LOAD TIMER 0 L REGISTER WITH 100, IT WILL COUNT THE REMAINING 156
      // 156 COUNTS OF 0.000128 = 0.019968  OR 19.968 MILLISECONDS  OR 50.08012820512821 Hz
      
      
      PWM1_Init(51);     //PWM ON RC2_BIT
      PWM1_Set_Duty(10);
      PWM1_Start();


      ADC_Init();

      //pic16F886 with internal oscillator driving timer zero and servo

  while(1){
  

  
       Read_potentiometer = ADC_Get_Sample(0);

       Read_potentiometer = 0.052  * Read_potentiometer;

       PWM1_Set_Duty(Read_potentiometer);
       Delay_ms(10);
       

      

       
       
  
  
  }


}