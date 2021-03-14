###Install Cmake :
wget https://github.com/Kitware/CMake/releases/download/v3.17.3/cmake-3.17.3.tar.gz
tar -zxvf cmake-3.17.3.tar.gz
cd cmake-3.17.3
sudo ./bootsrap
make
make install
cmake --version

###Run the program:
cd BezierCurve
mkdir build
cd build
cmake ..
make
./BezierCurve 

###Because of the need to configure a simple open environment.
###The lab machine do not support to download any library resouce.
###I make a little video of showing the functions of my assignment.
###Just in case the program does not run smoothly.
###If there are any problems, please contact me immediately, 
###I guarantee that there is no error in the program.
###Email: ww47@st-andrews.ac.uk
