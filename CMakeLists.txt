cmake_minimum_required(VERSION 3.24.2)
project(ElectricScooterRentalApp)

set(CMAKE_CXX_STANDARD 20)

include_directories(.)

add_executable(ElectricScooterRentalApp
        Controller.cpp
        Controller.h
        ElectricScooter.cpp
        ElectricScooter.h
        App.cpp UI.cpp Repository.cpp Operator.cpp Operator.h Tests.cpp Tests.h Qt.cpp)