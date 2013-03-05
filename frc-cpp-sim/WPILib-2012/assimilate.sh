#! /bin/sh

# copy source WPILib to here
echo "Copying WPILib source from ucpp directory..."
cp -r ~/.ucpp/gccdist/WindRiver/WPILib/source/WPILib/* ./

# convert tabs to spaces so it looks good in different editors
echo "Converting tabs to four spaces..."
sed -i -r 's/\t/    /g' `find | grep -e "\.cpp" -e "\.h"`

# remove space after word "Reserved." in copyright notice to it lines up
echo "Tidying copyright notice..."
sed -i -r 's/Reserved\. /Reserved\./' `find | grep -e "\.cpp" -e "\.h"`

# replace vxWorks.h with custom header file
#for FILE in `find | grep "\.h"`
#do
#	sed -i -r 's/#include <vxWorks.h>/#include "vxworks_compat.h"/' $FILE
#done

# gcc complains that Error::Report should be just Report (inside class Error)
echo "Fixing extra qualification on Error::Report in Error.h..."
sed -i 's/Error::Report/Report/' Error.h

# inetLib.h should become sys/socket.h, netinet/in.h, and arpa/inet.h
echo "Patching inetLib.h to the various Linux inet headers..."
sed -i 's/#include <inetLib.h>/#include <sys\/socket.h>\n#include <netinet\/in.h>\n#include <arpa\/inet.h>/' `find | grep -e "\.cpp" -e "\.h"`

# selectLib.h should become sys/select.h
echo "Patching selectLib.h to sys/select.h..."
sed -i 's/selectLib.h/sys\/select.h/' `find | grep -e "\.cpp" -e "\.h"`

# sockLib.h should become sys/socket.h
echo "Patching sockLib.h to sys/socket.h..."
sed -i 's/sockLib.h/sys\/socket.h/' `find | grep -e "\.cpp" -e "\.h"`

# not sure why (maybe the \n's) but sed adds \r's (^M in vim) to some files
echo "Converting files from dos to unix format (in case something happened)..."
dos2unix `find` > /dev/null 2>&1 

echo "All done, ready to build."
