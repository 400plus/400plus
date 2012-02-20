

# devinfo.md
This is a [MarkDown][] info file intended for [400Plus][] project
developers.

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
It seems the __BL__ loads our _AUTOEXEC.BIN_ into _0x800000_ address,
then jumps there. Unfortunately the __OFW__ will overwrite the beginning of
this area shortly after booting, so we need to move away from this addresses.
The first thing we do when we are called by the __BL__ is to call our
__`COPY()`__ [_init.c_] routine (see [_entry.S_]).
This routine will copy some part (_`0x4000`_/_16kb_) of the code from
_`0x800000`_ to _`0x7E0000`_. As we are not compiled with __PIC__, our code is
linked to run from _`0x7E0000`_.  See this address in the _linker.script_
and _Makefile_ files.  Actually we should be using this range
(_`0x7E0000`_:_`0x800000`_) for our hack (_128kb_).
This is what I (_0xAF_) do not understand: Why/How we run from _`0x7E0000`_,
when we only copied _16kb_ out of _128kb_ from our hack ? Moreover if I try
to copy more than _16kb_ in our __`COPY()`__ routine, the camera hangs.
Anyway, while we are in our __`my_taskcreate_Startup()`__ [_init.c_] you will
see that the call to __`CreateMainHeap(from, to)`__ have "`0x800000 - 0x20000`"
for the "_to_" argument. This is to keep the last _0x20000_ bytes (_128kb_) out
of the heap space.  This way we should be safe from __OFW__'s and ours heap
allocations (__`malloc()`__).

---

# IDEAS
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

<!-- vim: ft=markdown ts=4 sw=4 cc=80 spell: -->
