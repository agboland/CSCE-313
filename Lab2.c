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
alt_u32 SYSTEM_MODES_BASE = 0x21020;
// System Counters Base: 0x21000
alt_u32 counter_BASE = 0x21000;
// Random Pattern Base: 0x21010
alt_u32 pattern_BASE = 0x21000;

int main() {
	alt_putstr("Project2 - CSCE 313\n");
	
	// mode var alt_u8 0x0
	alt_u8 mode = 0x0;
	
	// counter var alt_u8 0x0
	alt_u8 counter = 0x0;
	
	// Original: rand var alt_u32 0x0
	//
	alt_u32 random = 0x0;
	
	// num of rand patterns int
	int patterns = 3;
	
	// Loop never exits
	while(1) {
	
		// read mode data from board
		mode = IORD_ALTERA_AVALON_PIO_DATA(SYSTEM_MODES_BASE);
	
		//********** MODE 1 **********
		// check if the mode is 1
		if(mode == 0x1){
			// output to board for checking purposes
			alt_putstr("LEDs light on MODE 1\n");
			
			// How to light pattern_BASE LEDs
			IOWR_ALTERA_AVALON_PIO_DATA(pattern_BASE, 0xFF);
			IOWR_ALTERA_AVALON_PIO_DATA(counter_BASE, 0xFF);
		}

		// read mode data from board
		 mode = IORD_ALTERA_AVALON_PIO_DATA(SYSTEM_MODES_BASE);
		
		//********** MODE 2 **********
    // output to string to board for checking purposes
		alt_putstr("Counter Lights on MODE 2\n");
    
		if(mode == 0x2){	
			// set all lights to off
			IOWR_ALTERA_AVALON_PIO_DATA(counter_BASE, 0x00);

      // counter for deciding the LED to turn on
      alt_u8 counter = 0x00;

      // Loop through the lights
      for(int i = 0; i < 256; i++) {
        // Check for each loop if the mode has changed, otherwise it is stuck
        mode = IORD_ALTERA_AVALON_PIO_DATA(SYSTEM_MODES_BASE);
        if(modes != 0x2) break;

        // Display in ascending order from counter of loop
        IOWR_ALTERA_AVALON_PIO_DATA(counter_BASE, counter);

        // Count up on counter for next showing
        counter = counter + 0x1;

        // Sleep function so that it counts slow enough for us to see it
        usleep(100000);
      }
		}
	}
}

