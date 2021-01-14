
#include "Stream.h"
int streamGet(struct Stream *s,int * finished){
    *finished =0;
 //printf("streamGet cnt = %d size =%d\n",s->cnt,s->size);
    if (s->cnt < s->size){
      // printf("streamGet %d\n",s->buffer[s->cnt]);
       return s->buffer[s->cnt++];
    }
    else
       *finished = 1;
return -1;
}

/*
peak examples from
http://sofdem.github.io/gccat/gccat/Cpeak.html
(2,⟨1,1,4,8,6,2,7,1⟩)
(0,⟨1,1,4,4,4,6,7,7⟩)
(4,⟨1,5,4,9,4,6,2,7,6⟩)
*/
main(){

int data1[] = {1,1,4,8,6,2,7,1};
int data2[] ={1,5,4,9,4,6,2,7,6};
struct Stream s;

s.buffer = data1;
s.size = 8;
s.cnt =0;

int val = peak(&s,2);
printf("result for peak({1,1,4,8,6,2,7,1},2) i.e. are there two peaks in the data? %d\n",val);

s.buffer = data2;
s.size = 9;
s.cnt =0;

val = peak(&s,4);
printf("result for peak({1,5,4,9,4,6,2,7,6},4) i.e. are there 4 peaks in the data? %d\n",val);

val = peak(&s,5);
printf("result for peak({1,5,4,9,4,6,2,7,6},5) i.e. are there 5 peaks in the data? %d\n",val);
}

