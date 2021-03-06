# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

# Default target executed when no arguments are given to make.
default_target: all

.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/amer/hsg

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/amer/hsg

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/usr/bin/cmake -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache

.PHONY : rebuild_cache/fast

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "No interactive CMake dialog available..."
	/usr/bin/cmake -E echo No\ interactive\ CMake\ dialog\ available.
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache

.PHONY : edit_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /home/amer/hsg/CMakeFiles /home/amer/hsg/CMakeFiles/progress.marks
	$(MAKE) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /home/amer/hsg/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean

.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named hsg

# Build rule for target.
hsg: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 hsg
.PHONY : hsg

# fast build rule for target.
hsg/fast:
	$(MAKE) -f CMakeFiles/hsg.dir/build.make CMakeFiles/hsg.dir/build
.PHONY : hsg/fast

Main.o: Main.cpp.o

.PHONY : Main.o

# target to build an object file
Main.cpp.o:
	$(MAKE) -f CMakeFiles/hsg.dir/build.make CMakeFiles/hsg.dir/Main.cpp.o
.PHONY : Main.cpp.o

Main.i: Main.cpp.i

.PHONY : Main.i

# target to preprocess a source file
Main.cpp.i:
	$(MAKE) -f CMakeFiles/hsg.dir/build.make CMakeFiles/hsg.dir/Main.cpp.i
.PHONY : Main.cpp.i

Main.s: Main.cpp.s

.PHONY : Main.s

# target to generate assembly for a file
Main.cpp.s:
	$(MAKE) -f CMakeFiles/hsg.dir/build.make CMakeFiles/hsg.dir/Main.cpp.s
.PHONY : Main.cpp.s

distributions/RandClass.o: distributions/RandClass.cpp.o

.PHONY : distributions/RandClass.o

# target to build an object file
distributions/RandClass.cpp.o:
	$(MAKE) -f CMakeFiles/hsg.dir/build.make CMakeFiles/hsg.dir/distributions/RandClass.cpp.o
.PHONY : distributions/RandClass.cpp.o

distributions/RandClass.i: distributions/RandClass.cpp.i

.PHONY : distributions/RandClass.i

# target to preprocess a source file
distributions/RandClass.cpp.i:
	$(MAKE) -f CMakeFiles/hsg.dir/build.make CMakeFiles/hsg.dir/distributions/RandClass.cpp.i
.PHONY : distributions/RandClass.cpp.i

distributions/RandClass.s: distributions/RandClass.cpp.s

.PHONY : distributions/RandClass.s

# target to generate assembly for a file
distributions/RandClass.cpp.s:
	$(MAKE) -f CMakeFiles/hsg.dir/build.make CMakeFiles/hsg.dir/distributions/RandClass.cpp.s
.PHONY : distributions/RandClass.cpp.s

hdfs/Chunk.o: hdfs/Chunk.cpp.o

.PHONY : hdfs/Chunk.o

# target to build an object file
hdfs/Chunk.cpp.o:
	$(MAKE) -f CMakeFiles/hsg.dir/build.make CMakeFiles/hsg.dir/hdfs/Chunk.cpp.o
.PHONY : hdfs/Chunk.cpp.o

hdfs/Chunk.i: hdfs/Chunk.cpp.i

.PHONY : hdfs/Chunk.i

# target to preprocess a source file
hdfs/Chunk.cpp.i:
	$(MAKE) -f CMakeFiles/hsg.dir/build.make CMakeFiles/hsg.dir/hdfs/Chunk.cpp.i
.PHONY : hdfs/Chunk.cpp.i

hdfs/Chunk.s: hdfs/Chunk.cpp.s

.PHONY : hdfs/Chunk.s

# target to generate assembly for a file
hdfs/Chunk.cpp.s:
	$(MAKE) -f CMakeFiles/hsg.dir/build.make CMakeFiles/hsg.dir/hdfs/Chunk.cpp.s
.PHONY : hdfs/Chunk.cpp.s

hdfs/Client.o: hdfs/Client.cpp.o

.PHONY : hdfs/Client.o

# target to build an object file
hdfs/Client.cpp.o:
	$(MAKE) -f CMakeFiles/hsg.dir/build.make CMakeFiles/hsg.dir/hdfs/Client.cpp.o
.PHONY : hdfs/Client.cpp.o

hdfs/Client.i: hdfs/Client.cpp.i

.PHONY : hdfs/Client.i

# target to preprocess a source file
hdfs/Client.cpp.i:
	$(MAKE) -f CMakeFiles/hsg.dir/build.make CMakeFiles/hsg.dir/hdfs/Client.cpp.i
.PHONY : hdfs/Client.cpp.i

hdfs/Client.s: hdfs/Client.cpp.s

.PHONY : hdfs/Client.s

# target to generate assembly for a file
hdfs/Client.cpp.s:
	$(MAKE) -f CMakeFiles/hsg.dir/build.make CMakeFiles/hsg.dir/hdfs/Client.cpp.s
.PHONY : hdfs/Client.cpp.s

hdfs/DataNode.o: hdfs/DataNode.cpp.o

.PHONY : hdfs/DataNode.o

# target to build an object file
hdfs/DataNode.cpp.o:
	$(MAKE) -f CMakeFiles/hsg.dir/build.make CMakeFiles/hsg.dir/hdfs/DataNode.cpp.o
.PHONY : hdfs/DataNode.cpp.o

hdfs/DataNode.i: hdfs/DataNode.cpp.i

.PHONY : hdfs/DataNode.i

