#!/bin/csh

set LOGLEVEL = 4

if ($1 != "") set LOGLEVEL = $1

#$MESA_TARGET/bin/syslog_server -l $LOGLEVEL 4000 &

## Now, all of the secure applications

set C = $MESA_TARGET/runtime/certificates/mesa_1.cert.pem
set K = $MESA_TARGET/runtime/certificates/mesa_1.key.pem
set P = $MESA_TARGET/runtime/certificates/test_list.cert
set R = $MESA_TARGET/runtime/certificates/randoms.dat

# Secure Order Placer
if (-e $MESA_TARGET/logs/op_hl7ps_secure.log) rm -f $MESA_TARGET/logs/op_hl7ps_secure.log
$MESA_TARGET/bin/hl7_rcvr_secure -l $LOGLEVEL -M OP -C $C -K $K -P $P -R $R -a -z ordplc 2101 &

