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
alt_u32 MODES_BASE = 0x21020;
// System Counters Base: 0x21000
alt_u32 counter_BASE = 0x21000;
// Random Pattern Base: 0x21010
alt_u32 pattern_BASE = 0x21010;

int main() {
	alt_putstr("Project2 - CSCE 313\n");
	
	// mode var alt_u8 0x0
	alt_u8 mode = 0x0;
	
	// counter var alt_u8 0x0
	alt_u8 counter = 0x0;
	
	// Original: rand var alt_u32 0x0
	// Has to be 32 to work with all 18 bits of red LEDs
	alt_u32 random = 0x0;
	
	// num of rand patterns int
  // not gonnal lie not really sure what this is yet
	int patterns = 3;
	
	// Loop never exits
	while(1) {
	
		// read mode data from board
		mode = IORD_ALTERA_AVALON_PIO_DATA(MODES_BASE);
	
		//********** MODE 1 **********
		// check if the mode is 1
		if(mode == 0x1){
			// output to board for checking purposes
			alt_putstr("LEDs light on MODE 1\n");
			
			// How to light pattern_BASE LEDs
			IOWR_ALTERA_AVALON_PIO_DATA(pattern_BASE, 0xFFFFFF);
			IOWR_ALTERA_AVALON_PIO_DATA(counter_BASE, 0xFF);
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
        if(modes != 0x2) break;

        // Display in ascending order from counter of loop
        IOWR_ALTERA_AVALON_PIO_DATA(counter_BASE, counter);

        // Count up on counter for next showing
        counter = counter + 0x1;

        // Sleep function so that it counts slow enough for us to see it
        usleep(100000);
      }  // Ending bracket for counter  
		}  // Ending bracket for if mode 2
    
		//********** MODE 3 **********
    
		if(mode == 0x3){	
      // output to string to board for checking purposes
		  alt_putstr("Random Lights on MODE 3\n");
      
			// set all red lights to off
			IOWR_ALTERA_AVALON_PIO_DATA(random_BASE, 0x0);
       
      // Loop through the lights
      while(1) {
        // Check mode while looping...
      	modes = IORD_ALTERA_AVALON_PIO_DATA(MODES_BASE);
        
        // break if mode changes
        if (modes != 0x3) break;

        // get rand value to assign to altera out
        random = rand() % 262144;

        // Sent rand val to altera
        IOWR_ALTERA_AVALON_PIO_DATA(random_BASE, random);

        // Sleep so we can actually see the changes
        usleep(100000);
      }  // Ending bracket while mode 3
    }  // Ending bracket if mode 3
	}  // Ending bracket large while loop
}  // Ending bracket main