# target to preprocess a source file
hdfs/DataNode.cpp.i:
	$(MAKE) -f CMakeFiles/hsg.dir/build.make CMakeFiles/hsg.dir/hdfs/DataNode.cpp.i
.PHONY : hdfs/DataNode.cpp.i

hdfs/DataNode.s: hdfs/DataNode.cpp.s

.PHONY : hdfs/DataNode.s

# target to generate assembly for a file
hdfs/DataNode.cpp.s:
	$(MAKE) -f CMakeFiles/hsg.dir/build.make CMakeFiles/hsg.dir/hdfs/DataNode.cpp.s
.PHONY : hdfs/DataNode.cpp.s

hdfs/DirFiles.o: hdfs/DirFiles.cpp.o

.PHONY : hdfs/DirFiles.o

# target to build an object file
hdfs/DirFiles.cpp.o:
	$(MAKE) -f CMakeFiles/hsg.dir/build.make CMakeFiles/hsg.dir/hdfs/DirFiles.cpp.o
.PHONY : hdfs/DirFiles.cpp.o

hdfs/DirFiles.i: hdfs/DirFiles.cpp.i

.PHONY : hdfs/DirFiles.i

# target to preprocess a source file
hdfs/DirFiles.cpp.i:
	$(MAKE) -f CMakeFiles/hsg.dir/build.make CMakeFiles/hsg.dir/hdfs/DirFiles.cpp.i
.PHONY : hdfs/DirFiles.cpp.i

hdfs/DirFiles.s: hdfs/DirFiles.cpp.s

.PHONY : hdfs/DirFiles.s

# target to generate assembly for a file
hdfs/DirFiles.cpp.s:
	$(MAKE) -f CMakeFiles/hsg.dir/build.make CMakeFiles/hsg.dir/hdfs/DirFiles.cpp.s
.PHONY : hdfs/DirFiles.cpp.s

hdfs/Hdd.o: hdfs/Hdd.cpp.o

.PHONY : hdfs/Hdd.o

# target to build an object file
hdfs/Hdd.cpp.o:
	$(MAKE) -f CMakeFiles/hsg.dir/build.make CMakeFiles/hsg.dir/hdfs/Hdd.cpp.o
.PHONY : hdfs/Hdd.cpp.o

hdfs/Hdd.i: hdfs/Hdd.cpp.i

.PHONY : hdfs/Hdd.i

# target to preprocess a source file
hdfs/Hdd.cpp.i:
	$(MAKE) -f CMakeFiles/hsg.dir/build.make CMakeFiles/hsg.dir/hdfs/Hdd.cpp.i
.PHONY : hdfs/Hdd.cpp.i

hdfs/Hdd.s: hdfs/Hdd.cpp.s

.PHONY : hdfs/Hdd.s

# target to generate assembly for a file
hdfs/Hdd.cpp.s:
	$(MAKE) -f CMakeFiles/hsg.dir/build.make CMakeFiles/hsg.dir/hdfs/Hdd.cpp.s
.PHONY : hdfs/Hdd.cpp.s

hdfs/HdfsClient.o: hdfs/HdfsClient.cpp.o

.PHONY : hdfs/HdfsClient.o

# target to build an object file
hdfs/HdfsClient.cpp.o:
	$(MAKE) -f CMakeFiles/hsg.dir/build.make CMakeFiles/hsg.dir/hdfs/HdfsClient.cpp.o
.PHONY : hdfs/HdfsClient.cpp.o

hdfs/HdfsClient.i: hdfs/HdfsClient.cpp.i

.PHONY : hdfs/HdfsClient.i

# target to preprocess a source file
hdfs/HdfsClient.cpp.i:
	$(MAKE) -f CMakeFiles/hsg.dir/build.make CMakeFiles/hsg.dir/hdfs/HdfsClient.cpp.i
.PHONY : hdfs/HdfsClient.cpp.i

hdfs/HdfsClient.s: hdfs/HdfsClient.cpp.s

.PHONY : hdfs/HdfsClient.s

# target to generate assembly for a file
hdfs/HdfsClient.cpp.s:
	$(MAKE) -f CMakeFiles/hsg.dir/build.make CMakeFiles/hsg.dir/hdfs/HdfsClient.cpp.s
.PHONY : hdfs/HdfsClient.cpp.s

hdfs/HdfsFile.o: hdfs/HdfsFile.cpp.o

.PHONY : hdfs/HdfsFile.o

# target to build an object file
hdfs/HdfsFile.cpp.o:
	$(MAKE) -f CMakeFiles/hsg.dir/build.make CMakeFiles/hsg.dir/hdfs/HdfsFile.cpp.o
.PHONY : hdfs/HdfsFile.cpp.o

hdfs/HdfsFile.i: hdfs/HdfsFile.cpp.i

.PHONY : hdfs/HdfsFile.i

# target to preprocess a source file
hdfs/HdfsFile.cpp.i:
	$(MAKE) -f CMakeFiles/hsg.dir/build.make CMakeFiles/hsg.dir/hdfs/HdfsFile.cpp.i
.PHONY : hdfs/HdfsFile.cpp.i

hdfs/HdfsFile.s: hdfs/HdfsFile.cpp.s

.PHONY : hdfs/HdfsFile.s

# target to generate assembly for a file
hdfs/HdfsFile.cpp.s:
	$(MAKE) -f CMakeFiles/hsg.dir/build.make CMakeFiles/hsg.dir/hdfs/HdfsFile.cpp.s
.PHONY : hdfs/HdfsFile.cpp.s

hdfs/NameNode.o: hdfs/NameNode.cpp.o

.PHONY : hdfs/NameNode.o

