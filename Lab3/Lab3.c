//library to use altera i/o functions
#include "sys/alt_stdio.h"

//library to use altera variable types
#include "alt_types.h"

//library to get all hardware definitions
#include "system.h"

//library that has the definition of pio functions
#include "altera_avalon_pio_regs.h"

//C standard libraries
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>

// System Modes Base: 0x21020
alt_u32 MODES_BASE = 0x21090;
// System Counters Base: 0x21000
alt_u32 counter_BASE = 0x21070;
// Random Pattern Base: 0x21010
alt_u32 pattern_BASE = 0x21080;

// Hex Display base addresses
alt_u32 hex0_BASE = 0x21060;
alt_u32 hex1_BASE = 0x21050;
alt_u32 hex2_BASE = 0x21040;
alt_u32 hex3_BASE = 0x21030;
alt_u32 hex4_BASE = 0x21020;

// bcd_inputs
alt_u32 bcdin_BASE = 0x21010;

// Speed controller
alt_u32 spcont_BASE = 0x21000;

// funct to control speed 
//int spd(alt_u8 num1){
//  if(num1== 0x1){
//    return 300000;
//  } else {
//    return 125000;
//  }
//}

int main() {
	alt_putstr("Project3 - CSCE 313\n");

	// mode var alt_u8 0x0
	alt_u8 mode = 0x0;

	// counter var alt_u8 0x0
	int counter = 0;

	// Original: rand var alt_u32 0x0
	// Has to be 32 to work with all 18 bits of red LEDs
	int random = 0;

	// num of rand patterns int
    // not gonnal lie not really sure what this is yet
	//int patterns = 3;

	// spdvar
	alt_u8 spd = 0x0;

	// Loop never exits
	while(1) {

		// read mode data from board
		mode = IORD_ALTERA_AVALON_PIO_DATA(MODES_BASE);

		//********** MODE 1 **********
		// check if the mode is 1
		if(mode == 0x1){
			// output to board for checking purposes
			alt_putstr("Decoder on MODE 1\n");
      
      while(1) {
        // Check mode while looping...
      	mode = IORD_ALTERA_AVALON_PIO_DATA(MODES_BASE);
        // break if mode changes
        if (mode != 0x1) break;

        // value to be displayed on HEX
        alt_u8 hex_IN = IORD_ALTERA_AVALON_PIO_DATA(bcdin_BASE);


        alt_u8 hex_Disp = 0x0;

        switch(hex_IN) {
        case 0x0: hex_Disp = 0b1000000;
        break;
        case 0x1: hex_Disp = 0b1111001;
        break;
        case 0x2: hex_Disp = 0b0100100;
        break;
        case 0x3: hex_Disp = 0b0110000;
        break;
        case 0x4: hex_Disp = 0b0011001;
        break;
        case 0x5: hex_Disp = 0b0010010;
        break;
        case 0x6: hex_Disp = 0b0000010;
        break;
        case 0x7: hex_Disp = 0b1111000;
        break;
        case 0x8: hex_Disp = 0b0000000;
        break;
        case 0x9: hex_Disp = 0b0011000;
        break;
        case 0xA: hex_Disp = 0b0001000;
        break;
        case 0xB: hex_Disp = 0b0000000;
        break;
        case 0xC: hex_Disp = 0b1000110;
        break;
        case 0xD: hex_Disp = 0b1000000;
        break;
        case 0xE: hex_Disp = 0b0000110;
        break;
        case 0xF: hex_Disp = 0b0001110;
        break;
        }


        // funct call to write to the display
        IOWR_ALTERA_AVALON_PIO_DATA(hex4_BASE, hex_Disp);
        
        spd = IORD_ALTERA_AVALON_PIO_DATA(spcont_BASE);

        // Sleep so we can actually see the changes
        if(spd == 0x1){
           usleep(300000);
         } else {
           usleep(125000);
         }

      }  // Ending bracket while mode 3
		}  // Ending bracket of mode 1 if

		//********** MODE 2 **********

		if(mode == 0x2){
      // output to string to board for checking purposes
		  alt_putstr("Counter Lights on MODE 2\n");

			// set all green lights to off
			IOWR_ALTERA_AVALON_PIO_DATA(counter_BASE, 0x00);

      // Loop through the lights
      for(int i = 0; i < 256; i++) {
        // Check for each loop if the mode has changed, otherwise it is stuck
        mode = IORD_ALTERA_AVALON_PIO_DATA(MODES_BASE);
        if(mode != 0x2) break;

        
        // Counter for hex0
        int hex0_Out = counter % 16;

        alt_u8 hex_Disp0 = 0x0;
        
         switch(hex0_Out) {
        case 0: hex_Disp0 = 0b1000000;
        break;
        case 1: hex_Disp0 = 0b1111001;
        break;
        case 2: hex_Disp0 = 0b0100100;
        break;
        case 3: hex_Disp0 = 0b0110000;
        break;
        case 4: hex_Disp0 = 0b0011001;
        break;
        case 5: hex_Disp0 = 0b0010010;
        break;
        case 6: hex_Disp0 = 0b0000010;
        break;
        case 7: hex_Disp0 = 0b1111000;
        break;
        case 8: hex_Disp0 = 0b0000000;
        break;
        case 9: hex_Disp0 = 0b0011000;
        break;
        case 10: hex_Disp0 = 0b0001000;
        break;
        case 11: hex_Disp0 = 0b0000000;
        break;
        case 12: hex_Disp0 = 0b1000110;
        break;
        case 13: hex_Disp0 = 0b1000000;
        break;
        case 14: hex_Disp0 = 0b0000110;
        break;
        case 15: hex_Disp0 = 0b0001110;
        break;
        }
        
        // Counter for hex1
        int hex1_Out = counter / 16;

        alt_u8 hex_Disp1 = 0x0;
        
        switch(hex1_Out) {
        case 0: hex_Disp1 = 0b1000000;
        break;
        case 1: hex_Disp1 = 0b1111001;
        break;
        case 2: hex_Disp1 = 0b0100100;
        break;
        case 3: hex_Disp1 = 0b0110000;
        break;
        case 4: hex_Disp1 = 0b0011001;
        break;
        case 5: hex_Disp1 = 0b0010010;
        break;
        case 6: hex_Disp1 = 0b0000010;
        break;
        case 7: hex_Disp1 = 0b1111000;
        break;
        case 8: hex_Disp1 = 0b0000000;
        break;
        case 9: hex_Disp1 = 0b0011000;
        break;
        case 10: hex_Disp1 = 0b0001000;
        break;
        case 11: hex_Disp1 = 0b0000000;
        break;
        case 12: hex_Disp1 = 0b1000110;
        break;
        case 13: hex_Disp1 = 0b1000000;
        break;
        case 14: hex_Disp1 = 0b0000110;
        break;
        case 15: hex_Disp1 = 0b0001110;
        break;
        }
        
        // Display of first val to HEX0 in ascending order from counter of loop
        IOWR_ALTERA_AVALON_PIO_DATA(hex0_BASE, hex_Disp0);

        // Display of second val to HEX1 in ...
        IOWR_ALTERA_AVALON_PIO_DATA(hex1_BASE, hex_Disp1);

        // Count up on counter for next showing
        counter = counter + 1;
        
        spd = IORD_ALTERA_AVALON_PIO_DATA(spcont_BASE);
        
        // Sleep so we can actually see the changes
        if(spd == 0x1){
           usleep(300000);
         } else {
           usleep(125000);
         }
      }  // Ending bracket for counter
		}  // Ending bracket for if mode 2

		//********** MODE 3 **********

		if(mode == 0x3){
      // output to string to board for checking purposes
		  alt_putstr("Random Lights on MODE 3\n");

			// set all red lights to off
			IOWR_ALTERA_AVALON_PIO_DATA(pattern_BASE, 0x0);

      // Loop through the lights
		while(1) {
        // Check mode while looping...
    	  	mode = IORD_ALTERA_AVALON_PIO_DATA(MODES_BASE);

      		// break if mode changes
      		if (mode != 0x3) break;

        	// get rand value to assign to altera out
        	random = rand() % 262144;
      
        // Counter for hex0
        int hex0_Out = random % 16;

        alt_u8 hex_Disp2 = 0x0;
        
         switch(hex2_Out) {
        case 0: hex_Disp2 = 0b1000000;
        break;
        case 1: hex_Disp2 = 0b1111001;
        break;
        case 2: hex_Disp2 = 0b0100100;
        break;
        case 3: hex_Disp2 = 0b0110000;
        break;
        case 4: hex_Disp2 = 0b0011001;
        break;
        case 5: hex_Disp2 = 0b0010010;
        break;
        case 6: hex_Disp2 = 0b0000010;
        break;
        case 7: hex_Disp2 = 0b1111000;
        break;
        case 8: hex_Disp2 = 0b0000000;
        break;
        case 9: hex_Disp2 = 0b0011000;
        break;
        case 10: hex_Disp2 = 0b0001000;
        break;
        case 11: hex_Disp2 = 0b0000000;
        break;
        case 12: hex_Disp2 = 0b1000110;
        break;
        case 13: hex_Disp2 = 0b1000000;
        break;
        case 14: hex_Disp2 = 0b0000110;
        break;
        case 15: hex_Disp2 = 0b0001110;
        break;
        }
        
        // Counter for hex1
        int hex1_Out = random / 16;

        alt_u8 hex_Disp3 = 0x0;
        
        switch(hex1_Out) {
        case 0: hex_Disp3 = 0b1000000;
        break;
        case 1: hex_Disp3 = 0b1111001;
        break;
        case 2: hex_Disp3 = 0b0100100;
        break;
        case 3: hex_Disp3 = 0b0110000;
        break;
        case 4: hex_Disp3 = 0b0011001;
        break;
        case 5: hex_Disp3 = 0b0010010;
        break;
        case 6: hex_Disp3 = 0b0000010;
        break;
        case 7: hex_Disp3 = 0b1111000;
        break;
        case 8: hex_Disp3 = 0b0000000;
        break;
        case 9: hex_Disp3 = 0b0011000;
        break;
        case 10: hex_Disp3 = 0b0001000;
        break;
        case 11: hex_Disp3 = 0b0000000;
        break;
        case 12: hex_Disp3 = 0b1000110;
        break;
        case 13: hex_Disp3 = 0b1000000;
        break;
        case 14: hex_Disp3 = 0b0000110;
        break;
        case 15: hex_Disp3 = 0b0001110;
        break;
        }
        
        // Display of first val to HEX0 in ascending order from counter of loop
        IOWR_ALTERA_AVALON_PIO_DATA(hex0_BASE, hex_Disp2);

        // Display of second val to HEX1 in ...
        IOWR_ALTERA_AVALON_PIO_DATA(hex1_BASE, hex_Disp3);

        spd = IORD_ALTERA_AVALON_PIO_DATA(spcont_BASE);
      
        // Sleep so we can actually see the changes
        	if(spd == 0x1){
        		usleep(300000);
        	} else {
        		usleep(125000);
        	}
      	  }  // Ending bracket while mode 3
		}  // Ending bracket if mode 3
	}  // Ending bracket large while loop
}  // Ending bracket main
