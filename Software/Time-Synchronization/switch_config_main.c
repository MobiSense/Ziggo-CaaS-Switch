#include "tsn_drivers/rtc.h"
#include "tsn_drivers/tsu.h"
#include "tsn_drivers/uio.h"
#include "tsn_drivers/gcl.h"
#include "config.h"

int main () {
    void *ptr, *ptr2;
	ptr = uio_init("/dev/uio0");
	gcl_init(ptr);
	rtc_init(ptr);
	tsu_init(ptr);

	ptr2 = switch_rule_uio_init();
	switch_rule_init(ptr2); // clear all existing rules.

    printf ("--- Start setting up Switch Rule. ---\r\n");
	set_switch_rule_ring3();
	printf ("--- Finish setting up Switch Rule. ---\r\n");

	printf ("--- Start setting up GCL. ---\r\n");
	set_gcl_ring3();
	printf ("--- Finish setting up GCL. ---\r\n");
    return 0;
}