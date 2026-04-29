#include <stdio.h>
#include <unistd.h>
#include <openamp/open_amp.h>
#include <metal/alloc.h>

#define RED_LIGHT_TIME 6
#define YELLOW_LIGHT_TIME 3
#define GREEN_LIGHT_TIME 5

const char* states[] = {"red", "green", "yellow"};
int times[]= {RED_LIGHT_TIME, GREEN_LIGHT_TIME, YELLOW_LIGHT_TIME};
const char* payload_path = "/home/nicholas/trafficLight/stato.txt";

int main () {
printf("Initializing application on Linux... \n");

int rpmsg_fd = open("/dev/ttyS0", O_RDWR);
if(rpmsg_fd < 0){
perror("Error: S0 channel was not found \n");
return 1;
}

int state_now = 0;
char flag = '0';

while(1) {
if(state_now > 2)
  state_now = 0;
  
FILE *f = fopen(payload_path, "w");
if(f) {
fprintf(f, "%s|%d", states[state_now], times[state_now]);
fflush(f);
fclose(f);

char flag = '1';
write(rpmsg_fd, &flag, 1);
printf("Command sent to Windows: %s \n", states[state_now]);
} else {printf("ERROR: can't open the file \n");}

sleep(times[state_now]);
state_now = (state_now)+1;
}
return 0;
}
