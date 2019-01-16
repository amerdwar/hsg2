################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../CMakeFiles/3.10.2/CompilerIdCXX/CMakeCXXCompilerId.cpp 

OBJS += \
./CMakeFiles/3.10.2/CompilerIdCXX/CMakeCXXCompilerId.o 

CPP_DEPS += \
./CMakeFiles/3.10.2/CompilerIdCXX/CMakeCXXCompilerId.d 


# Each subdirectory must supply rules for building sources it contributes
CMakeFiles/3.10.2/CompilerIdCXX/%.o: ../CMakeFiles/3.10.2/CompilerIdCXX/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/opt/simgrid/include -I/usr/include -I/usr/include/c++/7.3.0 -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


