################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../viva/src/vv_treemap/PajeTreemap.cc \
../viva/src/vv_treemap/VTApplication.cc \
../viva/src/vv_treemap/VTFrame.cc \
../viva/src/vv_treemap/VTWidget+Paje.cc \
../viva/src/vv_treemap/VTWidget+Treemap.cc \
../viva/src/vv_treemap/VTWidget.cc \
../viva/src/vv_treemap/VTWindow.cc \
../viva/src/vv_treemap/main.cc 

CC_DEPS += \
./viva/src/vv_treemap/PajeTreemap.d \
./viva/src/vv_treemap/VTApplication.d \
./viva/src/vv_treemap/VTFrame.d \
./viva/src/vv_treemap/VTWidget+Paje.d \
./viva/src/vv_treemap/VTWidget+Treemap.d \
./viva/src/vv_treemap/VTWidget.d \
./viva/src/vv_treemap/VTWindow.d \
./viva/src/vv_treemap/main.d 

OBJS += \
./viva/src/vv_treemap/PajeTreemap.o \
./viva/src/vv_treemap/VTApplication.o \
./viva/src/vv_treemap/VTFrame.o \
./viva/src/vv_treemap/VTWidget+Paje.o \
./viva/src/vv_treemap/VTWidget+Treemap.o \
./viva/src/vv_treemap/VTWidget.o \
./viva/src/vv_treemap/VTWindow.o \
./viva/src/vv_treemap/main.o 


# Each subdirectory must supply rules for building sources it contributes
viva/src/vv_treemap/%.o: ../viva/src/vv_treemap/%.cc
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/opt/simgrid/include -I/usr/include -I/usr/include/c++/7.3.0 -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


