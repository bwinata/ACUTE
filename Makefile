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

WORKING_DIR			= ${shell pwd}

ACUTE_SOURCE_DIR 	= $(WORKING_DIR)/src
ACUTE_RELEASE_DIR	= $(WORKING_DIR)/release
ACUTE_LIB_DIR		= $(ACUTE_RELEASE_DIR)/lib
ACUTE_EXAMPLES_DIR	= $(WORKING_DIR)/examples

ACUTE_SOURCE_FILES	= ${shell find ./src -name '*.c' -print}
ACUTE_SOURCE_FINAL	= $(ACUTE_SOURCE_DIR)/ACUTE.c

ACUTE_EXAMPLES_PKGS = $(ACUTE_RELEASE_DIR)/binary_search_tree $(ACUTE_RELEASE_DIR)/singly_linked_list
ACUTE_EXAMPLES_OBJS = ${foreach pkg, $(ACUTE_EXAMPLES_PKGS), $(ACUTE_RELEASE_DIR)/$(pkg).o}

CC 					= gcc
CWARN 				= -g -w -Wall
CFLAGS				= $(CWARN)
CINC				= -I$(ACUTE_SOURCE_DIR)

all:	$(ACUTE_RELEASE_DIR) $(ACUTE_LIB_DIR)/acuteAssert.o $(ACUTE_EXAMPLES_PKGS)

$(ACUTE_RELEASE_DIR): 
	mkdir -p $(ACUTE_RELEASE_DIR)
	mkdir -p $(ACUTE_LIB_DIR)

$(ACUTE_LIB_DIR)/acuteAssert.o:	$(ACUTE_SOURCE_DIR)/*.[ch]
	@echo "Making $@ ..."
	cat $(ACUTE_SOURCE_FILES) > $(ACUTE_SOURCE_FINAL)
	$(CC) $(CFLAGS) $(CINC) -o $@ -c $(ACUTE_SOURCE_FINAL)
	cp $(ACUTE_SOURCE_DIR)/*.h $(ACUTE_LIB_DIR)

$(ACUTE_RELEASE_DIR)/binary_search_tree:
	@echo "Making $@ ..."
	$(CC) $(CFLAGS) $(CINC) -o $@ $(ACUTE_EXAMPLES_DIR)/binary_search_tree/binary_search_tree_main.c $(ACUTE_LIB_DIR)/acuteAssert.o

$(ACUTE_RELEASE_DIR)/singly_linked_list:
	@echo "Making $@ ..."
	$(CC) $(CFLAGS) -o $@ $(ACUTE_EXAMPLES_DIR)/singly_linked_list/singly_linked_list_main.c $(ACUTE_LIB_DIR)/acuteAssert.o

clean:
	rm -rf $(ACUTE_RELEASE_DIR)
	rm -f $(ACUTE_SOURCE_FINAL)
	