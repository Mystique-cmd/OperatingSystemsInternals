:'Below are steps outlining the Kernel compilation commands.
Go to https://kernel.org and download the vanilla kernel to get the compressed archive file.
a) Extract the kernel file'
 	tar -xvf linux6*.tar.xz
 	cd linux-6*/
:'The build tools should be installed automatically during the decompression if now use the following command to install all the required build tools ( On Debian and Ubuntu Systems )'
	sudo apt install build-essential libncurses-dev bison flex libssl-dev libelf-dev
:'b) Import the current distro kernel config;'
	cp /boot/config-$(uname -r) .config
:'c) Configure the kernel ( make sure the terminal size is large enough to display the menu)'
	make menuconfig
:'d) Compile the kernel'
	make -j$(nproc)
:'e) Install modules and kernel'
	sudo make modules_install
	sudo make install
:'f) Reboot and start experimenting with the new kernel 
