install:
	$(MESA_ROOT)\scripts\createdirectory.bat $(MESA_TARGET)\html
	xcopy/E ecg $(MESA_TARGET)\html
	xcopy/E rid $(MESA_TARGET)\html
