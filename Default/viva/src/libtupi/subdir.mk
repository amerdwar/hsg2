################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../viva/src/libtupi/bary.c \
../viva/src/libtupi/basic.c \
../viva/src/libtupi/box.c \
../viva/src/libtupi/cell.c \
../viva/src/libtupi/dict.c \
../viva/src/libtupi/dynar.c \
../viva/src/libtupi/layout.c \
../viva/src/libtupi/node.c \
../viva/src/libtupi/particle.c 

OBJS += \
./viva/src/libtupi/bary.o \
./viva/src/libtupi/basic.o \
./viva/src/libtupi/box.o \
./viva/src/libtupi/cell.o \
./viva/src/libtupi/dict.o \
./viva/src/libtupi/dynar.o \
./viva/src/libtupi/layout.o \
./viva/src/libtupi/node.o \
./viva/src/libtupi/particle.o 

C_DEPS += \
./viva/src/libtupi/bary.d \
./viva/src/libtupi/basic.d \
./viva/src/libtupi/box.d \
./viva/src/libtupi/cell.d \
./viva/src/libtupi/dict.d \
./viva/src/libtupi/dynar.d \
./viva/src/libtupi/layout.d \
./viva/src/libtupi/node.d \
./viva/src/libtupi/particle.d 


# Each subdirectory must supply rules for building sources it contributes
viva/src/libtupi/%.o: ../viva/src/libtupi/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


