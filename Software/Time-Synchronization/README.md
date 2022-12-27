# Time Sync + Config for CaaS Switches

This repo contains source code to enable CaaS Switches' time synchronization logic and set up TSN GCL (gate control list), switch forwarding rules (including to dual-DMA).

## Build

```bash
mkdir build
cd build
cmake ..
make
```

After successfully build, there should be two executables: "time_sync_app" & "switch_config"

## Config

The "config" directory contains topology & TSN/CaaS schedule results.

* ***-config.json: topology file, contains node info (type, mac, ptp ports), link between nodes (with ports), and forwarding table.
* ***-schedule.json: schedule file, contains each links' schedule time interval & each CaaS switch's computation time interval.

## Run

* Copy topology & schedule file to build dir

```bash
cp [topology name]-config.json build/config.json
cp [topology name]-schedule.json build/schedule.json
```

* Start time synchronization, initiate GCL & switch forwarding rules as the config file

```bash
./time_sync_app
```

* Update GCL & switch forwarding rules

```bash
./switch_config
```

