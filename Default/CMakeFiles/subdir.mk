################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CXX_SRCS += \
../CMakeFiles/feature_tests.cxx 

C_SRCS += \
../CMakeFiles/feature_tests.c 

CXX_DEPS += \
./CMakeFiles/feature_tests.d 

OBJS += \
./CMakeFiles/feature_tests.o 

C_DEPS += \
./CMakeFiles/feature_tests.d 


# Each subdirectory must supply rules for building sources it contributes
CMakeFiles/%.o: ../CMakeFiles/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

CMakeFiles/%.o: ../CMakeFiles/%.cxx
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/opt/simgrid/include -I/usr/include -I/usr/include/c++/7.3.0 -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


