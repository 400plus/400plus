

---

# Introduction #
useful information for developers wanting to compile the code.<br>
<br>
<hr />
<h1>toolchains</h1>
<h2>summon-arm-toolchain <b>(this is the latest)</b></h2>
I'm using summon-arm-toolchain script initially written by Uwe Hermann, modified by Piotr Esden-Tempski<br>
and forked by Magic-Lantern guys. The toolchain needs to be compiled for soft-floats, <br>
the ML's script will compile it correctly. Please read the <b>32bit vs 64bit toolchain</b>, it's important.<br>
<br>
here is some short code to help you:<br>
<pre><code>cd /tmp<br>
hg clone https://bitbucket.org/hudson/magic-lantern<br>
hg update unified<br>
cd magic-lantern/toolchain<br>
./summon-arm<br>
</code></pre>
in the end you should have the arm toolchain in it's own folder.<br>
<br>
<br>
<h2>32bit vs 64bit toolchain</h2>
So it turns out that when your host system is 64bit and you have the toolchain compiled there,<br>
it will produce some rellocation errors on linking phase, when linking 400plus.<br>
Adding -mlong-calls (or -fPIC) to the CFLAGS will fix the rellocation problems on 64bit host toolchain,<br>
but unfortunately will add about ~8kb (~11kb with -fPIC) to the AUTOEXEC.BIN. <br>
We prefer to spend this extra KB into another features, instead of loosing them to the linker.<br>
(<i>note</i>: please if someone find a way to compile the toolchain in 64bit linux and get rid of rellocation errors and -mlong-call, DO TELL US PLEASE !)<br>
<br>
So Edu came with the solution: <br>
you need 32bit toolchain to get rid of the rellocation errors and the -mlong-calls (which adds 10kb)<br>
for that purpose you should use the chroot method below, or install a 32bit linux in a virtual machine.<br>
then make compile the toolchain there, and transfer it to your 64bit host<br>
(in my case i had to transfer a few extra libs with the toolchain and use LD_LIBRARY_PATH=/path/to/extra/libs)<br>

another solution would be to stay in the chroot/VM and compile 400Plus there.<br>
<br>
<br>
<h2>chroot in 32bit linux (gentoo) from 64bit linux host</h2>
this should be straight forward (copy/paste) howto.<br>
Read <a href='http://www.gentoo.org/proj/en/base/amd64/howtos/index.xml?part=1&chap=2'>this documentation</a> for more details.<br>
follow these steps to create and enter your cross environment.<br>
<pre><code>cd /tmp<br>
url="http://mirrors.kernel.org/gentoo/releases/x86/autobuilds"<br>
wget $url/`curl $url/latest-stage3-i686.txt | tail -1`<br>
mkdir /mnt/gentoo32<br>
cd /mnt/gentoo32/<br>
tar -xvjpf /tmp/stage3-i686-*.tar.bz2<br>
# ### UNCOMMENT THE NEXT LINE ONLY IF YOUR HOST IS _NOT_ GENTOO ### #<br>
# wget http://distfiles.gentoo.org/snapshots/portage-latest.tar.bz2 &amp;&amp; tar xjf portage-lat* -C usr/<br>
cp -L /etc/resolv.conf /mnt/gentoo32/etc/<br>
$EDITOR /mnt/gentoo32/etc/make.conf #can be skipped<br>
wget http://0xAF.org/chroot-gentoo32 -O ~/chroot-gentoo32.sh<br>
chmod +x ~/chroot-gentoo32.sh<br>
~/chroot-gentoo32.sh<br>
</code></pre>

if you can't download chroot-gentoo32 script for some reason, see the end of this document for the source code.<br>
<br>
You should be in working 32bit chroot now..<br>

Now compile the toolchain (see above)... and use it in the chroot, or copy it to your host system.<br>
<br>
next you need to get the <a href='https://googledrive.com/host/0B66DLxueQUdxRDVsYTQtR2VSNFU'>400plus sources</a>.<br>
if you want the current svn sources in your chroot, you'll need to install subversion first:<br>
<pre><code>emerge -av subversion<br>
</code></pre>
then checkout<br>
<pre><code>cd &amp;&amp; svn checkout http://400plus.googlecode.com/svn/trunk/ 400plus-read-only<br>
</code></pre>

<h2>Fedora 16 in a Virtual Machine</h2>

This guide explains how to prepare a 32bit environment to cross-compile the source code; I had to follow this procedure as compilation was reporting inexplicable errors on my 64bit machine.<br>
<br>
<h3>Create a VM</h3>