# target to build an object file
hdfs/NameNode.cpp.o:
	$(MAKE) -f CMakeFiles/hsg.dir/build.make CMakeFiles/hsg.dir/hdfs/NameNode.cpp.o
.PHONY : hdfs/NameNode.cpp.o

hdfs/NameNode.i: hdfs/NameNode.cpp.i

.PHONY : hdfs/NameNode.i

# target to preprocess a source file
hdfs/NameNode.cpp.i:
	$(MAKE) -f CMakeFiles/hsg.dir/build.make CMakeFiles/hsg.dir/hdfs/NameNode.cpp.i
.PHONY : hdfs/NameNode.cpp.i

hdfs/NameNode.s: hdfs/NameNode.cpp.s

.PHONY : hdfs/NameNode.s

# target to generate assembly for a file
hdfs/NameNode.cpp.s:
	$(MAKE) -f CMakeFiles/hsg.dir/build.make CMakeFiles/hsg.dir/hdfs/NameNode.cpp.s
.PHONY : hdfs/NameNode.cpp.s

json/jsoncpp.o: json/jsoncpp.cpp.o

.PHONY : json/jsoncpp.o

# target to build an object file
json/jsoncpp.cpp.o:
	$(MAKE) -f CMakeFiles/hsg.dir/build.make CMakeFiles/hsg.dir/json/jsoncpp.cpp.o
.PHONY : json/jsoncpp.cpp.o

json/jsoncpp.i: json/jsoncpp.cpp.i

.PHONY : json/jsoncpp.i

# target to preprocess a source file
json/jsoncpp.cpp.i:
	$(MAKE) -f CMakeFiles/hsg.dir/build.make CMakeFiles/hsg.dir/json/jsoncpp.cpp.i
.PHONY : json/jsoncpp.cpp.i

json/jsoncpp.s: json/jsoncpp.cpp.s

.PHONY : json/jsoncpp.s

# target to generate assembly for a file
json/jsoncpp.cpp.s:
	$(MAKE) -f CMakeFiles/hsg.dir/build.make CMakeFiles/hsg.dir/json/jsoncpp.cpp.s
.PHONY : json/jsoncpp.cpp.s

mapreduce/AppMaster.o: mapreduce/AppMaster.cpp.o

.PHONY : mapreduce/AppMaster.o

# target to build an object file
mapreduce/AppMaster.cpp.o:
	$(MAKE) -f CMakeFiles/hsg.dir/build.make CMakeFiles/hsg.dir/mapreduce/AppMaster.cpp.o
.PHONY : mapreduce/AppMaster.cpp.o

mapreduce/AppMaster.i: mapreduce/AppMaster.cpp.i

.PHONY : mapreduce/AppMaster.i

# target to preprocess a source file
mapreduce/AppMaster.cpp.i:
	$(MAKE) -f CMakeFiles/hsg.dir/build.make CMakeFiles/hsg.dir/mapreduce/AppMaster.cpp.i
.PHONY : mapreduce/AppMaster.cpp.i

mapreduce/AppMaster.s: mapreduce/AppMaster.cpp.s

.PHONY : mapreduce/AppMaster.s

# target to generate assembly for a file
mapreduce/AppMaster.cpp.s:
	$(MAKE) -f CMakeFiles/hsg.dir/build.make CMakeFiles/hsg.dir/mapreduce/AppMaster.cpp.s
.PHONY : mapreduce/AppMaster.cpp.s

mapreduce/AsyncWriter.o: mapreduce/AsyncWriter.cpp.o

.PHONY : mapreduce/AsyncWriter.o

# target to build an object file
mapreduce/AsyncWriter.cpp.o:
	$(MAKE) -f CMakeFiles/hsg.dir/build.make CMakeFiles/hsg.dir/mapreduce/AsyncWriter.cpp.o
.PHONY : mapreduce/AsyncWriter.cpp.o

mapreduce/AsyncWriter.i: mapreduce/AsyncWriter.cpp.i

.PHONY : mapreduce/AsyncWriter.i

# target to preprocess a source file
mapreduce/AsyncWriter.cpp.i:
	$(MAKE) -f CMakeFiles/hsg.dir/build.make CMakeFiles/hsg.dir/mapreduce/AsyncWriter.cpp.i
.PHONY : mapreduce/AsyncWriter.cpp.i

mapreduce/AsyncWriter.s: mapreduce/AsyncWriter.cpp.s

.PHONY : mapreduce/AsyncWriter.s

# target to generate assembly for a file
mapreduce/AsyncWriter.cpp.s:
	$(MAKE) -f CMakeFiles/hsg.dir/build.make CMakeFiles/hsg.dir/mapreduce/AsyncWriter.cpp.s
.PHONY : mapreduce/AsyncWriter.cpp.s

mapreduce/Combiner.o: mapreduce/Combiner.cpp.o

.PHONY : mapreduce/Combiner.o

# target to build an object file
mapreduce/Combiner.cpp.o:
	$(MAKE) -f CMakeFiles/hsg.dir/build.make CMakeFiles/hsg.dir/mapreduce/Combiner.cpp.o
.PHONY : mapreduce/Combiner.cpp.o

mapreduce/Combiner.i: mapreduce/Combiner.cpp.i

.PHONY : mapreduce/Combiner.i

# target to preprocess a source file
mapreduce/Combiner.cpp.i:
	$(MAKE) -f CMakeFiles/hsg.dir/build.make CMakeFiles/hsg.dir/mapreduce/Combiner.cpp.i
.PHONY : mapreduce/Combiner.cpp.i

mapreduce/Combiner.s: mapreduce/Combiner.cpp.s

.PHONY : mapreduce/Combiner.s

