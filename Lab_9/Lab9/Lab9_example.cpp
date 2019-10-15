/* ECE3220 Lab9_example.cpp
 * Author: Luis Rivera
 * 
 * This program shows how to use wiringPi on the Raspberri Pi 3 to turn on and off
 * an LED on the auxiliary board.

  Compile using -lwiringPi
	g++ Lab9_example.c -o Lab9_example -lwiringPi
		or
	add wiringPi to the linker (-l), if using Eclipse
 */
 
#include <iostream>
#include <unistd.h>		// sleep, usleep functions
#include <wiringPi.h>	// needed for the wiringPi functions

#define LED_RED 8		// wiringPi number corresponding to GPIO2.
#define LED_YEL	9		//Check Figures 2 and 3 in the Lab9 guide.
#define LED_GRN 7
#define LED_BLU 21

#define BTN_1	27
#define BTN_2	0
#define BTN_3	1
#define BTN_4	24
#define BTN_5	28

int main(int argc, char **argv)
{
	wiringPiSetup();	// wiringPiSetupGpio() could be used. The numbers for the ports would
						// need to match the RPi GPIO pinout.
	
	pinMode(LED_RED, OUTPUT);	// Configure GPIO2, which is the one connected to the red LED.
	pinMode(LED_YEL, OUTPUT);
	pinMode(LED_GRN, OUTPUT);
	pinMode(LED_BLU, OUTPUT);
	
	pinMode(BTN_1, INPUT);
	pinMode(BTN_2, INPUT);
	pinMode(BTN_3, INPUT);
	pinMode(BTN_4, INPUT);
	pinMode(BTN_5, INPUT);

	// The program will turn off the red LED, sleep for a while, then on, sleep, off, on and off.
	// You could use loops, if you wanted/needed.
	digitalWrite(LED_RED, LOW);
	digitalWrite(LED_YEL, LOW);
    digitalWrite(LED_GRN, LOW);
    digitalWrite(LED_BLU, LOW);
	usleep(500000);
	digitalWrite(LED_RED, HIGH);
	digitalWrite(LED_YEL, HIGH);
    digitalWrite(LED_GRN, HIGH);
    digitalWrite(LED_BLU, HIGH);
    usleep(500000);
	digitalWrite(LED_RED, LOW);
	digitalWrite(LED_YEL, LOW);
    digitalWrite(LED_GRN, LOW);
    digitalWrite(LED_BLU, LOW);
    usleep(500000);
    
	digitalWrite(LED_RED, HIGH);
	usleep(100000);
	digitalWrite(LED_YEL, HIGH);
	usleep(100000);
    digitalWrite(LED_GRN, HIGH);
    usleep(100000);
    digitalWrite(LED_BLU, HIGH);
    usleep(100000);
	digitalWrite(LED_RED, LOW);
	usleep(100000);
	digitalWrite(LED_YEL, LOW);
	usleep(100000);
    digitalWrite(LED_GRN, LOW);
    usleep(100000);
    digitalWrite(LED_BLU, LOW);
    usleep(100000);

    std::cout << "PRESS BUTTON 5 TO QUIT\n";
    while(digitalRead(BTN_5) != 1) {
    	if(digitalRead(BTN_1) == 1) {
    		digitalWrite(LED_RED,HIGH);
    		sleep(1);
    		digitalWrite(LED_RED,LOW);
    	}
    	if(digitalRead(BTN_2) == 1) {
    		digitalWrite(LED_YEL,HIGH);
    		sleep(1);
    		digitalWrite(LED_YEL,LOW);
    	}
    	if(digitalRead(BTN_3) == 1) {
    		digitalWrite(LED_GRN,HIGH);
    		sleep(1);
    		digitalWrite(LED_GRN,LOW);
    	}
    	if(digitalRead(BTN_4) == 1) {
    		for(int i=0; i<10; i++) {
				digitalWrite(LED_RED, HIGH);
				usleep(100000);
				digitalWrite(LED_YEL, HIGH);
				usleep(100000);
				digitalWrite(LED_GRN, HIGH);
				usleep(100000);
				digitalWrite(LED_BLU, HIGH);
				usleep(100000);
				digitalWrite(LED_RED, LOW);
				usleep(100000);
				digitalWrite(LED_YEL, LOW);
				usleep(100000);
				digitalWrite(LED_GRN, LOW);
				usleep(100000);
				digitalWrite(LED_BLU, LOW);
				usleep(100000);
    		}
    	}

    }

    return 0;
}
