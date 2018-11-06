#include <stdio.h>
#include "ifttt.h"

int main(int argc, char *argv[])
{

  ifttt("https://maker.ifttt.com/trigger/temp_waler/with/key/YoqUlnq-xfeJkIjhkrcFP", "Low", "High", "New");

/*
  printf("Trying to connect to server\n");
  ifttt("http://red.eecs.yorku.ca:8080/trigger/event/with/key/123", "my1", "my 2", "my 33333"); */
  return 0;
}
