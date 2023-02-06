#ifndef __Display__
#define __Display__


//_____________________________________________________________________________________________________________________

/* Start Color Functions */

void Black ();

void Red ();

void Green ();

void Yellow ();

void Blue ();

void Purple ();

void Cyan ();

void Reset ();

void Set_Color_Console (); /* This functions resets the color of the console */

void Set_Width_Console (); /* This functions resets the width of the console */

/* End Color Functions */

//_____________________________________________________________________________________________________________________

/* Start Some output functions */

/* This function goes up with the cursor n times */

void Go_up ( int times );
    
/* This functions goes up with the cursor and clears the line */

void Go_up_Clear_line ( int times );

/* Thid function clears the current line */

void Clear_line ();

/* This functions clears the screen */

void Clear_Screen();

/* End Some output functions */

//_____________________________________________________________________________________________________________________

#endif