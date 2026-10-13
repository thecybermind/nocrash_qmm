# NoCrash_QMM - QMM Plugin to fix q3msgboom  
# Copyright 2004-2026
# https://github.com/thecybermind/nocrash_qmm/
# 3-clause BSD license: https://opensource.org/license/bsd-3-clause
# Created By: Kevin Masterson < k.m.masterson@gmail.com >

BIN_32 := nocrash_qmm
BIN_64 := nocrash_qmm_x86_64

CC := g++

SRC_DIR := src
OBJ_DIR := obj
BIN_DIR := bin

SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp)

OBJ_FILES := $(SRC_FILES:$(SRC_DIR)/%.cpp=%.o)

CPPFLAGS := -MMD -MP -I ./include -isystem ../qmm_sdks -isystem ../qmm2/include
CFLAGS   := -Wall -pipe -fPIC
LDFLAGS  := -shared -fPIC
LDLIBS   :=

REL_CPPFLAGS := $(CPPFLAGS) -DNDEBUG
DBG_CPPFLAGS := $(CPPFLAGS) -D_DEBUG

REL_CFLAGS_32 := $(CFLAGS) -m32 -O2 -falign-functions=16 -fno-strict-aliasing -fstrength-reduce 
REL_CFLAGS_64 := $(CFLAGS) -O2 -falign-functions=16 -fno-strict-aliasing -fstrength-reduce 
DBG_CFLAGS_32 := $(CFLAGS) -m32 -g -pg
DBG_CFLAGS_64 := $(CFLAGS) -g -pg

REL_LDFLAGS_32 := $(LDFLAGS) -m32
REL_LDFLAGS_64 := $(LDFLAGS)
DBG_LDFLAGS_32 := $(LDFLAGS) -m32 -g -pg
DBG_LDFLAGS_64 := $(LDFLAGS) -g -pg

.PHONY: help all all32 all64 clean release release32 release64 debug debug32 debug64

help:
	@echo make targets:
	@echo all: release debug
	@echo all32: release32 debug32
	@echo all64: release64 debug64
	@echo release: release32 release64
	@echo release32: [32-bit release build]
	@echo release64: [64-bit release build]
	@echo debug: debug32 debug64
	@echo debug32: [32-bit debug build]
	@echo debug64: [64-bit debug build]

all: release debug
all32: release32 debug32
all64: release64 debug64
release: release32 release64
release32: $(BIN_DIR)/release/x86/$(BIN_32).so
release64: $(BIN_DIR)/release/x86_64/$(BIN_64).so
debug: debug32 debug64
debug32: $(BIN_DIR)/debug/x86/$(BIN_32).so
debug64: $(BIN_DIR)/debug/x86_64/$(BIN_64).so

$(BIN_DIR)/release/x86/$(BIN_32).so: $$(addprefix $(OBJ_DIR)/release/x86/,$(OBJ_FILES))
	mkdir -p $$(@D)
	$(CC) $(REL_LDFLAGS_32) -o $$@ $(LDLIBS) $$^
	
$(BIN_DIR)/release/x86_64/$(BIN_64).so: $$(addprefix $(OBJ_DIR)/release/x86_64/,$(OBJ_FILES))
	mkdir -p $$(@D)
	$(CC) $(REL_LDFLAGS_64) -o $$@ $(LDLIBS) $$^
	
$(BIN_DIR)/debug/x86/$(BIN_32).so: $$(addprefix $(OBJ_DIR)/debug/x86/,$(OBJ_FILES))
	mkdir -p $$(@D)
	$(CC) $(DBG_LDFLAGS_32) -o $$@ $(LDLIBS) $$^
	
$(BIN_DIR)/debug/x86_64/$(BIN_64).so: $$(addprefix $(OBJ_DIR)/debug/x86_64/,$(OBJ_FILES))
	mkdir -p $$(@D)
	$(CC) $(DBG_LDFLAGS_64) -o $$@ $(LDLIBS) $$^

$(OBJ_DIR)/release/x86/%.o: $(SRC_DIR)/%.cpp
	mkdir -p $$(@D)
	$(CC) $(REL_CPPFLAGS) $(REL_CFLAGS_32) -c $$< -o $$@

$(OBJ_DIR)/release/x86_64/%.o: $(SRC_DIR)/%.cpp
	mkdir -p $$(@D)
	$(CC) $(REL_CPPFLAGS) $(REL_CFLAGS_64) -c $$< -o $$@

$(OBJ_DIR)/debug/x86/%.o: $(SRC_DIR)/%.cpp
	mkdir -p $$(@D)
	$(CC) $(DBG_CPPFLAGS) $(DBG_CFLAGS_32) -c $$< -o $$@

$(OBJ_DIR)/debug/x86_64/%.o: $(SRC_DIR)/%.cpp
	mkdir -p $$(@D)
	$(CC) $(DBG_CPPFLAGS) $(DBG_CFLAGS_64) -c $$< -o $$@

-include $$(addprefix $(OBJ_DIR)/release/x86/,$(OBJ_FILES:.o=.d))
-include $$(addprefix $(OBJ_DIR)/release/x86_64/,$(OBJ_FILES:.o=.d))
-include $$(addprefix $(OBJ_DIR)/debug/x86/,$(OBJ_FILES:.o=.d))
-include $$(addprefix $(OBJ_DIR)/debug/x86_64/,$(OBJ_FILES:.o=.d))


clean:
	@$(RM) -rv $(BIN_DIR) $(OBJ_DIR)
