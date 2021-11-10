S = src
O = obj
L = lib
I = inc
D = dep

define n


endef

include project.mk

ifneq ($L,)
	ifeq ($(wildcard $L),)
$(error lib directory not found : "$L"$n\
	If you are calling make from another directory, please give the path to the lib folder to this makefile)
	endif
endif

CC = clang++ --std=c++17
RM = rm -fv $1
RMDIR = $(if $(wildcard $1),$(if $(if $1,$(shell ls $1),),$(warning "$1 is not empty, not removed"),rmdir $1))

DEP =	$(SRC:$S/%.cpp=$D/%.d)
OBJ =	$(SRC:$S/%.cpp=$O/%.o)

INCLUDES += $I

$(eval $(foreach MOD,$(LIB_MOD),$(MOD)_DIR?=$L/$(MOD)))

LIB = $(foreach MOD,$(LIB_MOD),$($(MOD)_DIR)/$($(MOD)_LIB))
INCLUDES += $(foreach MOD,$(LIB_MOD),$($(MOD)_DIR)/$($(MOD)_INC))
LDFLAGS += $(foreach LIBRARY,$(LIB),-L$(dir $(LIBRARY)) -l$(patsubst lib%.a,%,$(notdir $(LIBRARY))))

LIB_DEP = $(LIB:%=%.d)

$(eval $(foreach MOD,$(CMAKE_LIB_MOD),$(MOD)_DIR?=$L/$(MOD)))

CMAKE_LIB = $(foreach MOD,$(CMAKE_LIB_MOD),$(if $($(MOD)_LIB),$($(MOD)_DIR)/build/$($(MOD)_LIB),))
INCLUDES += $(foreach MOD,$(CMAKE_LIB_MOD),$(if $($(MOD)_INC),$($(MOD)_DIR)/$($(MOD)_INC),))
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

.PHONY: all, clean, fclean, libclean, realclean, re, relib, space, force, $(LIB_DEP)

all: $(LIB_TARGET) $(EXEC_TARGET)

$D:
	@mkdir -p $D

$O:
	@mkdir -p $O

$D/%.d: $S/%.cpp | $D $(INCLUDES)
	$(info Updating dep list for $<)
	@$(CC) -MM $(CPPFLAGS) $(INCLUDES:%=-I%) $< | \
		sed 's,\($*\)\.o[ :]*,$O\1.o $@ : ,g' > $@; \

$O/%.o: $S/%.cpp | $O
	$(CC) -c -o $@ $(CPPFLAGS) $(INCLUDES:%=-I%) $<

define submodule_init
$(if $(shell git submodule status $(1) | grep '^-'),@git submodule update --init $(1),@#)
endef

$(eval $(foreach MOD,$(CMAKE_LIB_MOD),$($(MOD)_DIR)/build/$($(MOD)_LIB): MOD = $(MOD)))
$(CMAKE_LIB): DIR = $($(MOD)_DIR)/build

$(CMAKE_LIB):
	$(call submodule_init,$(DIR))
	@mkdir -p $(DIR)
	@sh -c "cd $(DIR); cmake .."
	@$(MAKE) -C $(DIR)

$(eval $(foreach MOD,$(LIB_MOD),$($(MOD)_DIR)/$($(MOD)_LIB): MOD = $(MOD)))
$(LIB): DIR = $($(MOD)_DIR)

$(LIB):
	$(call submodule_init,$(DIR))
	make -C $(DIR) $($(MOD)_LIB) L='$(abspath $L)'

$(EXEC_TARGET): $(OBJ) $(LIB) project.mk | $(CMAKE_LIB)
	$(CC) -o $@ $(OBJ) $(LDFLAGS)

$(LIB_TARGET): $(OBJ) project.mk
	ar -rc $@ $(OBJ)
	ranlib $@

clean($O/% $D/%):
	@$(call RM,$%)

clean($(EXEC_TARGET) $(LIB_TARGET)):
	@$(call RM,$%)

clean($O): $(foreach file,$(OBJ),clean($(file)))
	@$(call RMDIR,$%)

clean($D): $(foreach file,$(DEP),clean($(file)))
	@$(call RMDIR,$%)

clean: clean($O $D)

fclean: clean clean($(EXEC_TARGET) $(LIB_TARGET))

libclean($(LIB_MOD:%=$L/%)):
	$(MAKE) -s -C $% fclean "L="

libclean($(CMAKE_LIB_MOD:%=$L/%/build)):
	rm -Rf $%

libclean: libclean($(LIB_MOD:%=$L/%))

realclean: libclean($(CMAKE_LIB_MOD:%=$L/%/build))

re: fclean all
relib: libclean all

force:
	@true

-include customrules.mk

ifeq ($(filter %clean relib re %.d,$(MAKECMDGOALS)),)
-include $(patsubst $O%.o,$D%.d,$(wildcard $(OBJ)))
endif
