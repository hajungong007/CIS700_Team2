# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

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

# The program to use to edit the cache.
CMAKE_EDIT_COMMAND = /usr/bin/ccmake

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/genesis/code/ROS/catkin_ws/src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/genesis/code/ROS/catkin_ws/build

# Utility rule file for _run_tests_sound_play_nosetests_scripts.test.

# Include the progress variables for this target.
include sound_play/CMakeFiles/_run_tests_sound_play_nosetests_scripts.test.dir/progress.make

sound_play/CMakeFiles/_run_tests_sound_play_nosetests_scripts.test:
	cd /home/genesis/code/ROS/catkin_ws/build/sound_play && ../catkin_generated/env_cached.sh /usr/bin/python /opt/ros/indigo/share/catkin/cmake/test/run_tests.py /home/genesis/code/ROS/catkin_ws/build/test_results/sound_play/nosetests-scripts.test.xml /usr/bin/cmake\ -E\ make_directory\ /home/genesis/code/ROS/catkin_ws/build/test_results/sound_play /usr/bin/nosetests-2.7\ -P\ --process-timeout=60\ --where=/home/genesis/code/ROS/catkin_ws/src/sound_play/scripts/test\ --with-xunit\ --xunit-file=/home/genesis/code/ROS/catkin_ws/build/test_results/sound_play/nosetests-scripts.test.xml

_run_tests_sound_play_nosetests_scripts.test: sound_play/CMakeFiles/_run_tests_sound_play_nosetests_scripts.test
_run_tests_sound_play_nosetests_scripts.test: sound_play/CMakeFiles/_run_tests_sound_play_nosetests_scripts.test.dir/build.make
.PHONY : _run_tests_sound_play_nosetests_scripts.test

# Rule to build all files generated by this target.
sound_play/CMakeFiles/_run_tests_sound_play_nosetests_scripts.test.dir/build: _run_tests_sound_play_nosetests_scripts.test
.PHONY : sound_play/CMakeFiles/_run_tests_sound_play_nosetests_scripts.test.dir/build

sound_play/CMakeFiles/_run_tests_sound_play_nosetests_scripts.test.dir/clean:
	cd /home/genesis/code/ROS/catkin_ws/build/sound_play && $(CMAKE_COMMAND) -P CMakeFiles/_run_tests_sound_play_nosetests_scripts.test.dir/cmake_clean.cmake
.PHONY : sound_play/CMakeFiles/_run_tests_sound_play_nosetests_scripts.test.dir/clean

sound_play/CMakeFiles/_run_tests_sound_play_nosetests_scripts.test.dir/depend:
	cd /home/genesis/code/ROS/catkin_ws/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/genesis/code/ROS/catkin_ws/src /home/genesis/code/ROS/catkin_ws/src/sound_play /home/genesis/code/ROS/catkin_ws/build /home/genesis/code/ROS/catkin_ws/build/sound_play /home/genesis/code/ROS/catkin_ws/build/sound_play/CMakeFiles/_run_tests_sound_play_nosetests_scripts.test.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : sound_play/CMakeFiles/_run_tests_sound_play_nosetests_scripts.test.dir/depend

