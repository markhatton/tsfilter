#!/bin/bash

# DISABLED PENDING SAMPLE TS diff -q <(${builddir}/tsfilter 0 600 601 602 4164 < ${srcdir}/test/testin.ts) <(${builddir}/tsfilter -a < ${srcdir}/test/testin.ts)

exit $?
