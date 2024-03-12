// Andrew Boland 3-12-24
#include "sys/alt_stdio.h"
#include "sys/alt_driver.h"
#include "alt_types.h"
#include "altera_avalon_pio_regs.h"
#include "system.h"
#include <math.h>
#include <sys/alt_alarm.h>
#include "myfile.h"

// add the pixel buffer dma as shown in no.5 of the software requirements in the assignment sheet
#include <altera_up_avalon_video_pixel_buffer_dma.h>

alt_u32 MODES_BASE = 0x201000;

int main()
{

  // declare the mode variable as alt_u8 and initialize with 0
	alt_u8 mode = 0x0;


  // Read pixel buffer (go to no.6 of software requirements in the assignment sheet)
	alt_up_pixel_buffer_dma_dev *my_pixel_buffer;
	my_pixel_buffer = alt_up_pixel_buffer_dma_open_dev("/dev/dma_buffer");

  // Check if the pixel array contains the image (go to no.7 of software requirements in the assignment sheet)
	if(!my_pixel_buffer) printf("Error opening pixel buffer\n");

 // Clear the screen (go to no.8 of software requirements in the assignment sheet)
	alt_up_pixel_buffer_dma_clear_screen(my_pixel_buffer,0);



  while(1) {

  // Read the mode value using IORD_ALTERA_AVALON_PIO_DATA();
	  mode = IORD_ALTERA_AVALON_PIO_DATA(MODES_BASE);



 	// check the mode value. if mode is 0.
	  if(mode == 0x0) {

    	//Clear the screen (go to no.8 of software requirements in the assignment sheet)
		  alt_up_pixel_buffer_dma_clear_screen(my_pixel_buffer,0);
		// display the image (go to no.9 of software requirements in the assignment sheet)
		  alt_up_pixel_buffer_dma_draw(my_pixel_buffer,
		  (myimage[(i*320*3+j*3+2)]) +
		  (myimage[(i*320*3+j*3+1)]<<8) +
		  (myimage[(i*320*3+j*3+0)]<<16),j,i);
    }

	// check the mode value. If mode is 1
	  if(mode == 0x1) {

		//Clear the screen (go to no.8 of software requirements in the assignment sheet)
		  alt_up_pixel_buffer_dma_clear_screen(my_pixel_buffer,0);

    	// Resize the image by 0.5 and display the image (go to no.10 of software requirements in the assignment sheet)
		 double f = 0.5;
		  alt_up_pixel_buffer_dma_draw(my_pixel_buffer,
		  (myimage[(i*320*3+j*3+2)]) +
		  (myimage[(i*320*3+j*3+1)]<<8) +
		  (myimage[(i*320*3+j*3+0)]<<16),j*f,i*f);
	  }


   // check the mode value. If mode is 2.
	  if(mode == 0x2) {

		//Clear the screen (go to no.8 of software requirements in the assignment sheet)
		  alt_up_pixel_buffer_dma_clear_screen(my_pixel_buffer,0);

    	// Resize the image by 2 and display the image (go to no.10 of software requirements in the assignment sheet)
			 double f = 2.0;
			  alt_up_pixel_buffer_dma_draw(my_pixel_buffer,
			  (myimage[(i*320*3+j*3+2)]) +
			  (myimage[(i*320*3+j*3+1)]<<8) +
			  (myimage[(i*320*3+j*3+0)]<<16),j*f,i*f);
	  }

   // check the mode value. If mode is 3.  print the message "Video message" on the console
	  if(mode == 0x3) {
		  alt_putstr("Video Project");
	  }
  }
  return 0;
  }