# target to generate assembly for a file
mapreduce/Combiner.cpp.s:
	$(MAKE) -f CMakeFiles/hsg.dir/build.make CMakeFiles/hsg.dir/mapreduce/Combiner.cpp.s
.PHONY : mapreduce/Combiner.cpp.s

mapreduce/Copier.o: mapreduce/Copier.cpp.o

.PHONY : mapreduce/Copier.o

# target to build an object file
mapreduce/Copier.cpp.o:
	$(MAKE) -f CMakeFiles/hsg.dir/build.make CMakeFiles/hsg.dir/mapreduce/Copier.cpp.o
.PHONY : mapreduce/Copier.cpp.o

mapreduce/Copier.i: mapreduce/Copier.cpp.i

.PHONY : mapreduce/Copier.i

# target to preprocess a source file
mapreduce/Copier.cpp.i:
	$(MAKE) -f CMakeFiles/hsg.dir/build.make CMakeFiles/hsg.dir/mapreduce/Copier.cpp.i
.PHONY : mapreduce/Copier.cpp.i

mapreduce/Copier.s: mapreduce/Copier.cpp.s

.PHONY : mapreduce/Copier.s

# target to generate assembly for a file
mapreduce/Copier.cpp.s:
	$(MAKE) -f CMakeFiles/hsg.dir/build.make CMakeFiles/hsg.dir/mapreduce/Copier.cpp.s
.PHONY : mapreduce/Copier.cpp.s

mapreduce/Counter.o: mapreduce/Counter.cpp.o

.PHONY : mapreduce/Counter.o

# target to build an object file
mapreduce/Counter.cpp.o:
	$(MAKE) -f CMakeFiles/hsg.dir/build.make CMakeFiles/hsg.dir/mapreduce/Counter.cpp.o
.PHONY : mapreduce/Counter.cpp.o

mapreduce/Counter.i: mapreduce/Counter.cpp.i

.PHONY : mapreduce/Counter.i

# target to preprocess a source file
mapreduce/Counter.cpp.i:
	$(MAKE) -f CMakeFiles/hsg.dir/build.make CMakeFiles/hsg.dir/mapreduce/Counter.cpp.i
.PHONY : mapreduce/Counter.cpp.i

mapreduce/Counter.s: mapreduce/Counter.cpp.s

.PHONY : mapreduce/Counter.s

# target to generate assembly for a file
mapreduce/Counter.cpp.s:
	$(MAKE) -f CMakeFiles/hsg.dir/build.make CMakeFiles/hsg.dir/mapreduce/Counter.cpp.s
.PHONY : mapreduce/Counter.cpp.s

mapreduce/JobInfo.o: mapreduce/JobInfo.cpp.o

.PHONY : mapreduce/JobInfo.o

# target to build an object file
mapreduce/JobInfo.cpp.o:
	$(MAKE) -f CMakeFiles/hsg.dir/build.make CMakeFiles/hsg.dir/mapreduce/JobInfo.cpp.o
.PHONY : mapreduce/JobInfo.cpp.o

mapreduce/JobInfo.i: mapreduce/JobInfo.cpp.i

.PHONY : mapreduce/JobInfo.i

# target to preprocess a source file
mapreduce/JobInfo.cpp.i:
	$(MAKE) -f CMakeFiles/hsg.dir/build.make CMakeFiles/hsg.dir/mapreduce/JobInfo.cpp.i
.PHONY : mapreduce/JobInfo.cpp.i

mapreduce/JobInfo.s: mapreduce/JobInfo.cpp.s

.PHONY : mapreduce/JobInfo.s

# target to generate assembly for a file
mapreduce/JobInfo.cpp.s:
	$(MAKE) -f CMakeFiles/hsg.dir/build.make CMakeFiles/hsg.dir/mapreduce/JobInfo.cpp.s
.PHONY : mapreduce/JobInfo.cpp.s

mapreduce/JsonJob.o: mapreduce/JsonJob.cpp.o

.PHONY : mapreduce/JsonJob.o

# target to build an object file
mapreduce/JsonJob.cpp.o:
	$(MAKE) -f CMakeFiles/hsg.dir/build.make CMakeFiles/hsg.dir/mapreduce/JsonJob.cpp.o
.PHONY : mapreduce/JsonJob.cpp.o

mapreduce/JsonJob.i: mapreduce/JsonJob.cpp.i

.PHONY : mapreduce/JsonJob.i

# target to preprocess a source file
mapreduce/JsonJob.cpp.i:
	$(MAKE) -f CMakeFiles/hsg.dir/build.make CMakeFiles/hsg.dir/mapreduce/JsonJob.cpp.i
.PHONY : mapreduce/JsonJob.cpp.i

mapreduce/JsonJob.s: mapreduce/JsonJob.cpp.s

.PHONY : mapreduce/JsonJob.s

# target to generate assembly for a file
mapreduce/JsonJob.cpp.s:
	$(MAKE) -f CMakeFiles/hsg.dir/build.make CMakeFiles/hsg.dir/mapreduce/JsonJob.cpp.s
.PHONY : mapreduce/JsonJob.cpp.s

mapreduce/MRClient.o: mapreduce/MRClient.cpp.o

.PHONY : mapreduce/MRClient.o

# target to build an object file
mapreduce/MRClient.cpp.o:
	$(MAKE) -f CMakeFiles/hsg.dir/build.make CMakeFiles/hsg.dir/mapreduce/MRClient.cpp.o
.PHONY : mapreduce/MRClient.cpp.o

mapreduce/MRClient.i: mapreduce/MRClient.cpp.i

