################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Creating_table_parser.cpp \
../Expression_handler.cpp \
../Query_parser.cpp \
../main.cpp \
../parser.cpp 

OBJS += \
./Creating_table_parser.o \
./Expression_handler.o \
./Query_parser.o \
./main.o \
./parser.o 

CPP_DEPS += \
./Creating_table_parser.d \
./Expression_handler.d \
./Query_parser.d \
./main.d \
./parser.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


