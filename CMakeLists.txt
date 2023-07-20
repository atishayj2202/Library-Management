cmake_minimum_required(VERSION 3.25)
project(Library_Management)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Library_Management main.cpp book_issue.h book.h student.h book_status.h student_status.h Student_Menu.h Admin_Menu.h)
