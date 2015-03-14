|<font color='red'><b><i>Note</i></b>: Due to lack of maintenance, this guide has been deprecated; please use the English version of the <a href='FirmwareHackInstallation.md'>firmware hack installation guide</a>.</font>|
|:-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|

<a href='Hidden comment: 

= Introduzione =

Questo documento descrive la procedura di installazione; se cerchi informazioni riguardo l"uso del hack, leggi il  [http://code.google.com/p/400plus/wiki/UserGuideItalian Manuale Utente 400D+].

= Dettagli =

== Prima di iniziare ==

_Per installare 400+ è assolutamente *necessario* un lettore di schede CF; è semplicemente *impossibile* installarlo tramite il cavo USB collegato alla fotocamera._

== Preparare la fotocamera ==

I passi seguenti impostano la fotocamera in modo da avviare 400+ ad ogni avvio; è necessario effettuare questa procedura solamente una volta:

#. Assicurarsi di usare una batteria completamente carica. È necessario un lettore di schede CF e windows,  linux o Osx.<br>Con Osx, potete usare windows virtualizzato o il metodo per linux.
#. Aggiornate al [http://web.canon.jp/imaging/eosdigital3/e4kr3_firmware-e.html ultimo firmware (1.1.1)] copiandolo nella CF tramite il lettore di schede,<br> poi inseritela nella fotocamera e avviate "aggiornamento firmware" dal menu delle impostazioni.
#. vuotate la CF, scaricate [http://code.google.com/p/400plus/downloads/list testfir.fir] e copiatelo nella CF con il lettore di schede.
#. inserite la CF nella fotocamera e avviate "aggiornamento firmware" usando testfir.fir, lo schermo si spegnerà.<br> _*<font color="red">Aspettate almeno 2 minuti senza toccare alcun tasto

Unknown end tag for &lt;/font&gt;

*_, spegnete, togliete la batteria e reinseritela.

== Preparare ogni scheda ==

I passi seguenti preparano la scheda con 400+  rendendolo riconoscibile dalla fotocamera; è necessario effettuare questa procedura per ogni scheda:

#. A seconda del vostro Sistema Operativo e CF Card il prossimo step cambia, ma prima inserite la CF nella fotocamera e formattatela.<br>
* Windows: usate [http://pel.hu/down/EOScard.exe EOScard] by [http://chdk.setepontos.com/index.php?topic=4214.msg58253#msg58253 pelican], dovete controllare EOS_DEVELOP e BOOTDISK<br>come mostrato [http://chdk.wikia.com/wiki/EOScard qui]
* Mac: usate zeno"s [http://www.zenoshrdlu.com/macboot/macboot.html MacBoot] (Lion non supportato).
* Linux: usate metodo diretto (qui sotto)<br>o usate il metodo e i file descritti [http://groups.google.com/group/ml-devel/browse_thread/thread/1161d4e6e93232de qui] (usate la seconda versione)
* Metodo diretto per Linux, Mac e windows con [http://www.cygwin.com/ cygwin] o [http://www.chrysocome.net/dd dd]:
* FAT12/FAT16 (CF Card <= 4GB)
```
dev=/dev/sdb1 # replace sdb1 with your CF device (first partition)
echo EOS_DEVELOP | dd of="$dev" bs=1 seek=43 count=11
echo BOOTDISK | dd of="$dev" bs=1 seek=64 count=8
```
* FAT32
```
dev=/dev/sdb1 # replace sdb1 with your CF device (first partition)
echo EOS_DEVELOP | dd of="$dev" bs=1 seek=71 count=11
echo BOOTDISK | dd of="$dev" bs=1 seek=92 count=8
```
* exFAT
Questo non può funzionare direttamente perché il "sector checksums" deve esser calcolato e  scritto dopo aver scritto le string. Usate i metodi precedenti.
#. scaricate [http://code.google.com/p/400plus/downloads/list l"ultimo autoexec.bin], estraetelo e copiatelo nella CF.
#. Copiate il file languages.ini sulla scheda CF, per avere il supporto multilingue.
#. Inserite la CF nella fotocamera e avete finito.

_*Se il LED blue della fotocamera si accende per un attimo all"accensione della fotocamera, l"hack è stato caricato con successo.*_

== Aggiornare 400+ ==

Per aggiornare da una versione precedente di "400+, basta sovrascrivere i file autoexec.bin e languages.ini` in tutte le schede.

== Disinstallare 400+ ==

Il prmo passaggio della procedure di installazione non può essere annullato al momento, e la fotocamera cercherà sempre di eseguire 400+ _se presente nella scheda CF_; pertanto formattando ogni scheda si rimuoverà 400+.

== Cosa fare poi ==

*Ora potete leggere la guida su [http://code.google.com/p/400plus/wiki/UserGuideItalian come usare l"hack].*

= Fonti =
* [http://chdk.setepontos.com/index.php/topic,3290.msg38630.html#msg38630 raingrove]
* [http://code.google.com/p/400d/downloads/detail?name=400d_autoexec_bin_guide.doc&can=2&q= Huong dan cai dat]
* [http://chdk.wikia.com/wiki/400D 400d page on wikia]
* [http://chdk.setepontos.com/index.php/topic,4214.msg39827.html#msg39827 whim"s post]

'></a>