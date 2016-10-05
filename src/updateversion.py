#!/usr/bin/env python

import os
import time

mydir = os.path.dirname(os.path.abspath(__file__))

tmpl = r'''
#ifndef BAYE_VERSION
#define BAYE_VERSION "{version}"
#endif
'''

ts = time.strftime("%Y%m%d%H%M")
open(os.path.join(mydir, 'baye', 'version.h'), 'wb').write(tmpl.format(version=ts))

