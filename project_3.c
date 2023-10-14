//Names: Aidan Stoner, Marc Santacapita, Erin Cardino, and Shaunessy Reynolds
//Date: 10/16/13
//Course: ELEC-3371
//Description: PE13 and PE15 need to be high in order for the 7-segments to display a number. PE11 switch which
//             7-segment is being displayed, PE8, PE10, PE12, & PE14 are data pins which will display the
//             decimal version of their binary value 0-9.
//******************************************************************************
//Global Variables:
int val = 0xA000;
int num1[10] = {0xA000, 0xA100, 0xA400, 0xA500, 0xB000, 0xB100, 0xB400, 0xB500, 0xE000, 0xE100};
int num2[10] = {0xA800, 0xA900, 0xAC00, 0xAD00, 0xB800, 0xB900, 0xBC00, 0xBD00, 0xE800, 0xE900}; //Variables for 7-seg display initially set to 0
int prevPA0, prevPD0 = 0, prevPD4=0; //holds previous value of PA0 for falling/rising edge purposes
int counter = 0; //counter for objective 4
int test=0;

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
     for(;;){
          GPIOE_ODR = val;   //sets GPIOE equal to num1 variable which will then be displayed on the MET1155
//******************************************************************************
//Objective 3 and Bonus Obj 1

          asm{
               CheckButton:
                    MOVW R0, #LO_ADDR(_val)             ;Puts the low address of num1 into R0
                    MOVT R0, #HI_ADDR(_val)             ;Puts the high address of num1 into R0
                    LDR R2, [R0]                         ;puts the value of num1 into R2
                    
                    MOVW R0, #LO_ADDR(GPIOA_IDR+0)       ;Puts the low address of GPIOA_IDR into R0
                    MOVT R0, #HI_ADDR(GPIOA_IDR+0)       ;Puts the high address of GPIOA_IDR into R0
                    LDR R1, [R0]                         ;Loads the value saved in R1 into the register with its address saved in R0, in
                                                         ;this case GPIOA_IDR
                    AND R3, R1, #1                       ;ANDs R1 with the number 1 in order to clear any high bits in the upper 32 bits
                                                         ;of the register.
                    CMP R3, #1                           ;If PA0 is pressed GPIOA_IDR has a value of 1 so R1 is compared to 1 and if
                                                         ;they are the same jumps to PAZero
                    BNE Display
                    
               PAZero:
                    MOVW R0, #LO_ADDR(GPIOA_IDR+0)       ;Puts the low address of GPIOA_IDR into R0
                    MOVT R0, #HI_ADDR(GPIOA_IDR+0)       ;Puts the high address of GPIOA_IDR into R0
                    LDR R1, [R0]                         ;Loads the value saved in R1 into the register with its address saved in R0, in
                                                         ;this case GPIOA_IDR
                    AND R3, R1, #1                       ;ANDs R1 with the number 1 in order to clear any high bits in the upper 32 bits
                                                         ;of the register.
                    CMP R3, #1                           ;If PA0 is pressed GPIOA_IDR has a value of 1 so R1 is compared to 1 and if
                                                         ;they are the same jumps to PAZero
                    BEQ PAZero

                    MOVW R0, #LO_ADDR(_val)             ;Puts the low address of num1 into R0
                    MOVT R0, #HI_ADDR(_val)             ;Puts the high address of num1 into R0
                    LDR R2, [R0]                         ;puts the value of num1 into R2

                    AND R3, R2, #0x800                   ;ANDs with hexidecimal 800 this is when just bit 11 is high
                    CMP R3, #0x800                       ;looks for if bit 11 is high in GPIOA
                    BEQ SetLow                           ;if it is jumps to setlow
                    B SetHigh                            ;if not jumps to sethigh

               SetLow:
                    MOVW R4, #0xF7FF                     ;sets bit 11 low
                    AND R2, R4
               B Display

               SetHigh:
                    ADD R2, #0x800                       ;sets bit 11 high
               B Display

               Display:
                    MOVW R0, #LO_ADDR(GPIOE_ODR+0)  ;Get the low address of GPIOE_ODR
                    MOVT R0, #HI_ADDR(GPIOE_ODR+0)  ;Get the high address of GPIOE_ODR
                    STR R2, [R0]                    ;Puts the value that is saved in R2 into the register whos address is saved in

                    MOVW R0, #LO_ADDR(_val)       ;Puts the low address of num1 into R0
                    MOVT R0, #HI_ADDR(_val)       ;Puts the high address of num1 into R0
                    STR R2, [R0]                   ;puts the value of num1 into R2
          }

//******************************************************************************
//objective 4
          if(GPIOD_IDR.B0 == 1 & PrevPD0 == 0){
               counter++;
               PrevPD0 = 1;
              if(counter > 9) counter = 0;
          }
          if(GPIOD_IDR.B4 == 1 & PrevPD4 == 0){
              counter--;
              PrevPD4 = 1;
              if(counter < 0) counter = 9;
          }
          if(GPIOE_ODR.B11 == 0){
               switch (counter) {
                    case 0: val = num1[0]; break;
                    case 1: val = num1[1]; break;
                    case 2: val = num1[2]; break;
                    case 3: val = num1[3]; break;
                    case 4: val = num1[4]; break;
                    case 5: val = num1[5]; break;
                    case 6: val = num1[6]; break;
                    case 7: val = num1[7]; break;
                    case 8: val = num1[8]; break;
                    case 9: val = num1[9]; break;
               }
          }
          if(GPIOE_ODR.B11 == 1){
               switch (counter) {
                    case 0: val = num2[0]; break;
                    case 1: val = num2[1]; break;
                    case 2: val = num2[2]; break;
                    case 3: val = num2[3]; break;
                    case 4: val = num2[4]; break;
                    case 5: val = num2[5]; break;
                    case 6: val = num2[6]; break;
                    case 7: val = num2[7]; break;
                    case 8: val = num2[8]; break;
                    case 9: val = num2[9]; break;
               }
          }
          if(GPIOD_IDR.B0 == 0 & PrevPD0 == 1){
                   prevPD0 = 0;
          }
          if(GPIOD_IDR.B4 == 0 & PrevPD4 == 1){
                   prevPD4 = 0;
          }
//******************************************************************************
//Bonus Objective 2

     }
}