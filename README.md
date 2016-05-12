# Build and Run:

1. `$ sudo apt-get install libqt5webkit5-dev libqt5opengl5-dev`
2. `$ mkdir bin`
3. `$ cd bin`
4. `$ qmake ../qtwebkit.pro`
5. `$ make`
6. `$ ln -s ../html/a.html a.html`
7. `$ ln -s ../html/b.html b.html`
7. `$ ./qtwebkit`

# DBus Test

`$ qdbus qtwebkit.demo.dbus /qtwebkit/demo/object qtwebkit.demo.interface.event_callback 123 "hello, world"`
