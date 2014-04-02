################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../API/API/Creating_table_parser.cpp \
../API/API/Database.cpp \
../API/API/Query_parser.cpp \
../API/API/Row.cpp \
../API/API/Table.cpp \
../API/API/main.cpp \
../API/API/parser.cpp 

OBJS += \
./API/API/Creating_table_parser.o \
./API/API/Database.o \
./API/API/Query_parser.o \
./API/API/Row.o \
./API/API/Table.o \
./API/API/main.o \
./API/API/parser.o 

CPP_DEPS += \
./API/API/Creating_table_parser.d \
./API/API/Database.d \
./API/API/Query_parser.d \
./API/API/Row.d \
./API/API/Table.d \
./API/API/main.d \
./API/API/parser.d 


# Each subdirectory must supply rules for building sources it contributes
API/API/%.o: ../API/API/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