.PHONY : mapreduce/MRClient.i

# target to preprocess a source file
mapreduce/MRClient.cpp.i:
	$(MAKE) -f CMakeFiles/hsg.dir/build.make CMakeFiles/hsg.dir/mapreduce/MRClient.cpp.i
.PHONY : mapreduce/MRClient.cpp.i

mapreduce/MRClient.s: mapreduce/MRClient.cpp.s

.PHONY : mapreduce/MRClient.s

# target to generate assembly for a file
mapreduce/MRClient.cpp.s:
	$(MAKE) -f CMakeFiles/hsg.dir/build.make CMakeFiles/hsg.dir/mapreduce/MRClient.cpp.s
.PHONY : mapreduce/MRClient.cpp.s

mapreduce/Mapper.o: mapreduce/Mapper.cpp.o

.PHONY : mapreduce/Mapper.o

# target to build an object file
mapreduce/Mapper.cpp.o:
	$(MAKE) -f CMakeFiles/hsg.dir/build.make CMakeFiles/hsg.dir/mapreduce/Mapper.cpp.o
.PHONY : mapreduce/Mapper.cpp.o

mapreduce/Mapper.i: mapreduce/Mapper.cpp.i

.PHONY : mapreduce/Mapper.i

# target to preprocess a source file
mapreduce/Mapper.cpp.i:
	$(MAKE) -f CMakeFiles/hsg.dir/build.make CMakeFiles/hsg.dir/mapreduce/Mapper.cpp.i
.PHONY : mapreduce/Mapper.cpp.i

mapreduce/Mapper.s: mapreduce/Mapper.cpp.s

.PHONY : mapreduce/Mapper.s

# target to generate assembly for a file
mapreduce/Mapper.cpp.s:
	$(MAKE) -f CMakeFiles/hsg.dir/build.make CMakeFiles/hsg.dir/mapreduce/Mapper.cpp.s
.PHONY : mapreduce/Mapper.cpp.s

mapreduce/Merger.o: mapreduce/Merger.cpp.o

.PHONY : mapreduce/Merger.o

# target to build an object file
mapreduce/Merger.cpp.o:
	$(MAKE) -f CMakeFiles/hsg.dir/build.make CMakeFiles/hsg.dir/mapreduce/Merger.cpp.o
.PHONY : mapreduce/Merger.cpp.o

mapreduce/Merger.i: mapreduce/Merger.cpp.i

.PHONY : mapreduce/Merger.i

# target to preprocess a source file
mapreduce/Merger.cpp.i:
	$(MAKE) -f CMakeFiles/hsg.dir/build.make CMakeFiles/hsg.dir/mapreduce/Merger.cpp.i
.PHONY : mapreduce/Merger.cpp.i

mapreduce/Merger.s: mapreduce/Merger.cpp.s

.PHONY : mapreduce/Merger.s

# target to generate assembly for a file
mapreduce/Merger.cpp.s:
	$(MAKE) -f CMakeFiles/hsg.dir/build.make CMakeFiles/hsg.dir/mapreduce/Merger.cpp.s
.PHONY : mapreduce/Merger.cpp.s

mapreduce/Reducer.o: mapreduce/Reducer.cpp.o

.PHONY : mapreduce/Reducer.o

# target to build an object file
mapreduce/Reducer.cpp.o:
	$(MAKE) -f CMakeFiles/hsg.dir/build.make CMakeFiles/hsg.dir/mapreduce/Reducer.cpp.o
.PHONY : mapreduce/Reducer.cpp.o

mapreduce/Reducer.i: mapreduce/Reducer.cpp.i

.PHONY : mapreduce/Reducer.i

# target to preprocess a source file
mapreduce/Reducer.cpp.i:
	$(MAKE) -f CMakeFiles/hsg.dir/build.make CMakeFiles/hsg.dir/mapreduce/Reducer.cpp.i
.PHONY : mapreduce/Reducer.cpp.i

mapreduce/Reducer.s: mapreduce/Reducer.cpp.s

.PHONY : mapreduce/Reducer.s

# target to generate assembly for a file
mapreduce/Reducer.cpp.s:
	$(MAKE) -f CMakeFiles/hsg.dir/build.make CMakeFiles/hsg.dir/mapreduce/Reducer.cpp.s
.PHONY : mapreduce/Reducer.cpp.s

messages/Message.o: messages/Message.cpp.o

.PHONY : messages/Message.o

# target to build an object file
messages/Message.cpp.o:
	$(MAKE) -f CMakeFiles/hsg.dir/build.make CMakeFiles/hsg.dir/messages/Message.cpp.o
.PHONY : messages/Message.cpp.o

messages/Message.i: messages/Message.cpp.i

.PHONY : messages/Message.i

# target to preprocess a source file
messages/Message.cpp.i:
	$(MAKE) -f CMakeFiles/hsg.dir/build.make CMakeFiles/hsg.dir/messages/Message.cpp.i
.PHONY : messages/Message.cpp.i

messages/Message.s: messages/Message.cpp.s

.PHONY : messages/Message.s

# target to generate assembly for a file
messages/Message.cpp.s:
	$(MAKE) -f CMakeFiles/hsg.dir/build.make CMakeFiles/hsg.dir/messages/Message.cpp.s
.PHONY : messages/Message.cpp.s

resources/JsonPlatform.o: resources/JsonPlatform.cpp.o

.PHONY : resources/JsonPlatform.o

# target to build an object file
resources/JsonPlatform.cpp.o:
	$(MAKE) -f CMakeFiles/hsg.dir/build.make CMakeFiles/hsg.dir/resources/JsonPlatform.cpp.o
