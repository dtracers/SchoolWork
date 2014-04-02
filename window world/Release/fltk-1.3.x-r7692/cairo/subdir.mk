################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CXX_SRCS += \
/System/Library/fltk-1.3.x-r7692/cairo/Fl_Cairo.cxx 

OBJS += \
./fltk-1.3.x-r7692/cairo/Fl_Cairo.o 

CXX_DEPS += \
./fltk-1.3.x-r7692/cairo/Fl_Cairo.d 


# Each subdirectory must supply rules for building sources it contributes
fltk-1.3.x-r7692/cairo/Fl_Cairo.o: /System/Library/fltk-1.3.x-r7692/cairo/Fl_Cairo.cxx
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/System/Library/fltk-1.3.x-r7692 -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


