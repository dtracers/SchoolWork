################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
O_SRCS += \
../bubble-sort.o \
../insertion-sort.o \
../option.o \
../radix-sort.o \
../selection-sort.o \
../shell-sort.o \
../sort.o 

CPP_SRCS += \
../bubble-sort.cpp \
../insertion-sort.cpp \
../number_maker.cpp \
../option.cpp \
../radix-sort.cpp \
../selection-sort.cpp \
../shell-sort.cpp \
../sort.cpp 

OBJS += \
./bubble-sort.o \
./insertion-sort.o \
./number_maker.o \
./option.o \
./radix-sort.o \
./selection-sort.o \
./shell-sort.o \
./sort.o 

CPP_DEPS += \
./bubble-sort.d \
./insertion-sort.d \
./number_maker.d \
./option.d \
./radix-sort.d \
./selection-sort.d \
./shell-sort.d \
./sort.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