.PHONY : resources/JsonPlatform.cpp.o

resources/JsonPlatform.i: resources/JsonPlatform.cpp.i

.PHONY : resources/JsonPlatform.i

# target to preprocess a source file
resources/JsonPlatform.cpp.i:
	$(MAKE) -f CMakeFiles/hsg.dir/build.make CMakeFiles/hsg.dir/resources/JsonPlatform.cpp.i
.PHONY : resources/JsonPlatform.cpp.i

resources/JsonPlatform.s: resources/JsonPlatform.cpp.s

.PHONY : resources/JsonPlatform.s

# target to generate assembly for a file
resources/JsonPlatform.cpp.s:
	$(MAKE) -f CMakeFiles/hsg.dir/build.make CMakeFiles/hsg.dir/resources/JsonPlatform.cpp.s
.PHONY : resources/JsonPlatform.cpp.s

yarn/Capacity.o: yarn/Capacity.cpp.o

.PHONY : yarn/Capacity.o

# target to build an object file
yarn/Capacity.cpp.o:
	$(MAKE) -f CMakeFiles/hsg.dir/build.make CMakeFiles/hsg.dir/yarn/Capacity.cpp.o
.PHONY : yarn/Capacity.cpp.o

yarn/Capacity.i: yarn/Capacity.cpp.i

.PHONY : yarn/Capacity.i

# target to preprocess a source file
yarn/Capacity.cpp.i:
	$(MAKE) -f CMakeFiles/hsg.dir/build.make CMakeFiles/hsg.dir/yarn/Capacity.cpp.i
.PHONY : yarn/Capacity.cpp.i

yarn/Capacity.s: yarn/Capacity.cpp.s

.PHONY : yarn/Capacity.s

# target to generate assembly for a file
yarn/Capacity.cpp.s:
	$(MAKE) -f CMakeFiles/hsg.dir/build.make CMakeFiles/hsg.dir/yarn/Capacity.cpp.s
.PHONY : yarn/Capacity.cpp.s

yarn/CapacityScheduler.o: yarn/CapacityScheduler.cpp.o

.PHONY : yarn/CapacityScheduler.o

# target to build an object file
yarn/CapacityScheduler.cpp.o:
	$(MAKE) -f CMakeFiles/hsg.dir/build.make CMakeFiles/hsg.dir/yarn/CapacityScheduler.cpp.o
.PHONY : yarn/CapacityScheduler.cpp.o

yarn/CapacityScheduler.i: yarn/CapacityScheduler.cpp.i

.PHONY : yarn/CapacityScheduler.i

# target to preprocess a source file
yarn/CapacityScheduler.cpp.i:
	$(MAKE) -f CMakeFiles/hsg.dir/build.make CMakeFiles/hsg.dir/yarn/CapacityScheduler.cpp.i
.PHONY : yarn/CapacityScheduler.cpp.i

yarn/CapacityScheduler.s: yarn/CapacityScheduler.cpp.s

.PHONY : yarn/CapacityScheduler.s

# target to generate assembly for a file
yarn/CapacityScheduler.cpp.s:
	$(MAKE) -f CMakeFiles/hsg.dir/build.make CMakeFiles/hsg.dir/yarn/CapacityScheduler.cpp.s
.PHONY : yarn/CapacityScheduler.cpp.s

yarn/FIFOScheduler.o: yarn/FIFOScheduler.cpp.o

.PHONY : yarn/FIFOScheduler.o

# target to build an object file
yarn/FIFOScheduler.cpp.o:
	$(MAKE) -f CMakeFiles/hsg.dir/build.make CMakeFiles/hsg.dir/yarn/FIFOScheduler.cpp.o
.PHONY : yarn/FIFOScheduler.cpp.o

yarn/FIFOScheduler.i: yarn/FIFOScheduler.cpp.i

.PHONY : yarn/FIFOScheduler.i

# target to preprocess a source file
yarn/FIFOScheduler.cpp.i:
	$(MAKE) -f CMakeFiles/hsg.dir/build.make CMakeFiles/hsg.dir/yarn/FIFOScheduler.cpp.i
.PHONY : yarn/FIFOScheduler.cpp.i

yarn/FIFOScheduler.s: yarn/FIFOScheduler.cpp.s

.PHONY : yarn/FIFOScheduler.s

# target to generate assembly for a file
yarn/FIFOScheduler.cpp.s:
	$(MAKE) -f CMakeFiles/hsg.dir/build.make CMakeFiles/hsg.dir/yarn/FIFOScheduler.cpp.s
.PHONY : yarn/FIFOScheduler.cpp.s

yarn/FairScheduler.o: yarn/FairScheduler.cpp.o

.PHONY : yarn/FairScheduler.o

# target to build an object file
yarn/FairScheduler.cpp.o:
	$(MAKE) -f CMakeFiles/hsg.dir/build.make CMakeFiles/hsg.dir/yarn/FairScheduler.cpp.o
.PHONY : yarn/FairScheduler.cpp.o

yarn/FairScheduler.i: yarn/FairScheduler.cpp.i

.PHONY : yarn/FairScheduler.i

# target to preprocess a source file
yarn/FairScheduler.cpp.i:
	$(MAKE) -f CMakeFiles/hsg.dir/build.make CMakeFiles/hsg.dir/yarn/FairScheduler.cpp.i
.PHONY : yarn/FairScheduler.cpp.i

yarn/FairScheduler.s: yarn/FairScheduler.cpp.s

.PHONY : yarn/FairScheduler.s

# target to generate assembly for a file
yarn/FairScheduler.cpp.s:
	$(MAKE) -f CMakeFiles/hsg.dir/build.make CMakeFiles/hsg.dir/yarn/FairScheduler.cpp.s
