################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../jar_main.cpp \
../jar_test.cpp \
../llist_jar.cpp \
../marble.cpp \
../marble_main.cpp \
../vector_jar.cpp 

OBJS += \
./jar_main.o \
./jar_test.o \
./llist_jar.o \
./marble.o \
./marble_main.o \
./vector_jar.o 

CPP_DEPS += \
./jar_main.d \
./jar_test.d \
./llist_jar.d \
./marble.d \
./marble_main.d \
./vector_jar.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


