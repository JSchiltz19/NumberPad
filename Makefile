
current-project := NumberPad
FQBN := arduino:avr:micro
path := arduino.avr.micro

##Compile
build/$(current-project).ino.hex : $(current-project).ino
		arduino-cli compile -b $(FQBN)
		
##Copy .hex from Ubuntu folder to windows
prepare-upload: build/$(current-project).ino.hex
	cp build/$(path)/$(current-project).ino.hex /mnt/d/NumberPadOutput/$(current-project).ino.hex
	
upload: build/$(current-project).ino.hex
	cp build/$(path)/$(current-project).ino.hex /mnt/d/NumberPadOutput/$(current-project).ino.hex
	/mnt/d/NumberPadOutput/upload_port8_micro.exe

clean: build
	rm -r build
