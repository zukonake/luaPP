SOURCE_PATH := src/
OBJ_PATH := bin
DEPEND_PATH := depend
TEST_PATH := $(SOURCE_PATH)/test
TARGET_PATH := libluna.a
VERSION := 1.0.0-alpha-win64
SOURCES := $(shell find $(SOURCE_PATH) -path $(TEST_PATH) -prune -o -type f -name "*.cpp" -printf '%p ')
OBJS := $(addprefix $(OBJ_PATH)/,$(patsubst %.cpp,%.o,$(shell find $(SOURCE_PATH) -path $(TEST_PATH) -prune -o -type f -name "*.cpp" -exec basename {} \;)))
DEBUG := -g -O0 -DDEBUG
STD := -std=c++17
LDLIBS := -llua -lboost_unit_test_framework
INCFLAGS := -I include
LIBFLAGS := -L lib -L /usr/x86_64-w64-mingw32/lib
LDFLAGS := $(STD) -fPIC -Wall -Wextra $(LDLIBS) $(DEBUG) $(INCFLAGS) $(LIBFLAGS)
COMPILER := x86_64-w64-mingw32-g++
PREFIX := /usr/x86_64-w64-mingw32/lib

.PHONY : clean  test

$(TARGET_PATH) : $(OBJS)
	x86_64-w64-mingw32-ar rvs $@ $(OBJS)

test: $(TEST_OBJS) $(OBJS)
	$(COMPILER) $(LDFLAGS) $(TEST_OBJS) $(OBJS) -DTEST -o test.out

.SECONDEXPANSION:
$(OBJ_PATH)/%.o : $$(shell find $(SOURCE_PATH) -type f -name %.cpp)
	@mkdir -p $(OBJ_PATH)
	@mkdir -p $(DEPEND_PATH)
	$(COMPILER) $(CXXFLAGS) -c $< -o $@
	$(COMPILER) -MM $(CXXFLAGS) $< > $(DEPEND_PATH)/$*.d
	@sed -i '1s/^/bin\//' $(DEPEND_PATH)/$*.d

clean :
	$(RM) -r $(OBJ_PATH) $(DEPEND_PATH) $(TARGET_PATH)

-include $(shell find $(DEPEND_PATH) -type f -name "*.d" -printf '%p ')
