/*
 * OGC Engineering
 * Non Real-Timed Polled Scheduler ( NRTPS )
 * library
 */

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include "lib_os_nrtps.h"
#include "hal.h"

struct s_lib_os_nrtps_event event_array[ LIB_OS_NRTPS__EVENT_ARRAY_SIZE ] =
    { 0, 0U, NULL, NULL };

void lib_os_nrtps_init( void )
{
    uint8_t init_index = 0U;
    for ( ; init_index < LIB_OS_NRTPS__EVENT_ARRAY_SIZE; init_index++ )
    {
        event_array[ init_index ].status = 0;
        event_array[ init_index ].timestamp = 0U;
        event_array[ init_index ].callback_function = NULL;
        event_array[ init_index ].argument_pointer = NULL;
    }
    return;
}

enum e_lib_os_nrtps_status lib_os_nrtps_set(
    uint64_t task_period_tick,
    void( *function )( void* ),
    void* arguments
    )
{
    uint8_t set_index = 0U;
    for ( ; set_index < LIB_OS_NRTPS__EVENT_ARRAY_SIZE; set_index++ )
    {
        if ( 0 == event_array[ set_index ].status )
        {
            event_array[ set_index ].status = 1;
            event_array[ set_index ].timestamp =
                hal_get_sys_tick() + task_period_tick;
            event_array[ set_index ].callback_function = function;
            event_array[ set_index ].argument_pointer = arguments;
            return ( enum_LIB_OS_NRTPS_STATUS__NONE );
        }
    }
    return ( enum_LIB_OS_NRTPS_STATUS__OUT_OF_SPACE );
}

enum e_lib_os_nrtps_status lib_os_nrtps_clear(
    void( *function )( void* )
    )
{
    bool task_found = false;
    uint8_t clear_index = 0U;
    for ( ; clear_index < LIB_OS_NRTPS__EVENT_ARRAY_SIZE; clear_index++ )
    {
        if ( ( 1 == event_array[ clear_index ].status )
             && ( function == event_array[ clear_index ].callback_function )
           )
        {
            event_array[ clear_index ].status = 0;
            event_array[ clear_index ].timestamp = 0;
            event_array[ clear_index ].callback_function = NULL;
            event_array[ clear_index ].argument_pointer = NULL;
            task_found = true;
        }
    }

    if ( true == task_found )
    {
        return ( enum_LIB_OS_NRTPS_STATUS__NONE );
    }
    else
    {
        return ( enum_LIB_OS_NRTPS_STATUS__NOT_FOUND );
    }
}

void lib_os_nrtps_start( void )
{
    uint8_t start_index = 0U;
    while ( start_index < LIB_OS_NRTPS__EVENT_ARRAY_SIZE )
    {
        if ( ( 1 == event_array[ start_index ].status )
             && ( event_array[ start_index ].timestamp < hal_get_sys_tick() )
           )
        {
            event_array[ start_index ].status = 0;
            if ( NULL != event_array[ start_index ].callback_function )
            {
                event_array[ start_index ].callback_function( event_array[ start_index ].argument_pointer );
            }
        }
        start_index++;
        if ( LIB_OS_NRTPS__EVENT_ARRAY_SIZE == start_index )
        {
            start_index = 0U;
        }
    }
    return;
}

void lib_os_nrtps_end( void )
{
    /* TODO: report any statistics and clean up before continuing oeprations */
}

#ifdef DEPLOYMENT_OPTION_RUN_UNIT_TESTS
void run_unit_tests__lib_os_nrtps( void )
{
    /* TODO: add setup, call, and response testing for all functions */
}
#endif /* DEPLOYMENT_OPTION_RUN_UNIT_TESTS */
