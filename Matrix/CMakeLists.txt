cmake_minimum_required(VERSION 3.13)
project(Matrix)

set(CMAKE_CXX_STANDARD 14)

add_executable(Matrix main.cpp Container.h Iterator.h MutableIterator.h Iterable.h Matrix.h Exceptions.h IteratorImplementation.hpp MutableIteratorImplementation.hpp MutableIterable.h ContainerImplementation.hpp MatrixImplementation.hpp ArrayDeleter.h)