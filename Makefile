########################################################
# Another C Unit Testing Framework (ACUTE)
#
# Author	:	Barry Winata
# Date		:	11 November 2013
# 
# Description
# ------------------------------------------------------
# Makefile for generating release object files and
# associated libraries. 
########################################################

WORKING_DIR		= ${shell pwd}

ACUTE_SOURCE 	= $(WORKING_DIR)/src
ACUTE_RELEASE	= $(WORKING_DIR)/release
ACUTE_LIB		= $(ACUTE_RELEASE)/lib
ACUTE_EXAMPLES	= $(WORKING_DIR)/examples

ACUTE_EXAMPLES_PKGS = $(ACUTE_RELEASE)/binary_search_tree $(ACUTE_RELEASE)/singly_linked_list
ACUTE_EXAMPLES_OBJS = ${foreach pkg, $(ACUTE_EXAMPLES_PKGS), $(ACUTE_RELEASE)/$(pkg).o}

CC 				= gcc
CWARN 			= -g -w -Wall
CFLAGS			= $(CWARN)
CINC			= -I$(ACUTE_SOURCE)

all:	$(ACUTE_RELEASE) $(ACUTE_LIB)/acuteAssert.o $(ACUTE_EXAMPLES_PKGS)

$(ACUTE_RELEASE): 
	mkdir -p $(ACUTE_RELEASE)
	mkdir -p $(ACUTE_LIB)
	@echo $(ACUTE_EXAMPLES_OBJ)

$(ACUTE_LIB)/acuteAssert.o:	$(ACUTE_SOURCE)/*.c
	@echo "Making $@ ..."
	$(CC) $(CFLAGS) -o $@ -c $(ACUTE_SOURCE)/acuteAsserts.c

$(ACUTE_RELEASE)/binary_search_tree:
	@echo "Making $@ ..."
	$(CC) $(CFLAGS) -o $@ $(ACUTE_EXAMPLES)/binary_search_tree/main.c

$(ACUTE_RELEASE)/singly_linked_list:
	@echo "Making $@ ..."
	$(CC) $(CFLAGS) -o $@ $(ACUTE_EXAMPLES)/singly_linked_list/main.c

clean:
	rm -rf $(ACUTE_RELEASE)
	