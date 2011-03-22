CC = bcc32
LINK = bcc32
IMPLIB = implib


usbgmget.exe: usbgmget.obj gmlib.lib
	$(LINK) -e$* $**

usbgmget.obj: usbgmget.cpp usbgm.h
	$(CC) -c usbgmget.cpp -o$*

gmlib.lib: ..\bin\usbgmpost\gmlib.dll
	$(IMPLIB) $* $**

clean:
	del usbgmget.exe
	del usbgmget.tds
	del usbgmget.obj
	del gmlib.lib