.PHONY : yarn/FairScheduler.cpp.s

yarn/HddMediator.o: yarn/HddMediator.cpp.o

.PHONY : yarn/HddMediator.o

# target to build an object file
yarn/HddMediator.cpp.o:
	$(MAKE) -f CMakeFiles/hsg.dir/build.make CMakeFiles/hsg.dir/yarn/HddMediator.cpp.o
.PHONY : yarn/HddMediator.cpp.o

yarn/HddMediator.i: yarn/HddMediator.cpp.i

.PHONY : yarn/HddMediator.i

# target to preprocess a source file
yarn/HddMediator.cpp.i:
	$(MAKE) -f CMakeFiles/hsg.dir/build.make CMakeFiles/hsg.dir/yarn/HddMediator.cpp.i
.PHONY : yarn/HddMediator.cpp.i

yarn/HddMediator.s: yarn/HddMediator.cpp.s

.PHONY : yarn/HddMediator.s

# target to generate assembly for a file
yarn/HddMediator.cpp.s:
	$(MAKE) -f CMakeFiles/hsg.dir/build.make CMakeFiles/hsg.dir/yarn/HddMediator.cpp.s
.PHONY : yarn/HddMediator.cpp.s

yarn/HeartBeater.o: yarn/HeartBeater.cpp.o

.PHONY : yarn/HeartBeater.o

# target to build an object file
yarn/HeartBeater.cpp.o:
	$(MAKE) -f CMakeFiles/hsg.dir/build.make CMakeFiles/hsg.dir/yarn/HeartBeater.cpp.o
.PHONY : yarn/HeartBeater.cpp.o

yarn/HeartBeater.i: yarn/HeartBeater.cpp.i

.PHONY : yarn/HeartBeater.i

# target to preprocess a source file
yarn/HeartBeater.cpp.i:
	$(MAKE) -f CMakeFiles/hsg.dir/build.make CMakeFiles/hsg.dir/yarn/HeartBeater.cpp.i
.PHONY : yarn/HeartBeater.cpp.i

yarn/HeartBeater.s: yarn/HeartBeater.cpp.s

.PHONY : yarn/HeartBeater.s

# target to generate assembly for a file
yarn/HeartBeater.cpp.s:
	$(MAKE) -f CMakeFiles/hsg.dir/build.make CMakeFiles/hsg.dir/yarn/HeartBeater.cpp.s
.PHONY : yarn/HeartBeater.cpp.s

yarn/NodeManager.o: yarn/NodeManager.cpp.o

.PHONY : yarn/NodeManager.o

# target to build an object file
yarn/NodeManager.cpp.o:
	$(MAKE) -f CMakeFiles/hsg.dir/build.make CMakeFiles/hsg.dir/yarn/NodeManager.cpp.o
.PHONY : yarn/NodeManager.cpp.o

yarn/NodeManager.i: yarn/NodeManager.cpp.i

.PHONY : yarn/NodeManager.i

# target to preprocess a source file
yarn/NodeManager.cpp.i:
	$(MAKE) -f CMakeFiles/hsg.dir/build.make CMakeFiles/hsg.dir/yarn/NodeManager.cpp.i
.PHONY : yarn/NodeManager.cpp.i

yarn/NodeManager.s: yarn/NodeManager.cpp.s

.PHONY : yarn/NodeManager.s

# target to generate assembly for a file
yarn/NodeManager.cpp.s:
	$(MAKE) -f CMakeFiles/hsg.dir/build.make CMakeFiles/hsg.dir/yarn/NodeManager.cpp.s
.PHONY : yarn/NodeManager.cpp.s

yarn/ResourceManager.o: yarn/ResourceManager.cpp.o

.PHONY : yarn/ResourceManager.o

# target to build an object file
yarn/ResourceManager.cpp.o:
	$(MAKE) -f CMakeFiles/hsg.dir/build.make CMakeFiles/hsg.dir/yarn/ResourceManager.cpp.o
.PHONY : yarn/ResourceManager.cpp.o

yarn/ResourceManager.i: yarn/ResourceManager.cpp.i

.PHONY : yarn/ResourceManager.i

# target to preprocess a source file
yarn/ResourceManager.cpp.i:
	$(MAKE) -f CMakeFiles/hsg.dir/build.make CMakeFiles/hsg.dir/yarn/ResourceManager.cpp.i
.PHONY : yarn/ResourceManager.cpp.i

yarn/ResourceManager.s: yarn/ResourceManager.cpp.s

.PHONY : yarn/ResourceManager.s

# target to generate assembly for a file
yarn/ResourceManager.cpp.s:
	$(MAKE) -f CMakeFiles/hsg.dir/build.make CMakeFiles/hsg.dir/yarn/ResourceManager.cpp.s
.PHONY : yarn/ResourceManager.cpp.s

yarn/YarnSchedulerBase.o: yarn/YarnSchedulerBase.cpp.o

.PHONY : yarn/YarnSchedulerBase.o

# target to build an object file
yarn/YarnSchedulerBase.cpp.o:
	$(MAKE) -f CMakeFiles/hsg.dir/build.make CMakeFiles/hsg.dir/yarn/YarnSchedulerBase.cpp.o
.PHONY : yarn/YarnSchedulerBase.cpp.o

yarn/YarnSchedulerBase.i: yarn/YarnSchedulerBase.cpp.i

.PHONY : yarn/YarnSchedulerBase.i

