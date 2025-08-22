# Hardware: FPGA bitstream & Petalinux system rootfs for TSN Evaluation Toolkit

This repo contains pre-build hardware & system rootfs to boot the **Zynq AX7021** FPGA board from SD card.

## File downloading

Download the following file from [this](https://cloud.tsinghua.edu.cn/d/61ad5a800206451c856d/) public link:

* BOOT.BIN
* boot.scr
* image.ub
* rootfs.tar.gz

## SD card partition

In order to boot the CaaS Switch, you are supposed to have a micro SD card with >32GiB storage. Then use:

```bash
sudo apt-get install gparted
sudo gparted
```

Parition it into two partition below

* BOOT: store boot files from petalinux
  
    Free space preceding (MiB): 4
  
    New size (MiB): 500
  
    File system: fat32
  
    Label: BOOT

* ROOTFS: store debian system rootfs
  
    Free space preceding (MiB): 0
  
    Free space following (MiB): 0
  
    File system: ext4
  
    Label: ROOTFS

## Copy files into SD card

Mound SD card:

```bash
sudo mount /dev/sda1 /media/alinx/BOOT/
sudo mount /dev/sda2 /media/alinx/ROOTFS/
```

Remove original files:

```bash
sudo rm -rf /media/alinx/BOOT/* /media/alinx/ROOTFS/*
```

Copy files:

```bash
sudo cp BOOT.BIN boot.scr image.ub /media/alinx/BOOT

sudo tar -zxvf rootfs.tar.gz -C /media/alinx/ROOTFS
sudo cp -r ~/init_os.sh /media/alinx/ROOTFS/home/root/init_os.sh 
sync
sudo chown root:root /media/alinx/ROOTFS
sudo chmod 755 /media/alinx/ROOTFS
```

## Launch the switch

### 1. Launch the Board

Plug the SD card into FPGA board, turn the switch to SD card boot mode.

![SD boot](../figs/FPGA_boot_mode_switch.png)

### 2. Initialize PS

Plug in SD card, setup AX7021 board to boot on SD, power on.

Connect a PC to the UART port of the board. We recommend using MobaXterm to connect the serial. Set up the Speed to 115200, Flow Control to None.

![MobaXterm](../figs/moba_serial.png)

The default username and password are as follows:

```json
username: "root"
password: "root"
```

Execute the initilization script to set up the linux environment.

```bash
sh init_os.sh
```

You can freely configure the host name, IP address, and MAC address, etc with the script, and can modify the script if needed.

### 3. Connect to Internet

Connect the PC's network port to the device's **PS** network port (ETH0).

Set up PC's corresponding port to be in the same subnet with the device (i.e., 192.168.137.x).

Afterwards, you can connect to the device through `ssh` and copy any Software files needed.

### 4. Run the Software

Please refer to the software part of this repo for further instructions.
