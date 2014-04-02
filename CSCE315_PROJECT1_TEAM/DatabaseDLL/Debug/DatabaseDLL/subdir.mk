################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../DatabaseDLL/Column.cpp \
../DatabaseDLL/Database.cpp \
../DatabaseDLL/Date.cpp \
../DatabaseDLL/ExpressionTree.cpp \
../DatabaseDLL/LogicHandler.cpp \
../DatabaseDLL/OPERATIONS.cpp \
../DatabaseDLL/Query_parser.cpp \
../DatabaseDLL/Table.cpp \
../DatabaseDLL/Table_parser.cpp \
../DatabaseDLL/Time.cpp \
../DatabaseDLL/global_parsing_methods.cpp \
../DatabaseDLL/main.cpp \
../DatabaseDLL/parser.cpp 

OBJS += \
./DatabaseDLL/Column.o \
./DatabaseDLL/Database.o \
./DatabaseDLL/Date.o \
./DatabaseDLL/ExpressionTree.o \
./DatabaseDLL/LogicHandler.o \
./DatabaseDLL/OPERATIONS.o \
./DatabaseDLL/Query_parser.o \
./DatabaseDLL/Table.o \
./DatabaseDLL/Table_parser.o \
./DatabaseDLL/Time.o \
./DatabaseDLL/global_parsing_methods.o \
./DatabaseDLL/main.o \
./DatabaseDLL/parser.o 

CPP_DEPS += \
./DatabaseDLL/Column.d \
./DatabaseDLL/Database.d \
./DatabaseDLL/Date.d \
./DatabaseDLL/ExpressionTree.d \
./DatabaseDLL/LogicHandler.d \
./DatabaseDLL/OPERATIONS.d \
./DatabaseDLL/Query_parser.d \
./DatabaseDLL/Table.d \
./DatabaseDLL/Table_parser.d \
./DatabaseDLL/Time.d \
./DatabaseDLL/global_parsing_methods.d \
./DatabaseDLL/main.d \
./DatabaseDLL/parser.d 


# Each subdirectory must supply rules for building sources it contributes
DatabaseDLL/%.o: ../DatabaseDLL/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


