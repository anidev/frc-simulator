#! /bin/sh

protoc --cpp_out=cpp-gen/ --java_out=java-gen/ *.proto
