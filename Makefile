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
ACUTE_TESTS_DIR		= $(WORKING_DIR)/tests

ACUTE_SOURCE_FILES	= ${shell find ./src/*.c -type f -print | sed 's:\./src/::g'}
ACUTE_OBJS			= ${foreach pkg, $(ACUTE_SOURCE_FILES:.c=.o), $(ACUTE_LIB_DIR)/$(pkg)}

ACUTE_EXAMPLES_PKGS = $(ACUTE_RELEASE_DIR)/binary_search_tree $(ACUTE_RELEASE_DIR)/singly_linked_list
ACUTE_TEST_HARNESS	= $(ACUTE_RELEASE_DIR)/acuteUnitTests

CC 					= gcc
CWARN 				= -g -w -Wall
CFLAGS				= $(CWARN)
CINC				= -I$(ACUTE_SOURCE_DIR)

all:	$(ACUTE_RELEASE_DIR) $(ACUTE_TEST_HARNESS) $(ACUTE_EXAMPLES_PKGS)

$(ACUTE_RELEASE_DIR): 
	mkdir -p $(ACUTE_RELEASE_DIR)
	mkdir -p $(ACUTE_LIB_DIR)
	@echo $(ACUTE_OBJS)

$(ACUTE_LIB_DIR)/acuteAsserts.o:
	@echo "Making $@ ..."
	$(CC) $(CFLAGS) $(CINC) -o $@ -c $(ACUTE_SOURCE_DIR)/acuteAsserts.c
	
$(ACUTE_LIB_DIR)/acuteTest.o:
	@echo "Making $@ ..."
	$(CC) $(CFLAGS) $(CINC) -o $@ -c $(ACUTE_SOURCE_DIR)/acuteTest.c
	
$(ACUTE_LIB_DIR)/acuteExecute.o:
	@echo "Making $@ ..."
	$(CC) $(CFLAGS) $(CINC) -o $@ -c $(ACUTE_SOURCE_DIR)/acuteExecute.c
	
$(ACUTE_LIB_DIR)/acuteException.o:
	@echo "Making $@ ..."
	$(CC) $(CFLAGS) $(CINC) -o $@ -c $(ACUTE_SOURCE_DIR)/acuteException.c			
	
$(ACUTE_RELEASE_DIR)/acuteUnitTests: $(ACUTE_OBJS)
	@echo "Making $@ ..."
	$(CC) $(CFLAGS) $(CINC) -o $@ $(ACUTE_TESTS_DIR)/acuteUnitTests.c $(ACUTE_OBJS)
	
$(ACUTE_RELEASE_DIR)/binary_search_tree: $(ACUTE_OBJS)
	@echo "Linking $@ ..."
	$(CC) $(CFLAGS) $(CINC) -o $@ $(ACUTE_EXAMPLES_DIR)/binary_search_tree/binary_search_tree_main.c $(ACUTE_OBJS)

$(ACUTE_RELEASE_DIR)/singly_linked_list: $(ACUTE_OBJS)
	@echo "Linking $@ ..."
	$(CC) $(CFLAGS) -o $@ $(ACUTE_EXAMPLES_DIR)/singly_linked_list/singly_linked_list_main.c $(ACUTE_OBJS)

clean:
	rm -rf $(ACUTE_RELEASE_DIR)
	rm -f $(ACUTE_SOURCE_FINAL)
	