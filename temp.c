#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "ifttt.h"

int main(int argc, char **argv) {
        FILE *fp;
        time_t secs;
        int read;
        float lowest = 0.0;
        int lowestI;
        float highest = 0.0;
        int highestI;
        float msg;
        float new;
        int newI;
        char nums[6];
        char high[12];
        char low[12];
        char newS[12];

        while (1) {
                secs = time(NULL);
                while(time(NULL) < secs + 1) {
                }
                fp = fopen("/sys/bus/w1/devices/28-01131bd2cee2/w1_slave", "r");
                if (fp == NULL) {
                        perror("opening file failed");
                        exit(1);
                }
                fseek(fp, 69, SEEK_SET);
                read = fread(nums, 5, 1, fp);
                if (read == 0) {
                        perror("reading file failed");
                        exit(1);
                }
                /* printf("%s\n", nums); */
                sscanf(nums, "%f", &new);
                new /= 1000;
                if (msg == 0.0) {
                        printf("new reading\n");
                        msg = new;
                        highest = new;
                        highestI = new;
                        lowest = new;
                        lowestI = new;
                        newI = new;
                        sprintf(high, "%d", highestI);
                        sprintf(low, "%d", lowestI);
                        sprintf(newS, "new read %d", newI);
                        ifttt("https://maker.ifttt.com/trigger/temp_walker/with/key/YoqUlnq-xfeJkIjhkrcFP", newS, high, low);
                        sprintf(newS, "%d", newI);
                }
                if (new - msg > 1) {
                        if (new > highest) {
                                printf("new highest\n");
                                highest = new;
                                highestI = new;
                                sprintf(high, "new high %d", highestI);
                                ifttt("https://maker.ifttt.com/trigger/temp_walker/with/key/YoqUlnq-xfeJkIjhkrcFP", newS, high, low);
                                high[0] = '\0';
                        } else {
                                msg = new;
                                newI = new;
                                sprintf(high, "%d", highestI);
                                sprintf(low, "%d", lowestI);
                                sprintf(newS, "%d", newI);
                                ifttt("https://maker.ifttt.com/trigger/temp_walker/with/key/YoqUlnq-xfeJkIjhkrcFP", newS, high, low);
                        }
                }
                if (new - msg < -1) {
                        if (new < lowest) {
                                printf("new lowest\n");
                                lowest = new;
                                lowestI = new;
                                sprintf(low, "new low %d", lowestI);
                                ifttt("https://maker.ifttt.com/trigger/temp_walker/with/key/YoqUlnq-xfeJkIjhkrcFP", newS, high, low);
                                low[0] = '\0';
                        } else {
                                msg = new;
                                newI = new;
                                sprintf(high, "%d", highestI);
                                sprintf(low, "%d", lowestI);
                                sprintf(newS, "%d", newI);
                                ifttt("https://maker.ifttt.com/trigger/temp_walker/with/key/YoqUlnq-xfeJkIjhkrcFP", newS, high, low);
                        }
                }
                printf("new %.3f\t high %.3f\t low %.3f\n", new, highest, lowest);
                fclose(fp);
        }
        return 0;
}
