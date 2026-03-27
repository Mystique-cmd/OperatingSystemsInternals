:'To debug the kernel memory, first you should ensure that KASAN ans SLUB are enabled'
	make menuconfig
:'rebuild the kernel once more'
	make -j$(nproc)
	sudo make modules_install
	sudo make install
	sudo update-grub
:'Check is KASAN is active'
	dmesg | grep -i kasan
