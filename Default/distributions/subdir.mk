################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../distributions/RandClass.cpp 

OBJS += \
./distributions/RandClass.o 

CPP_DEPS += \
./distributions/RandClass.d 


# Each subdirectory must supply rules for building sources it contributes
distributions/%.o: ../distributions/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/opt/simgrid/include -I/usr/include -I/usr/include/c++/7.3.0 -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


