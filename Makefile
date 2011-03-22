MAKE = make
MKDIR = mkdir
CP = copy

all: bin\usbgmpost\usbgmget.exe

bin\usbgmpost\usbgmget.exe: src\usbgmget.exe
	$(CP) $** bin\usbgmpost\

src\usbgmget.exe: bin\usbgmpost\gmlib.dll
	cd src
	$(MAKE)
	cd ..

clean: 
	cd src
	$(MAKE) clean
	cd ..
	del bin\usbgmpost\usbgmget.exe
