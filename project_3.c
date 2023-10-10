//Names: Aidan Stoner, Marc Santacapita, Erin Cardino, and Shaunessy Reynolds
//Date: 10/16/13
//Course: ELEC-3371
//Description: PE13 and PE15 need to be high in order for the 7-segments to display a number. PE11 switch which
//             7-segment is being displayed, PE8, PE10, PE12, & PE14 are data pins which will display the
//             decimal version of their binary value 0-9.
//kah bruh -nussy
//test tset test
//bruh (MORE TESTING
//******************************************************************************
//Global Variables:
int num1 = 0xA500; //Variables for 7-seg display
int prevPA0 = 0; //holds previous value of PA0 for falling/rising edge purposes
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
//Objective 3
     asm{
          LOOP:
               MOVW R0, #LO_ADDR(GPIOA_IDR+0)       ;Puts the low address of GPIOA_IDR into R0
               MOVT R0, #HI_ADDR(GPIOA_IDR+0)       ;Puts the high address of GPIOA_IDR into R0
               LDR R1, [R0]                         ;Loads the value saved in R1 into the register with its address saved in R0, in
                                                    ;this case GPIOA_IDR
               AND R3, R1, #1                       ;ANDs R1 with the number 1 in order to clear any high bits in the upper 32 bits
                                                    ;of the register.
               CMP R3, #1                           ;If PA0 is pressed GPIOA_IDR has a value of 1 so R1 is compared to 1 and if
                                                    ;they are the same jumps to LABEL2
               BEQ PAZero
          B LOOP
               
          PAZero:
               MOVW R0, #LO_ADDR(GPIOA_IDR+0)       ;Puts the low address of GPIOA_IDR into R0
               MOVT R0, #HI_ADDR(GPIOA_IDR+0)       ;Puts the high address of GPIOA_IDR into R0
               LDR R1, [R0]                         ;Loads the value saved in R1 into the register with its address saved in R0, in
                                                    ;this case GPIOA_IDR
               AND R3, R1, #1                       ;ANDs R1 with the number 1 in order to clear any high bits in the upper 32 bits
                                                    ;of the register.
               CMP R3, #1                           ;If PA0 is pressed GPIOA_IDR has a value of 1 so R1 is compared to 1 and if
                                                    ;they are the same jumps to LABEL2
               BEQ PAZero
               
               MOVW R0, #LO_ADDR(_num1)       ;Puts the low address of num1 into R0
               MOVT R0, #HI_ADDR(_num1)       ;Puts the high address of num1 into R0
               LDR R2, [R0]                   ;puts the value of num1 into R2
               
               AND R3, R2, #0x800
               CMP R3, #0x800
               BEQ SetLow
               B SetHigh
          
          SetLow:
               MOVW R4, #0xF7FF
               AND R2, R4
          B Display
          
          SetHigh:
               ADD R2, #0x800
          B Display
          
          Display:
               MOVW R0, #LO_ADDR(GPIOE_ODR+0)  ;Get the low address of GPIOE_ODR
               MOVT R0, #HI_ADDR(GPIOE_ODR+0)  ;Get the high address of GPIOE_ODR
               STR R2, [R0]                    ;Puts the value that is saved in R2 into the register whos address is saved in
               
               MOVW R0, #LO_ADDR(_num1)       ;Puts the low address of num1 into R0
               MOVT R0, #HI_ADDR(_num1)       ;Puts the high address of num1 into R0
               STR R2, [R0]                   ;puts the value of num1 into R2
          B LOOP
               
     }
     
}