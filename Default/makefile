################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm

# All of the sources participating in the build are defined here
-include sources.mk
-include viva/src/vv_treemap/subdir.mk
-include viva/src/viva/subdir.mk
-include viva/src/utils/subdir.mk
-include viva/src/libtupi/subdir.mk
-include messages/subdir.mk
-include hdfs/subdir.mk
-include distributions/subdir.mk
-include CMakeFiles/hsg.dir/Adder/subdir.mk
-include CMakeFiles/hsg.dir/subdir.mk
-include CMakeFiles/3.10.2/CompilerIdCXX/subdir.mk
-include CMakeFiles/3.10.2/CompilerIdC/subdir.mk
-include CMakeFiles/subdir.mk
-include Adder/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: hsg

# Tool invocations
hsg: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: GCC C++ Linker'
	g++  -o "hsg" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(CC_DEPS)$(C++_DEPS)$(EXECUTABLES)$(C_UPPER_DEPS)$(CXX_DEPS)$(OBJS)$(CPP_DEPS)$(C_DEPS) hsg
	-@echo ' '

.PHONY: all clean dependents

-include ../makefile.targets
