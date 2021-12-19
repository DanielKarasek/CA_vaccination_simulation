

BIN_DIR = bin
SRC_DIR = src
OBJ_DIR = obj
TARGET_EXEC = CA_SIMULATOR


SRCS := $(wildcard $(SRC_DIR)/*.cpp)
OBJS := $(SRCS:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

DEPS := $(OBJS:.o=.d)


CXX = g++

CPPFLAGS = -Iinclude -MMD -MP
CXXFLAGS = -Wall -pedantic -g --std=c++2a
# CXXFLAGS = -Wall -O2
LDFLAGS = 




.PHONY: clean all run print


$(BIN_DIR)/$(TARGET_EXEC): $(OBJS) | $(BIN_DIR) 
	$(CXX) $(LDFLAGS) $^ $(LDLIBS) -o $@
	
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<  

$(OBJ_DIR):
	mkdir -p $@

$(BIN_DIR):
	mkdir -p $@

run: $(BIN_DIR)/$(TARGET_EXEC)
	$(BIN_DIR)/$(TARGET_EXEC)

print: 
	echo $(SRCS)
	echo $(OBJS)
clean:
	@$(RM) -rv $(BIN_DIR) $(OBJ_DIR)

-include $(DEPS)