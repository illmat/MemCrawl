CC = g++
CC_FLAGS = -c -w

EXEC = MemCrawl
SOURCES = $(wildcard *.cpp)
OBJECTS = $(SOURCES:.cpp=.o)
OUT_DIR := bin
OBJS_DIR := obj
OUT_OBJS := $(addprefix $(OBJS_DIR)/,$(OBJECTS))
OUT_EXEC := $(OUT_DIR)/$(EXEC)

$(EXEC): $(OBJECTS)
	$(CC) $(OUT_OBJS) -o $(OUT_EXEC)

%.o: %.cpp
	$(CC) $(CC_FLAGS) $< -o $(OBJS_DIR)/$@

$(OBJECTS): | $(OBJS_DIR)

$(OBJS_DIR):
	mkdir -p $(OBJS_DIR)
	mkdir -p $(OUT_DIR)

clean:
	rm -rf $(OBJS_DIR) $(OUT_DIR)
