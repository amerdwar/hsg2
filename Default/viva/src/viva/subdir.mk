################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../viva/src/viva/TimeInterval.cc \
../viva/src/viva/VivaApplication.cc \
../viva/src/viva/VivaGraph.cc \
../viva/src/viva/VivaGraphView.cc \
../viva/src/viva/VivaLayoutRunner.cc \
../viva/src/viva/VivaNode.cc \
../viva/src/viva/VivaRenderingThread.cc \
../viva/src/viva/VivaWindow.cc \
../viva/src/viva/main.cc 

CC_DEPS += \
./viva/src/viva/TimeInterval.d \
./viva/src/viva/VivaApplication.d \
./viva/src/viva/VivaGraph.d \
./viva/src/viva/VivaGraphView.d \
./viva/src/viva/VivaLayoutRunner.d \
./viva/src/viva/VivaNode.d \
./viva/src/viva/VivaRenderingThread.d \
./viva/src/viva/VivaWindow.d \
./viva/src/viva/main.d 

OBJS += \
./viva/src/viva/TimeInterval.o \
./viva/src/viva/VivaApplication.o \
./viva/src/viva/VivaGraph.o \
./viva/src/viva/VivaGraphView.o \
./viva/src/viva/VivaLayoutRunner.o \
./viva/src/viva/VivaNode.o \
./viva/src/viva/VivaRenderingThread.o \
./viva/src/viva/VivaWindow.o \
./viva/src/viva/main.o 


# Each subdirectory must supply rules for building sources it contributes
viva/src/viva/%.o: ../viva/src/viva/%.cc
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/opt/simgrid/include -I/usr/include -I/usr/include/c++/7.3.0 -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


