SOURCE_PATH := src/
BUILD_PATH := build/
OBJ_PATH := $(BUILD_PATH)obj/
DEBUG_PATH := libluapp.so
RELEASE_PATH := libluapp.so
TARGET_PATH := $(DEBUG_PATH)
SOURCES := $(shell find $(SOURCE_PATH) -type f -name "*.cpp" -printf '%p ')
HEADERS := $(shell find $(SOURCE_PATH) -type f -name "*.hpp" -printf '%p ')
OBJS := $(addprefix $(OBJ_PATH),$(patsubst %.cpp,%.o,$(shell find $(SOURCE_PATH) -type f -name "*.cpp" -exec basename {} \;)))
DEBUG := -g -O0
STD := -std=c++14
LDLIBS := -llua5.2
INCFLAGS := -I include -I src
LIBFLAGS := -L lib -L /usr/lib
CXXFLAGS := $(STD) -fPIC -Wall -Wextra $(DEBUG) $(INCFLAGS)
LDFLAGS := $(STD) -fPIC -shared -Wall -Wextra $(LDLIBS) $(DEBUG) $(INCFLAGS) $(LIBFLAGS)
COMPILER := g++

.PHONY : clean

$(TARGET_PATH) : $(OBJS)
	$(COMPILER) $(LDFLAGS) $(OBJS) -o $@

.SECONDEXPANSION:
$(OBJ_PATH)%.o : $$(shell find $(SOURCE_PATH) -type f -name %.cpp)
	@mkdir -p $(BUILD_PATH)
	@mkdir -p $(OBJ_PATH)
	$(COMPILER) $(CXXFLAGS) -c $< -o $@
	$(COMPILER) -MM $(CXXFLAGS) $< > $(BUILD_PATH)$*.d
	@sed -i '1s/^/build\/obj\//' $(BUILD_PATH)$*.d

clean :
	$(RM) -r $(BUILD_PATH) *~ bin $(TARGET_PATH) vgcore* callgrind* *.so

-include $(shell find $(BUILD_PATH) -type f -name "*.d" -printf '%p ')
