#!/bin/sh
doxygen
mkdir -p doc
export NODE_PATH=$NODE_PATH:/usr/local/lib/node_modules/
node -e "
    'use strict';

    var moxygen = require('moxygen');

    var options = moxygen.defaultOptions;
    options.filters.members.push('public-static-func');
    options.filters.members.push('protected-static-func');
    options.directory = 'xml/';
    options.output = 'doc/DOCUMENTATION.md';
    options.groups = false;
    options.noindex = false;
    options.anchors = false;
    options.language = 'cpp';
    options.templates = 'templates';

    moxygen.run(options);
"
