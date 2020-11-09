#include <unistd.h>
#include <stdio.h>
#include <sys/select.h>


struct State {
  unsigned long Out;
  unsigned long Time; 
  unsigned long Next[4];};
typedef const struct State STyp;

#define goN   0
#define waitN 1
#define goE   2
#define waitE 3

//Memory Address, Time and Array of Outcomes
STyp FSM[4]={
 {0x21,3000,{goN,waitN,goN,waitN}},
 {0x22, 500,{goE,goE,goE,goE}},
 {0x0C,3000,{goE,goE,waitE,waitE}},
 {0x14, 500,{goN,goN,goN,goN}}};

unsigned long S;  // index to the current state

unsigned long Input = 0;

// cc.byexamples.com calls this int kbhit(), to mirror the Windows console
//  function of the same name.  Otherwise, the code is the same.

//Check to see if there is any input in the file descriptor
int inputAvailable()  
{
  struct timeval tv;
  fd_set fds;
  tv.tv_sec = 0;
  tv.tv_usec = 0;
  FD_ZERO(&fds);
  FD_SET(STDIN_FILENO, &fds);
  select(STDIN_FILENO+1, &fds, NULL, NULL, &tv);
  return (FD_ISSET(0, &fds));
}

int main()
{ 
    char data[200];
    int oldOutput = 0;

    S = goN;

    printf("Press enter to activate sensor:\n");

    while(1){
       /* add in  here your emulation of the code */

      /* TODO replace the following line with a printf of the current value of lights
        The value of the lights is in FSM[S].Out */

      int LIGHTS = FSM[S].Out;
      
      if (LIGHTS != oldOutput) {

        oldOutput++;

        if (LIGHTS & 1) {
          printf("North Green: lights %X state %lu\n", LIGHTS, S);
          oldOutput = LIGHTS;
        } else if (LIGHTS & 2) {
          printf("North Yellow: lights %X state %lu\n", LIGHTS, S);
        } else if (LIGHTS & 8) {
          printf("East Green: lights %X state %lu\n", LIGHTS, S);
          oldOutput = LIGHTS;
        } else if (LIGHTS & 4) {
          printf("East Yellow: lights %X state %lu\n", LIGHTS, S);
          Input = 3;
        }
          usleep(1000 * FSM[S].Time);
          S = FSM[S].Next[Input];
        }

        if (inputAvailable()) {
          Input = 0;
          printf("\nPlease enter a value:\n");
          scanf("%s" , data);

/* TODO  Set the input value to 00 or 01 or 10 or 11 binary i.e. 0,1,2,3 decimal depending on the input.
         For example If the user enters N set Input to 2 decimal i.e. 10 binary. */

          if (data[0] == 'N') {
            printf("North selected\n");
            Input = 2;
          }
          else if (data[0] == 'E') {
             printf("East selected\n");
             Input = 1;
          }
          else if (data[0] == 'B') {
            printf("Both buttons on\n");
             Input = 3;
          }
          else {
            printf("Both buttons off\n");
             Input = 0;
          }

          S = FSM[S].Next[Input];
      }
    }
}