I used Fedora 16 (64 bits) as the "host" OS, and Fedora 16 (32 bits) as the "guest" OS, for no other particular reason that it is what I am used to run; I downloaded the <a href='http://fedoraproject.org/en/get-fedora-options'>Fedora 16 Desktop Edition (32 bit CD ISO)</a>.<br>
<br>
Basically, I followed the <a href='http://fedoraproject.org/wiki/Virtualization_Quick_Start'>Virtualization Quick Start guide</a> to create the virtual machine. Most relevant parameters for the emulation were: 4GB of disk space, 512 MB of RAM, 1 CPU. Select an i686 architecture (should work with a 64b arch, as long as you install a 32b OS) and use KVM if your processor supports it (it is way faster than the non-KVM alternative). Boot the VM, using the ISO downloaded previously, and install it to the (virtual) disk drive<br>
(there are no critical parameters here, just follow the installation assistant).<br>
<br>
<h3>Prepare the VM</h3>

No special preparation is required here, just update the software:<br>
<pre><code>su -c "yum -y update"<br>
su -c "yum -y update"<br>
</code></pre>

<i>Yes: it must be run twice, as the first update will only update the updater itself</i>. Then reboot (just the VM, not the computer) and install the required dependencies:<br>
<pre><code>su -c "yum -y install gcc mpfr-devel libmpc-devel"<br>
</code></pre>

<h3>Install the cross-compiler</h3>

Once you have your 32bit machine up and running, simply follow the instructions at <a href='#toolchains.md'>toolchains</a>.<br>
<br>
<h3>Compile 400plus</h3>

You need to download the <a href='https://googledrive.com/host/0B66DLxueQUdxRDVsYTQtR2VSNFU'>400plus sources</a> or checkout the current SVN:<br>
<pre><code>cd &amp;&amp; svn checkout http://400plus.googlecode.com/svn/trunk/ 400plus-read-only<br>
</code></pre>

Finally, we are ready to compile:<br>
<pre><code>export PATH=/opt/arm-elf/bin/:$PATH<br>
cd 400plus<br>
make<br>
</code></pre>

If everything goes as expected, you will get a new and shiny "AUTOEXEC.BIN" file.<br>
<br>
<h2>Ubuntu</h2>

Our friend draekko has created a new build script for Ubuntu (tested only on Ubuntu 13.10 and 14.04) as well as required patches to recompile the toolchain on modern versions of Linux. Relevant files at <a href='https://github.com/draekko/arm-462-toolchain-400plus'>https://github.com/draekko/arm-462-toolchain-400plus</a> (relevent info in build-toolchain-for-400plus.sh). Same caveats for 64bit compiles as listed above.<br>
<br>
<hr />
<h1>links</h1>
<ul><li><a href='http://code.google.com/p/400plus/wiki/FirmwareHackInstallation'>Hack Installation procedure</a>
</li><li><a href='http://chdk.setepontos.com/index.php?topic=3290.0'>CHDK forum thread for 400D/XTI development</a><br>
</li><li><a href='http://www.akae.cn/study/ebook/wrs/vx5.5/'>VxWorks Programmer's Guide, Drivers API, OS Libraries and more</a><br>
<br></li></ul>

<hr />
<h1>chroot-gentoo32</h1>
<pre><code>#!/bin/bash<br>
<br>
# change to appropriate dir<br>
CHROOTDIR=/mnt/gentoo32<br>
<br>
bind_dirs=(<br>
	"/dev"<br>
	"/dev/pts"<br>
	"/dev/shm"<br>
	"/proc"<br>
	"/proc/bus/usb"<br>
	"/sys"<br>
	"/tmp"<br>
	"/usr/portage" # this is only if your host is gentoo<br>
)<br>
<br>
<br>
# no need to change anything below this line<br>
<br>
if [ $UID -ne 0 ]; then<br>
	echo "need root... executing with su"<br>
	su -c "$0 $*"<br>
	exit<br>
fi<br>
<br>
mkdir -p $CHROOTDIR/usr/portage/<br>
if [ ! -f $CHROOTDIR/root/.bashrc ]; then<br>
	cp $CHROOTDIR/etc/skel/.bashrc $CHROOTDIR/root/.bashrc<br>
	echo "source /etc/profile" &gt;&gt; $CHROOTDIR/root/.bashrc<br>
	echo "env-update" &gt;&gt; $CHROOTDIR/root/.bashrc<br>
	echo 'export PS1="[chroot] $PS1"' &gt;&gt; $CHROOTDIR/root/.bashrc<br>
	echo 'export PATH=$PATH:/arm-elf-toolchain/bin/' &gt;&gt; $CHROOTDIR/root/.bashrc<br>
fi<br>
<br>
for (( x=0; x &lt; ${#bind_dirs[@]}; x++ )); do<br>
	dir="${bind_dirs[$x]}"<br>
	mount -o bind "$dir" "$CHROOTDIR/$dir"<br>
done<br>
<br>
if [ `uname -m` == x86_64 ]; then<br>
	l32=linux32<br>
fi<br>
<br>
$l32 chroot $CHROOTDIR /bin/bash<br>
<br>
for (( x=$((${#bind_dirs[@]} - 1)) ; x &gt;= 0; x-- )); do<br>
	dir="${bind_dirs[$x]}"<br>
	umount "$CHROOTDIR/$dir"<br>
done<br>
<br>
</code></pre>