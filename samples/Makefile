# SRCS = $(wildcard *.cpp)
OS_NAME = $(shell uname)
SRC_DIR = .
SRCS := $(shell find $(SRC_DIR) -type f -name "*.cpp")
OBJS = $(patsubst $(SRC_DIR)/%.cpp,%,$(SRCS))
# OBJS = $(patsubst .%,%,$(OBJS))
CXX := $(TOOL_PREFIX)g++
OUTPUT_DIR := output

ifneq ($(ARS_INC_DIR),)
ARS_INC = -I$(ARS_INC_DIR)
endif
ifneq ($(ARS_LIB_DIR),)
ARS_LIB = -L$(ARS_LIB_DIR)
endif

INC = $(ARS_INC) -I/usr/local/include
LIB = $(ARS_LIB) -L/usr/lib -L/usr/local/lib
ifeq ($(OS_NAME), Darwin)
INC += -I/usr/local/opt/openssl@1.1/include
LIB += -L/usr/local/opt/openssl@1.1/lib
endif

LIB += -laru -lssl -lcrypto -lglog -lpthread -lc

CFLAGS = -DWITH_OPENSSL -std=c++17 -g -W -Wall -o2 \
		-Wl,-rpath,$(ARS_LIB_DIR) \
		-Wno-deprecated-declarations \
		-Wno-class-memaccess -Wno-unknown-warning-option -Wno-unused-parameter -Wno-format

DEMOS = demo_os \
		demo_tcp demo_udp \
		demo_evpp \
		demo_crypto_uuid \
		demo_co \
		demo_cthpool

all: $(DEMOS)

demo_os:
	@mkdir -p $(OUTPUT_DIR)
	@echo "$(CXX) $@"
	@$(CXX) $@.cpp $(INC) $(LIB) $(CFLAGS) -o $(OUTPUT_DIR)/$@

demo_tcp:
	@mkdir -p $(OUTPUT_DIR)
	@echo "$(CXX) $@"
	@$(CXX) $@.cpp $(INC) $(LIB) $(CFLAGS) -o $(OUTPUT_DIR)/$@

demo_udp:
	@mkdir -p $(OUTPUT_DIR)
	@echo "$(CXX) $@"
	@$(CXX) $@.cpp $(INC) $(LIB) $(CFLAGS) -o $(OUTPUT_DIR)/$@

demo_evpp:
	@mkdir -p $(OUTPUT_DIR)/evpp
	@echo "$(CXX) $@"
	@$(CXX) evpp/demo_ev_loop_thread_pool.cpp $(INC) $(LIB) $(CFLAGS) -o $(OUTPUT_DIR)/evpp/demo_ev_loop_thread_pool
	@$(CXX) evpp/demo_ev_loop_thread.cpp $(INC) $(LIB) $(CFLAGS) -o $(OUTPUT_DIR)/evpp/demo_ev_loop_thread
	@$(CXX) evpp/demo_ev_loop.cpp $(INC) $(LIB) $(CFLAGS) -o $(OUTPUT_DIR)/evpp/demo_ev_loop
	@$(CXX) evpp/demo_tcp_client.cpp $(INC) $(LIB) $(CFLAGS) -o $(OUTPUT_DIR)/evpp/demo_tcp_client
	@$(CXX) evpp/demo_tcp_server.cpp $(INC) $(LIB) $(CFLAGS) -o $(OUTPUT_DIR)/evpp/demo_tcp_server
	@$(CXX) evpp/demo_udp_client.cpp $(INC) $(LIB) $(CFLAGS) -o $(OUTPUT_DIR)/evpp/demo_udp_client
	@$(CXX) evpp/demo_udp_server.cpp $(INC) $(LIB) $(CFLAGS) -o $(OUTPUT_DIR)/evpp/demo_udp_server

demo_crypto_uuid:
	@mkdir -p $(OUTPUT_DIR)
	@echo "$(CXX) $@"
	@$(CXX) $@.cpp $(INC) $(LIB) $(CFLAGS) -o $(OUTPUT_DIR)/$@

demo_co:
	@mkdir -p $(OUTPUT_DIR)
	@echo "$(CXX) $@"
	@$(CXX) $@.cpp $(INC) $(LIB) $(CFLAGS) -o $(OUTPUT_DIR)/$@

demo_cthpool:
	@mkdir -p $(OUTPUT_DIR)
	@echo "$(CXX) $@"
	@$(CXX) $@.cpp $(INC) $(LIB) $(CFLAGS) -o $(OUTPUT_DIR)/$@
