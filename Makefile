# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

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
CMAKE_SOURCE_DIR = /home/alpha/tuturial/hsg

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/alpha/tuturial/hsg

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/usr/bin/cmake -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
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
	$(CMAKE_COMMAND) -E cmake_progress_start /home/alpha/tuturial/hsg/CMakeFiles /home/alpha/tuturial/hsg/CMakeFiles/progress.marks
	$(MAKE) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /home/alpha/tuturial/hsg/CMakeFiles 0
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
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
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

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... rebuild_cache"
	@echo "... hsg"
	@echo "... edit_cache"
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
	@echo "... hdfs/HdfsFile.o"
	@echo "... hdfs/HdfsFile.i"
	@echo "... hdfs/HdfsFile.s"
	@echo "... hdfs/NameNode.o"
	@echo "... hdfs/NameNode.i"
	@echo "... hdfs/NameNode.s"
	@echo "... messages/Message.o"
	@echo "... messages/Message.i"
	@echo "... messages/Message.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