# target to preprocess a source file
yarn/YarnSchedulerBase.cpp.i:
	$(MAKE) -f CMakeFiles/hsg.dir/build.make CMakeFiles/hsg.dir/yarn/YarnSchedulerBase.cpp.i
.PHONY : yarn/YarnSchedulerBase.cpp.i

yarn/YarnSchedulerBase.s: yarn/YarnSchedulerBase.cpp.s

.PHONY : yarn/YarnSchedulerBase.s

# target to generate assembly for a file
yarn/YarnSchedulerBase.cpp.s:
	$(MAKE) -f CMakeFiles/hsg.dir/build.make CMakeFiles/hsg.dir/yarn/YarnSchedulerBase.cpp.s
.PHONY : yarn/YarnSchedulerBase.cpp.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... rebuild_cache"
	@echo "... edit_cache"
	@echo "... hsg"
	@echo "... Main.o"
	@echo "... Main.i"
	@echo "... Main.s"
	@echo "... distributions/RandClass.o"
	@echo "... distributions/RandClass.i"
	@echo "... distributions/RandClass.s"
	@echo "... hdfs/Chunk.o"
	@echo "... hdfs/Chunk.i"
	@echo "... hdfs/Chunk.s"
	@echo "... hdfs/Client.o"
	@echo "... hdfs/Client.i"
	@echo "... hdfs/Client.s"
	@echo "... hdfs/DataNode.o"
	@echo "... hdfs/DataNode.i"
	@echo "... hdfs/DataNode.s"
	@echo "... hdfs/DirFiles.o"
	@echo "... hdfs/DirFiles.i"
	@echo "... hdfs/DirFiles.s"
	@echo "... hdfs/Hdd.o"
	@echo "... hdfs/Hdd.i"
	@echo "... hdfs/Hdd.s"
	@echo "... hdfs/HdfsClient.o"
	@echo "... hdfs/HdfsClient.i"
	@echo "... hdfs/HdfsClient.s"
	@echo "... hdfs/HdfsFile.o"
	@echo "... hdfs/HdfsFile.i"
	@echo "... hdfs/HdfsFile.s"
	@echo "... hdfs/NameNode.o"
	@echo "... hdfs/NameNode.i"
	@echo "... hdfs/NameNode.s"
	@echo "... json/jsoncpp.o"
	@echo "... json/jsoncpp.i"
	@echo "... json/jsoncpp.s"
	@echo "... mapreduce/AppMaster.o"
	@echo "... mapreduce/AppMaster.i"
	@echo "... mapreduce/AppMaster.s"
	@echo "... mapreduce/AsyncWriter.o"
	@echo "... mapreduce/AsyncWriter.i"
	@echo "... mapreduce/AsyncWriter.s"
	@echo "... mapreduce/Combiner.o"
	@echo "... mapreduce/Combiner.i"
	@echo "... mapreduce/Combiner.s"
	@echo "... mapreduce/Copier.o"
	@echo "... mapreduce/Copier.i"
	@echo "... mapreduce/Copier.s"
	@echo "... mapreduce/Counter.o"
	@echo "... mapreduce/Counter.i"
	@echo "... mapreduce/Counter.s"
	@echo "... mapreduce/JobInfo.o"
	@echo "... mapreduce/JobInfo.i"
	@echo "... mapreduce/JobInfo.s"
	@echo "... mapreduce/JsonJob.o"
	@echo "... mapreduce/JsonJob.i"
	@echo "... mapreduce/JsonJob.s"
	@echo "... mapreduce/MRClient.o"
	@echo "... mapreduce/MRClient.i"
	@echo "... mapreduce/MRClient.s"
	@echo "... mapreduce/Mapper.o"
	@echo "... mapreduce/Mapper.i"
	@echo "... mapreduce/Mapper.s"
	@echo "... mapreduce/Merger.o"
	@echo "... mapreduce/Merger.i"
	@echo "... mapreduce/Merger.s"
	@echo "... mapreduce/Reducer.o"
	@echo "... mapreduce/Reducer.i"
	@echo "... mapreduce/Reducer.s"
	@echo "... messages/Message.o"
	@echo "... messages/Message.i"
	@echo "... messages/Message.s"
	@echo "... resources/JsonPlatform.o"
	@echo "... resources/JsonPlatform.i"
	@echo "... resources/JsonPlatform.s"
	@echo "... yarn/Capacity.o"
	@echo "... yarn/Capacity.i"
	@echo "... yarn/Capacity.s"
	@echo "... yarn/CapacityScheduler.o"
	@echo "... yarn/CapacityScheduler.i"
	@echo "... yarn/CapacityScheduler.s"
	@echo "... yarn/FIFOScheduler.o"
	@echo "... yarn/FIFOScheduler.i"
	@echo "... yarn/FIFOScheduler.s"
	@echo "... yarn/FairScheduler.o"
	@echo "... yarn/FairScheduler.i"
	@echo "... yarn/FairScheduler.s"
	@echo "... yarn/HddMediator.o"
	@echo "... yarn/HddMediator.i"
	@echo "... yarn/HddMediator.s"
	@echo "... yarn/HeartBeater.o"
	@echo "... yarn/HeartBeater.i"
	@echo "... yarn/HeartBeater.s"
	@echo "... yarn/NodeManager.o"
	@echo "... yarn/NodeManager.i"
	@echo "... yarn/NodeManager.s"
	@echo "... yarn/ResourceManager.o"
	@echo "... yarn/ResourceManager.i"
	@echo "... yarn/ResourceManager.s"
	@echo "... yarn/YarnSchedulerBase.o"
	@echo "... yarn/YarnSchedulerBase.i"
	@echo "... yarn/YarnSchedulerBase.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

