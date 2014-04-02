################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../API/API/Column.cpp \
../API/API/Database.cpp \
../API/API/Date.cpp \
../API/API/ExpressionTree.cpp \
../API/API/LogicHandler.cpp \
../API/API/Query_parser.cpp \
../API/API/Table.cpp \
../API/API/Table_parser.cpp \
../API/API/Time.cpp \
../API/API/global_parsing_methods.cpp \
../API/API/main.cpp \
../API/API/parser.cpp 

OBJS += \
./API/API/Column.o \
./API/API/Database.o \
./API/API/Date.o \
./API/API/ExpressionTree.o \
./API/API/LogicHandler.o \
./API/API/Query_parser.o \
./API/API/Table.o \
./API/API/Table_parser.o \
./API/API/Time.o \
./API/API/global_parsing_methods.o \
./API/API/main.o \
./API/API/parser.o 

CPP_DEPS += \
./API/API/Column.d \
./API/API/Database.d \
./API/API/Date.d \
./API/API/ExpressionTree.d \
./API/API/LogicHandler.d \
./API/API/Query_parser.d \
./API/API/Table.d \
./API/API/Table_parser.d \
./API/API/Time.d \
./API/API/global_parsing_methods.d \
./API/API/main.d \
./API/API/parser.d 


# Each subdirectory must supply rules for building sources it contributes
API/API/%.o: ../API/API/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


