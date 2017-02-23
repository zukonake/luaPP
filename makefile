SOURCE_PATH := src/
BUILD_PATH := build/
OBJ_PATH := $(BUILD_PATH)obj/
VERSION := 0.10.0-alpha-win64
TARGET_PATH := libluapp.a
SOURCES := $(shell find $(SOURCE_PATH) -type f -name "*.cpp" -printf '%p ')
HEADERS := $(shell find $(SOURCE_PATH) -type f -name "*.hpp" -printf '%p ')
OBJS := $(addprefix $(OBJ_PATH),$(patsubst %.cpp,%.o,$(shell find $(SOURCE_PATH) -type f -name "*.cpp" -exec basename {} \;)))
DEBUG := -g -O0
STD := -std=c++14
LDLIBS := -llua
INCFLAGS := -I include
LIBFLAGS := -L lib -L /usr/x86_64-w64-mingw32/lib
CXXFLAGS := $(STD) -fPIC -Wall -Wextra $(DEBUG) $(INCFLAGS)
COMPILER := x86_64-w64-mingw32-g++
PREFIX := /usr/x86_64-w64-mingw32/lib

.PHONY : clean install uninstall

$(TARGET_PATH) : $(OBJS)
	x86_64-w64-mingw32-ar rvs $@ $(OBJS)
	
.SECONDEXPANSION:
$(OBJ_PATH)%.o : $$(shell find $(SOURCE_PATH) -type f -name %.cpp)
	@mkdir -p $(BUILD_PATH)
	@mkdir -p $(OBJ_PATH)
	$(COMPILER) $(CXXFLAGS) -c $< -o $@
	$(COMPILER) -MM $(CXXFLAGS) $< > $(BUILD_PATH)$*.d
	@sed -i '1s/^/build\/obj\//' $(BUILD_PATH)$*.d

install: $(TARGET_PATH)
	cp $< $(DESTDIR)$(PREFIX)/$<
	chmod 644 $(DESTDIR)$(PREFIX)/$<

uninstall:
	rm -f $(DESTDIR)$(PREFIX)/$(TARGET_PATH)

clean :
	$(RM) -r $(BUILD_PATH) *~ bin $(TARGET_PATH) vgcore* callgrind* *.so

-include $(shell find $(BUILD_PATH) -type f -name "*.d" -printf '%p ')
