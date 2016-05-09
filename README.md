Sample Boost.Asio programs.

# Get the Project

Clone:
```bash
git clone https://github.com/piribes/sample_boost_asio.git
```

# on OSX

Compile:
```bash
cd sample_boost_asio
mkdir build
cd build
cmake -GXcode ..
xcodebuild -configuration Debug
```

Run:
```bash
./sample_serial_publisher/Debug/sample_serial_publisher 50001 /dev/ttys001
```

If you prefer, you can open the Xcode project and build/develop from GUI:
```bash
cd sample_boost_asio/build
open sample_boost_asio.xcodeproj
```

# on UNIX

Compile:
```bash
mkdir build
cd build
cmake ..
make
```

Run:
```bash
./sample_serial_publisher/sample_serial_publisher 50001 /dev/ttyS001
```

