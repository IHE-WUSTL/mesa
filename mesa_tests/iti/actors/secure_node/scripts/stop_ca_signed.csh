#!/bin/csh

set LOGLEVEL = 4

if ($1 != "") set LOGLEVEL = $1

set C = $MESA_TARGET/runtime/certs-ca-signed/test_sys_1.cert.pem
set K = $MESA_TARGET/runtime/certs-ca-signed/test_sys_1.key.pem
set P = $MESA_TARGET/runtime/certs-ca-signed/mesa_list.cert
set R = $MESA_TARGET/runtime/certs-ca-signed/randoms.dat

$MESA_TARGET/bin/syslog_client -c -r 5424 -x 5426 localhost 4001 "<SHUTDOWN/>"

$MESA_TARGET/bin/syslog_client -c -r 5424 -x TCP  localhost 4002 "<SHUTDOWN/>"

$MESA_TARGET/bin/syslog_client_secure -c -r 5424 -x 5425 -C $C -K $K -P $P -R $R localhost 4003 "<SHUTDOWN/>"


# Order Placer
$MESA_TARGET/bin/kill_hl7_secure -C $C -K $K -P $P -R $R localhost 2101

# Order Filler
$MESA_TARGET/bin/kill_hl7_secure -C $C -K $K -P $P -R $R localhost 2201
$MESA_TARGET/bin/open_assoc_secure -C $C -K $K -P $P -R $R -s 0 -x 1.2.840.113654.2.30.1 localhost 2251

# PD Supplier
$MESA_TARGET/bin/kill_hl7_secure -C $C -K $K -P $P -R $R localhost 3701

# PIX Manager
$MESA_TARGET/bin/kill_hl7_secure -C $C -K $K -P $P -R $R localhost 3601

