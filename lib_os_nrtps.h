#ifndef LIB_OS_NRTPS_H
#define LIB_OS_NRTPS_H

#include <stdint.h>

#ifndef LIB_OS_NRTPS__EVENT_ARRAY_SIZE
#define LIB_OS_NRTPS__EVENT_ARRAY_SIZE ( uint8_t )5U
#warning "DEFAULT value used in lib_os_nrtps: LIB_OS_NRTPS__EVENT_ARRAY_SIZE"
#endif

struct s_lib_os_nrtps_event
{
    int8_t status;    /* general status of this entry */
    uint64_t timestamp; /* timestamp this event should occur */
    void( *callback_function )( void* ); /* callback to function */
    void* argument_pointer; /* pointer to arguments required by callback */
};

enum e_lib_os_nrtps_status
{
    enum_LIB_OS_NRTPS_STATUS__OUT_OF_SPACE = -2,
    enum_LIB_OS_NRTPS_STATUS__NOT_FOUND = -1,
    enum_LIB_OS_NRTPS_STATUS__NONE = 0,
};

void lib_os_nrtps_init( void );
enum e_lib_os_nrtps_status lib_os_nrtps_set(
    uint64_t period_tick,
    void( *function )( void* ),
    void* arguments
    );
enum e_lib_os_nrtps_status lib_os_nrtps_clear(
    void( *function )( void* )
    );
void lib_os_nrtps_start( void );
void lib_os_nrtps_end( void );

#ifdef DEPLOYMENT_OPTION_RUN_UNIT_TESTS
void run_unit_tests__lib_os_nrtps( void );
#endif /* DEPLOYMENT_OPTION_RUN_UNIT_TESTS */

#endif /* LIB_OS_NRTPS_H */
