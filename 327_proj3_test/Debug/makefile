################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/subdir.mk
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
all: 327_proj3_test

dependents:
	-cd /home/tfriend27/327_proj3_fileIO/Debug && $(MAKE) all
	-cd /home/tfriend27/327_proj3_stringparser/Debug && $(MAKE) all

# Tool invocations
327_proj3_test: $(OBJS) $(USER_OBJS) /home/tfriend27/327_proj3_fileIO/Debug/lib327_proj3_fileIO.a /home/tfriend27/327_proj3_stringparser/Debug/lib327_proj3_stringparser.a
	@echo 'Building target: $@'
	@echo 'Invoking: GCC C++ Linker'
	g++ -L../../327_proj3_test/327_proj3_fileIO/Debug -L../../327_proj3_test/327_proj3_stringparser/Debug -o "327_proj3_test" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(CC_DEPS)$(C++_DEPS)$(EXECUTABLES)$(C_UPPER_DEPS)$(CXX_DEPS)$(OBJS)$(CPP_DEPS)$(C_DEPS) 327_proj3_test
	-@echo ' '

.PHONY: all clean dependents
/home/tfriend27/327_proj3_fileIO/Debug/lib327_proj3_fileIO.a:
/home/tfriend27/327_proj3_stringparser/Debug/lib327_proj3_stringparser.a:

-include ../makefile.targets
