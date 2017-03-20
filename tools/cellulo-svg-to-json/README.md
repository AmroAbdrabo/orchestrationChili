cellulo-svg-to-json
===================

Command line tool to extract Cellulo zones from SVG files designed in vector graphic editors, such as Inkscape.

Tested with Qt 5.8.0 on Ubuntu 16.04.

Build
-----

1. Build and install [qml-cellulo](../../).
1. Run the following:

    ```
    mkdir build && cd build
    /path-to-qt-install-root/5.8/gcc_64/bin/qmake ..
    make -j5 install
    ```

Run
---

```
cellulo-svg-to-json --help
```
