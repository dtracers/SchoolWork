################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Schedulable.cpp \
../Scheduler.cpp \
../Semaphore.cpp \
../task.cpp \
../task_test_step1.cpp \
../task_test_step2.cpp 

OBJS += \
./Schedulable.o \
./Scheduler.o \
./Semaphore.o \
./task.o \
./task_test_step1.o \
./task_test_step2.o 

CPP_DEPS += \
./Schedulable.d \
./Scheduler.d \
./Semaphore.d \
./task.d \
./task_test_step1.d \
./task_test_step2.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


