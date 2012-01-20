#!/bin/bash

ret=0

# test -i and -o arguments
# DISABLED PENDING SAMPLE TS TEMPOUT=$(mktemp /tmp/libtstest.XXXXXX)
# DISABLED PENDING SAMPLE TS ${builddir}/tsfilter -i ${srcdir}/test/testin.ts -o ${TEMPOUT} 0 600 601 602 603 1005 4164
# DISABLED PENDING SAMPLE TS diff -q "$TEMPOUT" "${srcdir}/test/testout.ts" || ret=1
# DISABLED PENDING SAMPLE TS rm -f $TEMPOUT

exit $ret
