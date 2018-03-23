cellulo-svg-to-json
===================

Command line tool to extract Cellulo zones from SVG files designed in vector graphic editors, such as Inkscape.

Tested with Qt 5.10.0 on:

  - Ubuntu 17.10
  - macOS 10.13.3

Build
-----

1. Build and install [qml-cellulo](../../).
1. Run the following:

    ```
    mkdir build && cd build
    qt-install-root/qt-version/target-platform/bin/qmake ..
    make -j5 install
    ```

Run
---

```
cellulo-svg-to-json --help
```
