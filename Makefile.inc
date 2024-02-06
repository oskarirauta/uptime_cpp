UPTIME_DIR?=uptime
INCLUDES += -I./$(UPTIME_DIR)/include
UPTIME_OBJS:= \
	objs/uptime_t.o

objs/uptime_t.o: $(UPTIME_DIR)/src/uptime.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c -o $@ $<;
