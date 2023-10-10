//Names: Aidan Stoner, Marc Santacapita, Erin Cardino, and Shaunessy Reynolds
//Date: 10/16/13
//Course: ELEC-3371
//Description: PE13 and PE15 need to be high in order for the 7-segments to display a number. PE11 switch which
//             7-segment is being displayed, PE8, PE10, PE12, & PE14 are data pins which will display the
//             decimal version of their binary value 0-9.
//******************************************************************************
//Global Variables:
int num1 = 0xA000; //Variables for 7-seg display
int prevPA0, prevPA1 = 0; //holds previous value of PA0 for falling/rising edge purposes
int counter = 0; //counter for objective 4
short PA1pressed = 0;
//******************************************************************************
//Main Function
void main() {
//Initializations
     RCC_APB2ENR |= 1 << 2;  //enables clock for PortA
     RCC_APB2ENR |= 1 << 5;  //enables clock for PortD
     RCC_APB2ENR |= 1 << 6;  //enables clock for PortD    need to choose output port and enable it
     
     GPIOA_CRL = 0x44444444; //Set PortA as an input
     GPIOA_CRH = 0x44444444;
     GPIOD_CRL = 0x44444444; //Set PortD as an input
     GPIOD_CRH = 0x44444444;
     GPIOE_CRL = 0x33333333; //Set PortE as an output for LEDS
     GPIOE_CRH = 0x33333333;
//******************************************************************************
//Objective 2
          GPIOE_ODR = num1;   //sets GPIOE equal to num1 variable which will then be displayed on the MET1155
//******************************************************************************
     //while(1){
//Objective 3
          if(GPIOA_IDR.B0 == 1){
               prevPA0 = 1;
          }
          if(GPIOA_IDR.B0 == 0 & prevPA0 == 1){
               GPIOE_ODR.B11 = ~GPIOE_ODR.B11;
               prevPA0 = 0;
          }
    // }

//******************************************************************************
//objective 4
            for(;;) {
              if(GPIOD_IDR.B4 == 1) PA1pressed = 1;

              if(GPIOD_IDR.B3 == 0 & PA1pressed == 1){
              counter++;
              if(counter == 9) counter = 0;
              }
              
              if(GPIOD_IDR.B4 == 0 & PA1pressed == 1) {
              //while(GPIOD_IDR.B4 != 0){}
              counter++;
              if(counter == 9){
              counter = 0;}


               switch (counter) {
                      case 9: GPIOE_ODR = 0xA000; break;
                      case 0: GPIOE_ODR = 0xA100; break;
                      case 1: GPIOE_ODR = 0xA400; break;
                      case 2: GPIOE_ODR = 0xA500; break;
                      case 3: GPIOE_ODR = 0xB000; break;
                      case 4: GPIOE_ODR = 0xB100; break;
                      case 5: GPIOE_ODR = 0xB400; break;
                      case 6: GPIOE_ODR = 0xB500; break;
                      case 7: GPIOE_ODR = 0xE000; break;
                      case 8: GPIOE_ODR = 0xE100; break;
                      }
               //counter++ ;
               PA1pressed = 0;  
               }
               }
}
               


         

      

