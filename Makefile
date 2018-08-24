# Ping the various pieces of hardware
# Employ use of routing tables???


# PROJECT VARS
PROJ_DIR = $(shell pwd)
PROJ = crc
GY_PROJ_DIR = /home/stephen/Desktop/CRC
LAB_PROJ_DIR = ~/Documents/hi_im_stephen/CRC

# SOURCE VARS
CSP_DIR = $(PROJ)/lib/libcsp

CFLAGS = \
-Wall

MY_SOURCES = \
$(PROJ)/main.c \
$(PROJ)/server.c \
$(PROJ)/client.c \
$(PROJ)/calculateCrc.c

INCLUDES = \
-I$(PROJ) \
-I$(CSP_DIR)/include \
-I$(CSP_DIR)/build/include

LIBS = \
$(PROJ)/lib/libcsp/build/libcsp.a \
-lpthread

EXEC = \
crc.exe

CSP_CONFIG_OPTIONS = \
--enable-crc32 \
--enable-rdp


### MAC (DEV) COMMANDS
pushGY:
	rsync -r . goodyearLinux:$(GY_PROJ_DIR)
pushLAB:
	rsync -r . newLabPC:$(LAB_PROJ_DIR)

### LINUX (RUN) COMMANDS
proj:
	gcc $(CFLAGS) $(INCLUDES) $(MY_SOURCES) $(LIBS) -o $(EXEC)

csp:
	cd $(CSP_DIR); ./waf configure; ./waf clean; ./waf configure $(CSP_CONFIG_OPTIONS); ./waf build

destroy: 
	rm -r $(PROJ)
	
clean:
	cd $(CSP_DIR); ./waf clean
	rm -r $(EXEC)
	
run: 
	./$(EXEC)

### TEST COMMANDS

test_workspace:
	@echo $(PROJ_DIR)