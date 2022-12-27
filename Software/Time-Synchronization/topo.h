#ifndef TOPO_H
#define TOPO_H

extern "C" {
    void setup_topo();
    void setup_gcl();
    void get_ptp_ports(int *ptp_ports);
}
#endif