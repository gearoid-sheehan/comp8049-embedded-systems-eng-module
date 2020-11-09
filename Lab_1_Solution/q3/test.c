#include <stdint.h>
 
typedef volatile struct {
 uint32_t DR;
 uint32_t RSR_ECR;
 uint8_t reserved1[0x10];
 const uint32_t FR;
 uint8_t reserved2[0x4];
 uint32_t LPR;
 uint32_t IBRD;
 uint32_t FBRD;
 uint32_t LCR_H;
 uint32_t CR;
 uint32_t IFLS;
 uint32_t IMSC;
 const uint32_t RIS;
 const uint32_t MIS;
 uint32_t ICR;
 uint32_t DMACR;
} pl011_T;
 
enum {
 RXFE = 0x10,
 TXFF = 0x20,
};
 
pl011_T * const UART0 = (pl011_T *)0x101f1000;
pl011_T * const UART1 = (pl011_T *)0x101f2000;
pl011_T * const UART2 = (pl011_T *)0x101f3000;
 
static inline char upperchar(char c) {
 if((c >= 'a') && (c <= 'z')) {
  return c - 'a' + 'A';
 } else {
  return c;
 }
}

static void uart_echo(pl011_T *uart) {
 if ((uart->FR & RXFE) == 0) {
	char ch = uart->DR;
  while(uart->FR & TXFF);
  	uart->DR = ch;
  	uart->DR = upperchar(uart->DR);
 }
}
 
void print_uart0(const char *s) {
 while(*s != '\0') { /* Loop until end of string */
 UART0->DR = (unsigned int)(*s); /* Transmit char */
 s++; /* Next char */
 }
}

struct State {

  unsigned long Out;

  unsigned long Time; 

  unsigned long Next[4];};

typedef const struct State STyp;

#define goN   0

#define waitN 1

#define goE   2

#define waitE 3

STyp FSM[4]={

 {0x21,3000,{goN,waitN,goN,waitN}},

 {0x22, 500,{goE,goE,goE,goE}},

 {0x0C,3000,{goE,goE,waitE,waitE}},

 {0x14, 500,{goN,goN,goN,goN}}};

unsigned long S;  // index to the current state

unsigned long Input;

void c_entry() {
S = goN; 
unsigned int light;
int change =0;
int ch;

print_uart0("Press enter to activate sensor:\n");

 for(;;) {
 
    //emulate this line LIGHT = FSM[S].Out;  // set lights
    light = FSM[S].Out;
      if (light != change) {
        change++;
      if (light & 1) {
        print_uart0("North Green\n");
        change = light;
      } else if (light & 2) {
        print_uart0("North Yellow\n");
      } else if (light & 8) {
        print_uart0("East Green\n");
        change = light;
      } else if (light & 4) {
        print_uart0("East Yellow\n");
        Input = 3;
      }

 // TODO (some kind of delay) emulate this line   SysTick_Wait10ms(FSM[S].Time);
      for (int i = 0; i < 100000 * FSM[S].Time; i++)
      {
        int x = i;
      }

      S = FSM[S].Next[Input]; 
   }
	
 //  emulate  Input = SENSOR;     // read sensors
   if ((UART0->FR & RXFE) == 0) {
      // TODO need to emulate input for the two buttons here. That is press E for east button, 
      // N for North button and B for both buttons
      change =1;
      ch = UART0->DR;
      
      if (ch == 'N') {
        print_uart0("North selected\n");
    		Input = 2;
  	  }
  	  else if (ch == 'E') {
     		print_uart0("East selected\n");
     		Input = 1;
  	  }
  	  else if (ch == 'B') {
    		print_uart0("Both buttons on\n");
     		Input = 3;
  	  }
  	  else {
    		print_uart0("Both buttons off\n");
     		Input = 0;
      }

        S = FSM[S].Next[Input];
	    }
    }
}