################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
/System/Library/fltk-1.3.x-r7692/src/xutf8/lcUniConv/8bit_tab_to_h.c \
/System/Library/fltk-1.3.x-r7692/src/xutf8/lcUniConv/cjk_tab_to_h.c 

OBJS += \
./fltk-1.3.x-r7692/src/xutf8/lcUniConv/8bit_tab_to_h.o \
./fltk-1.3.x-r7692/src/xutf8/lcUniConv/cjk_tab_to_h.o 

C_DEPS += \
./fltk-1.3.x-r7692/src/xutf8/lcUniConv/8bit_tab_to_h.d \
./fltk-1.3.x-r7692/src/xutf8/lcUniConv/cjk_tab_to_h.d 


# Each subdirectory must supply rules for building sources it contributes
fltk-1.3.x-r7692/src/xutf8/lcUniConv/8bit_tab_to_h.o: /System/Library/fltk-1.3.x-r7692/src/xutf8/lcUniConv/8bit_tab_to_h.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

fltk-1.3.x-r7692/src/xutf8/lcUniConv/cjk_tab_to_h.o: /System/Library/fltk-1.3.x-r7692/src/xutf8/lcUniConv/cjk_tab_to_h.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


