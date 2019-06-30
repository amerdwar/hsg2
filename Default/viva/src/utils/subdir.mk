################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../viva/src/utils/PajeThreadReader.cc \
../viva/src/utils/QPajeTypeFilter.cc \
../viva/src/utils/QPajeTypeModel.cc \
../viva/src/utils/VTSFrame.cc \
../viva/src/utils/VTSWindow.cc 

CC_DEPS += \
./viva/src/utils/PajeThreadReader.d \
./viva/src/utils/QPajeTypeFilter.d \
./viva/src/utils/QPajeTypeModel.d \
./viva/src/utils/VTSFrame.d \
./viva/src/utils/VTSWindow.d 

OBJS += \
./viva/src/utils/PajeThreadReader.o \
./viva/src/utils/QPajeTypeFilter.o \
./viva/src/utils/QPajeTypeModel.o \
./viva/src/utils/VTSFrame.o \
./viva/src/utils/VTSWindow.o 


# Each subdirectory must supply rules for building sources it contributes
viva/src/utils/%.o: ../viva/src/utils/%.cc
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/opt/simgrid/include -I/usr/include -I/usr/include/c++/7.3.0 -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


