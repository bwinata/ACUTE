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

# Get Current Working Directory
WORKING_DIR			= ${shell pwd}

# Define folder paths
ACUTE_SOURCE_DIR 	= $(WORKING_DIR)/src
ACUTE_RELEASE_DIR	= $(WORKING_DIR)/release
ACUTE_LIB_DIR		= $(ACUTE_RELEASE_DIR)/lib
ACUTE_EXAMPLES_DIR	= $(WORKING_DIR)/examples
ACUTE_TESTS_DIR		= $(WORKING_DIR)/tests

# List available source directories and label as object files
ACUTE_PKGS			= ${shell find ./src/* -type d -print | sed 's:\./src/::g'}
ACUTE_OBJS			= ${foreach pkg, $(ACUTE_PKGS), $(ACUTE_LIB_DIR)/$(pkg).o}

# List available executables to build
ACUTE_EXAMPLES_PKGS = $(ACUTE_RELEASE_DIR)/binary_search_tree $(ACUTE_RELEASE_DIR)/singly_linked_list
ACUTE_TEST_HARNESS	= $(ACUTE_RELEASE_DIR)/acuteUnitTests

# Compiler / Flags and Header locations
CC 					= gcc
CWARN 				= -g -w -Wall
CFLAGS				= $(CWARN)
CINC				= -I$(ACUTE_SOURCE_DIR)/asserts -I$(ACUTE_SOURCE_DIR)/exception -I$(ACUTE_SOURCE_DIR)/framework

all:	$(ACUTE_RELEASE_DIR) $(ACUTE_TEST_HARNESS) $(ACUTE_EXAMPLES_PKGS)

# Create Release directories
$(ACUTE_RELEASE_DIR): 
	mkdir -p $(ACUTE_RELEASE_DIR)
	mkdir -p $(ACUTE_LIB_DIR)
	
# Compile but don't link object files 
$(ACUTE_LIB_DIR)/asserts.o:
	@echo "Making $@ ..."
	$(CC) $(CFLAGS) $(CINC) -o $@ -c $(ACUTE_SOURCE_DIR)/asserts/acuteAsserts.c
	
$(ACUTE_LIB_DIR)/exceptions.o:
	@echo "Making $@ ..."
	$(CC) $(CFLAGS) $(CINC) -o $@ -c $(ACUTE_SOURCE_DIR)/exceptions/acuteException.c

$(ACUTE_LIB_DIR)/framework.o:
	@echo "Making $@ ..."
	cat $(ACUTE_SOURCE_DIR)/framework/acuteTest.c $(ACUTE_SOURCE_DIR)/framework/acuteExecute.c > $(ACUTE_SOURCE_DIR)/framework/acuteFramework.c 
	$(CC) $(CFLAGS) $(CINC) -o $@ -c $(ACUTE_SOURCE_DIR)/framework/acuteFramework.c
	rm -f $(ACUTE_SOURCE_DIR)/framework/acuteFramework.c
	
# Build executables and link with created object files
$(ACUTE_RELEASE_DIR)/acuteUnitTests: $(ACUTE_OBJS)
	@echo "Making $@ ..."
	$(CC) $(CFLAGS) $(CINC) -o $@ $(ACUTE_TESTS_DIR)/acuteUnitTests.c $(ACUTE_OBJS)
	
$(ACUTE_RELEASE_DIR)/binary_search_tree: $(ACUTE_OBJS)
	@echo "Linking $@ ..."
	$(CC) $(CFLAGS) $(CINC) -o $@ $(ACUTE_EXAMPLES_DIR)/binary_search_tree/binary_search_tree_main.c $(ACUTE_OBJS)

$(ACUTE_RELEASE_DIR)/singly_linked_list: $(ACUTE_OBJS)
	@echo "Linking $@ ..."
	$(CC) $(CFLAGS) -o $@ $(ACUTE_EXAMPLES_DIR)/singly_linked_list/singly_linked_list_main.c $(ACUTE_OBJS)

# Clean release directory
clean:
	rm -rf $(ACUTE_RELEASE_DIR)
	rm -f $(ACUTE_SOURCE_FINAL)
	