frc-simulator
=============

A simulator for running robot code from the FRC robotics competitions that works by creating a
native environment for simulating the cRIO and other hardware.

Since simulators for LabView and Java already exist in some fashion, the original goal of this
project was to create a simulator for C++ robot code. It works by compiling WPILib and your robot
code to a native executable that runs on a PC. Various libraries have to be overloaded and even
simulated, such as specific VxWorks APIs and low-level cRIO FPGA functions. The whole build system
uses CMake to build and link together the various parts.

The goal of this project is to be able to simulate C++, Java, and maybe even LabView code on a PC
without having to deploy to a robot every time. To ease developing simulators for each language,
this project will separate the robot code into a server, which simulates a robot awaiting deployment,
and the executable generated from the robot code, which will connect to server over network sockets.
This architecture has the added benefit of being able to test robot code remotely, though honestly
there isn't much use for that.

UPDATE: This project is currently on standby as I do not have time right now to continue working on it
        (though I may push updates occasionally), and also because in a few years the cRio will be obsolete
        and replaced by the new DRio. As such, I am deciding whether it is worth the time and effort
        to continue working on this cRio simulator.
