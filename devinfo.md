# devinfo.md
This is a [MarkDown][] info file intended for [400Plus][] project developers.  
There are some browser extensions to beautify [MarkDown][] files
if you do not have a way to render it and do not want to read it in plain text.  
This file should be available directly from the
[Project Repository on the Web](http://400plus.googlecode.com/svn/trunk/devinfo.md)

  [MarkDown]: http://daringfireball.net/projects/markdown/syntax
  [400Plus]: http://code.google.com/p/400plus

## DESCRIPTION
Here one should be able to find some of our discoveries in the path of
development and reverse engineering. _(if I succeed in writing this file)_

---

# ACRONYMS
## Acronyms used in this documentation
* __BL__  = BootLoader
* __OFW__ = Original FirmWare (The original Canon's firmware)
* __WDT__ = WatchDogTimer
* __RO__  = Read Only
* __PIC__ = Position Independent Code

## Acronyms used by ___Canon___ in the __OFW__
* __FIO__ = FileIO

---

# INFORMATION
## Boot procedure
So the __BL__ loads our _AUTOEXEC.BIN_ into _0x800000_ address, then jumps
there to execute our code.  
Unfortunately the __OFW__ will overwrite the beginning (or the whole maybe?)
of this area shortly after booting while we are executed from there. So we need
to move away from this addresses as soon as possible.  
The first thing we do when we are called by the __BL__ is to call our
__`COPY()`__ [_init.c_] routine (see [_entry.S_]). This routine will copy our
hack from _`0x800000`_ to _`0x7E0000`_.  
As we are not compiled with __PIC__, our code is linked to run from
_`0x7E0000`_.  You can see this address in the _linker.script_ and _Makefile_
files.  
Additionally while we are in our __`my_taskcreate_Startup()`__ [_init.c_]
we've changed the "_to_" argument of the __`CreateMainHeap(from, to)`__ call,
from "`0x800000`" to "`0x800000 - 0x20000`".  
This is so to keep the last _0x20000_ bytes (_128kb_), our hack, out of the
heap space, and this way to be safe from __OFW__'s and our heap allocations
(__`malloc()`__).

## image player stuff
0xF4B8 - there is a structure, offset 0x18 seems to be the
RealImagePosition, perhaps there are the zoom levels and other stuff for the
"PB IM" (playback image)

## DP Led blink
	eventproc_EdLedBlink();
	// or
	(*((int*)0xC0220000)) = 0x48; // led on (blink state)
	(*((int*)0xC0210014)) = 3; // make it blink

## VRAM buffers
Our display is 360x240. The buffers store YUV422 data.

Image VRAM (the one which is used in image player) is located:
	// from: 0x412604    to: 0x4AA404    size: 0x97E00 (622080)
there are 2 buffers inside, with small data between...

Menu VRAM (the one which will be used for menus, like in ML):
	// from: 0x212D7C    to: 0x23D144    size: 0x2A3C8 (173000)

	// it seems the usable region (360x240) of the menu vram is:
	// from: 0x212D7C    to: 0x227EFC    size: 0x15180 (86400)
	// then there is some small data
	// and the buffer continues, (probably bmp buffer)
	// from: 0x227FC4    to: 0x23D144    size: 0x15180 (86400)

## Button addresses (thanks Sergei)
button pressed: 0x20
button not pressed: 0x21

JUMP: 0xC0220134
TRASH: 0xC0220130

## Message Queues
CreateMessageQueue returns pointer to a structure of this type I believe:
	struct {
		int messages_in_the_queue; // unread
		char * name_of_the_queue;
	}

## state machines
Alex made some nice diagrams of our state machines:
http://a1ex.bitbucket.org/ML/states/400D-alt/index.html


---

# IDEAS
## bootflags, this is for the .fir enabler
	// FFFF5720 read_bootflag
	// FFFF5638 write_bootflag

	// diasble
	read_bootflag(0, buf);
	buf[1] = 0;
	write_bootflag(0, buf);

	// enable
	read_bootflag(0, buf);
	buf[1] = -1;
	write_bootflag(0, buf);


	// check the 350d bootflags enabler... their toggle routine is:
	read_bootflag(buf1, buf2);
	if (buf1[1] == 0)	buf1[1] = -1;
	else				buf1[1] = 0;
	write_bootflag(buf1, buf2);


	// chat with andrew:
	// if you study the 400d bootloader, the syntax is different
	// arg0 is either 0 or 1, it sets different flags
	// (always pass 0 though, didn't recognize the other flags)


## MMIO for buttons
we should be able to see the buttons on MMIO ports
the a540 camera (which is vxworks) sees them at:

	volatile long *mmio0 = (void*)0xc0220200;
	volatile long *mmio1 = (void*)0xc0220204;
	volatile long *mmio2 = (void*)0xc0220208;

	dst[0] = *mmio0;
	dst[1] = *mmio1;
	dst[2] = *mmio2 & 0xffff;

## force MF for lens (may be)
we can try setting cameraMode->ef\_lens\_exist=0 to force, not sure if it works.
if it works, it could be useful for bracketing...

## Help translators
make a perl script to extract the lang keys and put them in the end of the
languages.ini as comments

## HELP messages
make them show on key press (when over some menu item) zoom-in btn is good
candidate.
use dialog 64 (best), or 91 (or it was 98?), or 101

## MEMSPY - usability
Make memspy more usable, perhaps a menu for it would be nice.

## DPData debug
Catch changes to DPData with memspy or make a separate routine to catch the
changes... i.e. a copy of DPData (though there is one from canon) and a routine
which checks for differences between the original and the copy, then reports
them and update the copy buffer.

## Proxying unknown queues (just some untested food for thought)

Let's suppose there is some _hMessageQueue_ we know about and want to 
intercept, but we do not know what routine reads that queue, or just do not 
want to dissasemble it. However, we can be pretty sure that the firmware will 
do something similar to this (example extracted form _main_ctrl_):

	// code should be indented one tab right.
	firmware_routine() {
		while (TRUE) {
			ReceiveMessageQueue(hMessageQueue, &message, 0);

			// do something about "message"
		}
	}

Now, we coud insert a proxy, that will read all messages in that queue before 
they reach _firmware_routine_, like this:

	proxy_routine() {
		int *hOutputQueue = CreateMessageQueue("ProxyQueue", param); // [1]
		int *hInputQueue  = hMessageQueue;

		hMessageQueue  = hOutputQueue;

		while (TRUE) {
			ReceiveMessageQueue(hInputQueue, &message, 0);

			// do something about "message"

			PostMessageQueue(hOutputQueue, message, forever); // [2]
		}

		// [1] What's "param" here exactly?
		// [2] Should "forever" be set to TRUE?
	}

Obviously, that proxy should be launched as a separate task:

	hijack_routine() {
		CreateTask("ProxyTask", prio, stack_size, proxy_routine, parm); //[3]
		// [3] Decide values missing values
	}




// 0xAF:
Ok, I did not found a way to steal the queue, it just dont work, perhaps I'm
not doing it in the right way.

What I found so far is that there is no problem to ReceiveMessageQueue(someQ);
in parallel with the original task.
i.e.
we start a separate task and call:
	ReceiveMessageQueue(hMainMessQueue, &msg, 0);
and we receive the same events as the original MainCtrl task.
this is still a good way to catch if something is happening.

i will continue my investigations...



## try to get the booting logs from the beginning
Use the blinking driver for vxworks from owerlord as base.
Probably make another driver, which just stores messages to big buffer
(32/64kb) then at the __`task_Startup()`__ write the booting log to the CF.

## Doxygen comments in code
Comment the code with doxygen comments.

## Temporarily disable the hack
1. write a temp file to the CF
2. __`reboot()`__ or use the __WDT__ routines to block the __WDT__ pings
and get rebooted.
3. find the __BL__'s __FIO__ routines (atleast __`open()`__) and check
for the temp file existence.
4. remove the file if exists.
5. call __OFW__'s init procedure if the temp file was there.
(start normally, skip the hack)

## Auto-Protect option
Check if it's possible to make the files _Read-Only_ (with __RO__ attribute)
on-the-fly. This will protect them from deleting with <_Erase_> and
<_Erase all_>. I suppose the __OFW__ protect works the same way.

## Separate folders for photos
The High-End cameras (_5d2_) have this option. One can change the folder where
the photos are saved.
See [DCF](http://en.wikipedia.org/wiki/Design_rule_for_Camera_File_system).

## Separate folder for 400Plus stuff
It would be nice to have our files in separate folder. See the previous idea.

## Lens info
Continue investigation on lens info structures and tables.
This info can be useful for _Presets_ based on attached lens.

## PTP - Picture Transfer Protocol
Investigate on PTP stuff, the ultimate goal is to be able to upload the
_AUTOEXEC.BIN_ into the camera via the PTP (USB).
See [PTP](http://en.wikipedia.org/wiki/Picture_Transfer_Protocol).

## Help messages
Short help messages for every menu. Either as pop-up message
(__`StartTimer()`__ can be used), or with dedicated __HELP__ button.

---

# ROUTINES
## Useful routines
* `StartTimer(int time, void *proc, void *proc, int);`  
  Canon uses this to schedule a proc for starting.  
  In the both proc arguments they are giving the same pointer.  
  Last arg is 0

## Routines which needs more attention
* `eventproc_SetCustomFunc`
* `eventproc_ExportToEventProcedure`
* `eventproc_CreateProxyOfEventProcedure`
* `eventproc_ShutDownAndRestartAfter`
* `eventproc_ShutDownAndRestartWhen`
* `eventproc_BlockUntilAfterTimeout`
* `PTPRspnd.StartTransportLog`
* `eventproc_SpecyficToPartnerEvent`
* `eventproc_ShowMemBlock`
* `eventproc_ResetMem`
* `eventproc_EnableBootDisk`
* `eventproc_DisableBootDisk`
* `eventproc_EnableDigitalGain`
* `eventproc_DisableDigitalGain`
* `eventproc_EnableLinearOffsetCorrect`
* `eventproc_DisableLinearOffsetCorrect`
* `eventproc_TransferNormalScreen` - normal
* `eventproc_TransferUpsideDownScreen` - upside-down
* `eventproc_TransferMirrorScreen` - mirror
* `eventproc_TransferRotateScreen` - rotate
* `PTP_Actions`
* `register_ptp_handler`


vim: ft=markdown ts=4 sw=4 cc=80 spell:
