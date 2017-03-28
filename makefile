SOURCE_PATH := src
OBJ_PATH := bin
DOC_PATH := doc
DEPEND_PATH := depend
TEST_PATH := $(SOURCE_PATH)/test
TARGET_PATH := libluna-2.0.0-alpha.so
LINK_PATH := libluna.so
VERSION := 2.0.0
SOURCES := $(shell find $(SOURCE_PATH) -path $(TEST_PATH) -prune -o -type f -name "*.cpp" -printf '%p ')
OBJS := $(addprefix $(OBJ_PATH)/,$(patsubst %.cpp,%.o,$(shell find $(SOURCE_PATH) -path $(TEST_PATH) -prune -o -type f -name "*.cpp" -exec basename {} \;)))
TEST_SOURCES := $(shell find $(TEST_PATH) -type f -name "*.cpp" -printf '%p ')
TEST_OBJS := $(addprefix $(OBJ_PATH)/,$(patsubst %.cpp,%.o,$(shell find $(TEST_PATH) -type f -name "*.cpp" -exec basename {} \;)))
DEBUG := -g -O0 -DDEBUG
STD := -std=c++17
LDLIBS := -llua -lboost_unit_test_framework
INCFLAGS := -I include
LIBFLAGS := -L /usr/lib
CXXFLAGS := $(STD) -fPIC -Wall -Wextra $(DEBUG) $(INCFLAGS)
LDFLAGS := $(STD) -fPIC -Wall -Wextra $(LDLIBS) $(DEBUG) $(INCFLAGS) $(LIBFLAGS)
COMPILER := g++
PREFIX := /usr/lib
DOXYFILE := Doxyfile


.PHONY : clean install uninstall test doc

$(TARGET_PATH) : $(OBJS)
	$(COMPILER) -shared $(LDFLAGS) $(OBJS) -o $@

test: $(TEST_OBJS) $(OBJS)
	$(COMPILER) $(LDFLAGS) $(TEST_OBJS) $(OBJS) -DTEST -o test.out

.SECONDEXPANSION:
$(OBJ_PATH)/%.o : $$(shell find $(SOURCE_PATH) -type f -name %.cpp)
	@mkdir -p $(OBJ_PATH)
	@mkdir -p $(DEPEND_PATH)
	$(COMPILER) $(CXXFLAGS) -c $< -o $@
	$(COMPILER) -MM $(CXXFLAGS) $< > $(DEPEND_PATH)/$*.d
	@sed -i '1s/^/bin\//' $(DEPEND_PATH)/$*.d

install: $(TARGET_PATH)
	install -m 755 $(TARGET_PATH) $(PREFIX)/$(TARGET_PATH)
	ln -sf $(PREFIX)/$(TARGET_PATH) $(PREXIX)/$(LINK_PATH)

uninstall:
	rm -f $(PREFIX)/$(TARGET_PATH) $(PREFIX)/$(LINK_PATH)

clean :
	$(RM) -r $(OBJ_PATH) $(DEPEND_PATH) $(TARGET_PATH) $(DOC_PATH)

doc :
	@mkdir -p $(DOC_PATH)
	doxygen $(DOXYFILE)

-include $(shell find $(DEPEND_PATH) -type f -name "*.d" -printf '%p ')
