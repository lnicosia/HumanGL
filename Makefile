S = src
O = obj
L = lib
I = inc
D = dep

define n


endef

CC = clang++ --std=c++20 -O3

include project.mk

ifneq ($L,)
	ifeq ($(wildcard $L),)
$(error lib directory not found : "$L"$n\
	If you are calling make from another directory, please give the path to the lib folder to this makefile)
	endif
endif

RM = rm -fv $1
RMDIR = $(if $(wildcard $1),$(if $(if $1,$(shell ls $1),),$(warning "$1 is not empty, not removed"),rmdir $1))

DEP =	$(SRC:$S/%.cpp=$D/%.d)
OBJ =	$(SRC:$S/%.cpp=$O/%.o)

TMP_DIRS=$(sort $(foreach DIRS,$(OBJ) $(DEP),$(dir $(shell echo '$(DIRS)' | sed ':do;p;s,^\(.*\)/[^/]*$$,\1,;\%^\(.*\)/[^/]*$$%b do;d'))))

INCLUDES += $I

$(foreach MOD,$(LIB_MOD),$(eval $(MOD)_DIR?=$L/$(MOD)))

LIB = $(foreach MOD,$(LIB_MOD),$(patsubst %,$($(MOD)_DIR)/%,$($(MOD)_LIB)))
INCLUDES += $(foreach MOD,$(LIB_MOD),$(patsubst %,$($(MOD)_DIR)/%,$($(MOD)_INC)))
LDFLAGS += $(foreach LIBRARY,$(LIB),-L$(dir $(LIBRARY)) -l$(patsubst lib%.a,%,$(notdir $(LIBRARY))))

LIB_DEP = $(LIB:%=%.d)

$(foreach MOD,$(CMAKE_LIB_MOD),$(eval $(MOD)_DIR?=$L/$(MOD)))

CMAKE_LIB = $(foreach MOD,$(CMAKE_LIB_MOD),$(if $($(MOD)_LIB),$(patsubst %,$($(MOD)_DIR)/build/%,$($(MOD)_LIB))))
INCLUDES += $(foreach MOD,$(CMAKE_LIB_MOD),$(if $($(MOD)_INC),$(patsubst %,$($(MOD)_DIR)/%,$($(MOD)_INC))))
LDFLAGS += $(foreach LIBRARY,$(CMAKE_LIB),-L$(dir $(LIBRARY)) -l$(patsubst lib%.a,%,$(notdir $(LIBRARY))))

UNAME_S = $(shell uname -s)
ifeq ($(UNAME_S),Linux)
	CPPFLAGS +=
	LDFLAGS +=
else ifeq ($(UNAME_S),Darwin)
	CPPFLAGS +=
	LDFLAGS +=
else
$(error OS not supported)
endif

.PHONY: all, clean, clean(), fclean, libclean, libclean(), realclean, re, relib, space, force

all: $(LIB_TARGET) $(EXEC_TARGET)

$(TMP_DIRS) $I:
	@mkdir -p $@

.SECONDEXPANSION:
$D/%.d: $S/%.cpp | $$(dir $$@) $(INCLUDES)
	$(info Updating dep list for $<)
	@$(CC) -MM $(CPPFLAGS) $(INCLUDES:%=-I%) $< | \
		sed 's,\($*\)\.o[ :]*,$O/\1.o $@ : ,g' > $@; \

.SECONDEXPANSION:
$(OBJ): $O/%.o: $S/%.cpp |  $$(dir $$@) $(INCLUDES)
	$(CC) -c -o $@ $(CPPFLAGS) $(INCLUDES:%=-I%) $<

define submodule_init
$(if $(wildcard $(1)),,tar -xf $(1).tar -C $(dir $(1)))
endef

define init_includes
$($(1)_INC:%=$($(1)_DIR)/%):
	$(call submodule_init,$($(1)_DIR))

endef

$(foreach MOD,$(LIB_MOD) $(CMAKE_LIB_MOD),$(eval $(call init_includes,$(MOD))))

$(foreach MOD,$(CMAKE_LIB_MOD),$(eval $($(MOD)_DIR)/build/$($(MOD)_LIB): MOD = $(MOD)))
$(CMAKE_LIB): DIR = $($(MOD)_DIR)/build

$(CMAKE_LIB):
	@mkdir -p $(DIR)
	@sh -c "cd $(DIR); cmake .."
	@$(MAKE) -C $(DIR)

$(foreach MOD,$(LIB_MOD),$(eval $($(MOD)_DIR)/$($(MOD)_LIB): MOD = $(MOD)))
$(LIB): DIR = $($(MOD)_DIR)

.SECONDEXPANSION:
$(LIB): $$(shell $$(MAKE) -C $$(DIR) -j4 -q $$($$(MOD)_LIB) > /dev/null || echo force)
	@$(MAKE) -j4 -C $(DIR) $($(MOD)_LIB) L='$L'

$(EXEC_TARGET): $(LIB) $(if $(wildcard $(if $(USING_EXTERNAL),noexternal,external)),clean) $(OBJ) project.mk | $(CMAKE_LIB)
	@touch $(if $(USING_EXTERNAL),external,noexternal)
	$(CC) -o $@ $(OBJ) $(CPPFLAGS) $(LDFLAGS)

$(LIB_TARGET): $(OBJ) project.mk
	ar -rc $@ $(OBJ)
	ranlib $@

$(patsubst %,clean@%,$(OBJ) $(DEP) external noexternal $(EXEC_TARGET) $(LIB_TARGET)): clean@%:
	@$(call RM,$*)

$(foreach FILE,$(OBJ) $(DEP) $(TMP_DIR),$(eval $(if $(filter-out ./,$(dir $(FILE))),clean@$(dir $(FILE)): clean@$(FILE),)))

$(TMP_DIRS:%=clean@%):
	@$(call RMDIR,$%)

clean: $(TMP_DIRS:%=clean@%) clean@external clean@noexternal

fclean: clean $(patsubst %,clean@%,$(EXEC_TARGET) $(LIB_TARGET))

$(LIB_MOD:%=libclean@$L/%): libclean@%:
	@$(MAKE) -s -C $* fclean "L="

$(CMAKE_LIB_MOD:%=libclean@$L/%/build): libclean@%:
	rm -Rf $*

libclean: $(LIB_MOD:%=libclean@$L/%)

realclean: $(CMAKE_LIB_MOD:%=libclean@$L/%/build) libclean fclean

re: fclean all
relib: libclean all

force:
	@true

-include customrules.mk

ifeq ($(filter %clean relib re %.d,$(MAKECMDGOALS)),)
-include $(patsubst $O%.o,$D%.d,$(wildcard $(OBJ)))
endif
