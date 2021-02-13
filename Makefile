TARGET ?= shadow
SRC_DIRS ?= ./Core \
			./Function \
			./Main

SRCS := $(shell find $(SRC_DIRS) -name *.cpp)
OBJS := $(addsuffix .o,$(basename $(SRCS)))
DEPS := $(OBJS:.o=.d)

INC_DIRS := $(shell find $(SRC_DIRS) -type d)
INC_FLAGS := $(addprefix -I,$(INC_DIRS))

CPPFLAGS ?= $(INC_FLAGS) -MMD -MP

CPPFLAGS += -std=c++17

LDFLAGS:= -lcryptopp -fopenmp

$(TARGET): $(OBJS)
	$(CXX) -o $@ $^ $(LDFLAGS)


.PHONY: clean
clean:
	$(RM) $(TARGET) $(OBJS) $(DEPS)

-include $(DEPS)


