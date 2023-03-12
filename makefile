CC = g++
BUILD_DIR = build
CPP_DIR = .
HPP_DIR = includes
STD = -std=c++11

SERVER_EXE_FILE = s.out
CLIENT_EXE_FILE = c.out

all: $(BUILD_DIR) $(SERVER_EXE_FILE) \
	$(BUILD_DIR) $(CLIENT_EXE_FILE)



SERVER_OBJECTS = \
	$(BUILD_DIR)/Date.o \
	$(BUILD_DIR)/Jsonhandler.o \
	$(BUILD_DIR)/Server.o \
	$(BUILD_DIR)/Function.o \


CLIENT_OBJECTS = \
	$(BUILD_DIR)/Function.o \
	$(BUILD_DIR)/Client.o \



DateSensitivityList = \
	$(CPP_DIR)/Date.cpp \
	$(HPP_DIR)/Date.hpp

FunctionSensitivityList = \
	$(CPP_DIR)/Function.cpp \
	$(HPP_DIR)/Function.hpp

JsonhandlerSensitivityList = \
	$(CPP_DIR)/Jsonhandler.cpp \
	$(HPP_DIR)/Jsonhandler.hpp

ServerSensitivityList = \
	$(CPP_DIR)/Server.cpp \
	$(HPP_DIR)/Server.hpp

ClientSensitivityList = \
	$(CPP_DIR)/Client.cpp \
	$(HPP_DIR)/Client.hpp



$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)


$(BUILD_DIR)/Date.o: $(DateensitivityList)
	$(CC) $(STD) -c $(CPP_DIR)/Date.cpp -o $(BUILD_DIR)/Date.o

$(BUILD_DIR)/Function.o: $(FunctionSensitivityList)
	$(CC) $(STD) -c $(CPP_DIR)/Function.cpp -o $(BUILD_DIR)/Function.o

$(BUILD_DIR)/Jsonhandler.o: $(jsonhandlerSensitivityList)
	$(CC) $(STD) -c $(CPP_DIR)/Jsonhandler.cpp -o $(BUILD_DIR)/Jsonhandler.o

$(BUILD_DIR)/Server.o: $(ServerSensitivityList)
	$(CC) $(STD) -c $(CPP_DIR)/Server.cpp -o $(BUILD_DIR)/Server.o

$(BUILD_DIR)/Client.o: $(ClientSensitivityList)
	$(CC) $(STD) -c $(CPP_DIR)/Client.cpp -o $(BUILD_DIR)/Client.o


$(SERVER_EXE_FILE): $(SERVER_OBJECTS)
	$(CC) $(STD) $(SERVER_OBJECTS) -o $(SERVER_EXE_FILE)

$(CLIENT_EXE_FILE): $(CLIENT_OBJECTS)
	$(CC) $(STD) $(CLIENT_OBJECTS) -o $(CLIENT_EXE_FILE)



.PHONY: clean
clean:
	rm -rf $(BUILD_DIR) *.o *.out