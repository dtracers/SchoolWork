################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include fltk-1.3.x-r7692/zlib/subdir.mk
-include fltk-1.3.x-r7692/test/subdir.mk
-include fltk-1.3.x-r7692/src/xutf8/utils/subdir.mk
-include fltk-1.3.x-r7692/src/xutf8/subdir.mk
-include fltk-1.3.x-r7692/src/xutf8/lcUniConv/subdir.mk
-include fltk-1.3.x-r7692/src/subdir.mk
-include fltk-1.3.x-r7692/png/subdir.mk
-include fltk-1.3.x-r7692/misc/subdir.mk
-include fltk-1.3.x-r7692/jpeg/subdir.mk
-include fltk-1.3.x-r7692/ide/deprecated/Xcode3.1/Project\ Templates/FLTK/subdir.mk
-include fltk-1.3.x-r7692/ide/Xcode3/Project\ Templates/FLTK/subdir.mk
-include fltk-1.3.x-r7692/fluid/subdir.mk
-include fltk-1.3.x-r7692/examples/subdir.mk
-include fltk-1.3.x-r7692/cairo/subdir.mk
-include fltk-1.3.x-r7692/CMake/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: window\ world

# Tool invocations
window\ world: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: MacOS X C++ Linker'
	g++ -L/usr/include -o "window world" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(C++_DEPS)$(OBJS)$(C_DEPS)$(CC_DEPS)$(CPP_DEPS)$(EXECUTABLES)$(CXX_DEPS)$(C_UPPER_DEPS) "window world"
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
