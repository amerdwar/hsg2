################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../hdfs/Chunk.cpp \
../hdfs/Client.cpp \
../hdfs/DataNode.cpp \
../hdfs/DirFiles.cpp \
../hdfs/HdfsClient.cpp \
../hdfs/HdfsClient_test.cpp \
../hdfs/HdfsFile.cpp \
../hdfs/NameNode.cpp 

OBJS += \
./hdfs/Chunk.o \
./hdfs/Client.o \
./hdfs/DataNode.o \
./hdfs/DirFiles.o \
./hdfs/HdfsClient.o \
./hdfs/HdfsClient_test.o \
./hdfs/HdfsFile.o \
./hdfs/NameNode.o 

CPP_DEPS += \
./hdfs/Chunk.d \
./hdfs/Client.d \
./hdfs/DataNode.d \
./hdfs/DirFiles.d \
./hdfs/HdfsClient.d \
./hdfs/HdfsClient_test.d \
./hdfs/HdfsFile.d \
./hdfs/NameNode.d 


# Each subdirectory must supply rules for building sources it contributes
hdfs/%.o: ../hdfs/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/opt/simgrid/include -I/usr/include -I/usr/include/c++/7.3.0 -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


