# Table of contents #


# Introduction #

This document describes the Installation procedure; if you need information on using the hack, please read the [User Guide](http://code.google.com/p/400plus/wiki/UserGuide).

# Details #

## Before you begin ##

_In order to install `400plus` you are definitively going to **need** a CF card reader; it is simply **not possible** to install `400plus` through a USB cord attached to your camera._

## Preparing the camera ##

The following steps prepare your camera to execute `400plus` each time it start up; this procedure must be done only once:

  1. Use a fully charged battery. You need CF card reader and Windows, Linux or Mac. On a mac you can use the native method or, use Windows under Bootcamp/VMware Fusion or use the Linux method.
  1. Update to [latest firmware (1.1.1)](http://web.canon.jp/imaging/eosdigital3/e4kr3_firmware-e.html) by copying it into the root of CF with your card reader, then put it in the camera and run "update firmware" in the setup menu.
  1. Empty your CF, download [400plus-testfir-1.bin.zip](https://googledrive.com/host/0B66DLxueQUdxVFJ3LXdpRDJtNnc), unpack it and copy the file testfir.fir into of your CF with the card reader.
  1. Insert the CF into the camera and run the firmware update using 'testfir.fir', the screen will go blank then. **<font color='red'>Wait at least 2 minutes</font>**_, turn it off, and finally take battery out and back in._

## Preparing each card ##

The following steps prepare a card to contain `400plus`  and be recognized by the camera; this procedure must be done for each card:

  1. First step is to format the CF card, preferably using the camera, but you can format it on the PC, too.
  1. Now the card must be made _bootable_, so the camera recognizes it:
    * **Windows XP**: use [EOScard](http://pel.hu/eoscard/); you need to check both EOS\_DEVELOP and BOOTDISK, but neither CHDK nor ML. _NOTE: Latest version of EOScard does not allow to disable CHDK or ML when both EOS\_DEVELOP and BOOTDISK are active; after formatting the card, please remove all the files copied to the card by this utility._
    * **Windows 7**: Try first the method described above for WinXP. If you have problems, try right clicking the EOSCard.exe and click Compatibility tab, then check "Run this program as administrator". Some Win7 users reported that no method was working for them, however; in that case, install VirtualBox with a Linux LiveCD or WinXP running in it, and then use the appropriate method inside the VM (after attaching the card reader to the VM).
    * **Mac**: use zeno's [MacBoot](http://www.zenoshrdlu.com/macboot/macboot.html) automated tool. (select "Make DSLR Bootable")
    * **Linux**: use the direct method (below) or use the method and files described [here](http://groups.google.com/group/ml-devel/browse_thread/thread/1161d4e6e93232de) (use the second version).
    * **Direct method** for Linux, Mac, and Windows with [cygwin](http://www.cygwin.com/) or [dd](http://www.chrysocome.net/dd):
      * Find the device corresponding to your CF card (produces a list of devices, to see where your CF card is; easy way to find it is to match the size):
        * Linux:
```
  sudo fdisk -l
```
        * Mac (first unmount the card from Disk Utility)
```
  diskutil list
```
      * FAT12 / FAT16 (CF cards up to 2GB) (replace sdX1 with the name of the device corresponding to the first partition of your CF device):
```
  dev=/dev/sdX1
  echo EOS_DEVELOP | dd of="$dev" bs=1 seek=43 count=11
  echo BOOTDISK | dd of="$dev" bs=1 seek=64 count=8
```
      * FAT32 (CF cards 4GB or larger) (replace sdX1 with the name of the device corresponding to the first partition of your CF device):
```
  dev=/dev/sdX1
  echo EOS_DEVELOP | dd of="$dev" bs=1 seek=71 count=11
  echo BOOTDISK | dd of="$dev" bs=1 seek=92 count=8
```
      * exFAT
> > > > This is not going to work directly, because the sector checksums needs to be calculated and written back after writing the strings. Use the above methods.
  1. Download the [latest official release](https://googledrive.com/host/0B66DLxueQUdxVnlqXzA5TU9wclU), extract it, and copy to CF.
  1. Put the languages.ini on the CF too, if you want support for additional languages.
  1. Insert the CF into camera... and you are done!

_If the blue LED of your camera briefly lights up when the camera is turned on, the hack has been successfully loaded._

## Updating 400plus ##

To update from a previous version of `400plus`, just overwrite the `autoexec.bin` and `languages.ini` files in all your cards.

## Removing 400plus ##
  * Permanently remove 400plus

> > The first step of the installation procedure cannot be undone (at least for now), and the camera will always try to execute `400plus` _if it is in the CF card_; thus, formating all your cards will remove `400plus` for all practical purposes.
  * Temporarily disable 400plus
> > Power Off the camera, then press and hold the **TRASH** button. While holding the button, power on the camera, it should boot without 400plus.

## What's next ##

Now you can read the [User Guide](http://code.google.com/p/400plus/wiki/UserGuide).

# Sources #
  * [raingrove](http://chdk.setepontos.com/index.php/topic,3290.msg38630.html#msg38630)
  * [whim's post](http://chdk.setepontos.com/index.php/topic,4214.msg39827.html#msg39827)

|**ATTENTION**: _Please, use the comments section below exclusively for comments (typos, clarifications, suggestions) about this page; open an issue to request support or suggest a new feature, and visit the forum for general discussions about the project._|
|:---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|