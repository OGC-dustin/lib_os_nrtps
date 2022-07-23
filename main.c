/*
 * OGC Engineering
 * Non Real-Timed Polled Scheduler ( NRTPS )
 * generic main function
 */

#include "app.h"
#include "lib_os_nrtps.h"
#include "hal.h"

int main( void )
{
    lib_os_nrtps_init();
	hal_init();
	app_init();
	lib_os_nrtps_start();
	lib_os_nrtps_end();
    return ( 0U );
}
