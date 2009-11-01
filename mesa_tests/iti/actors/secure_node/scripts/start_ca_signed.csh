#!/bin/csh

set LOGLEVEL = 4

if ($1 != "") set LOGLEVEL = $1

#$MESA_TARGET/bin/syslog_server -l $LOGLEVEL 4000 &

## Now, all of the secure applications

set C = $MESA_TARGET/runtime/certs-ca-signed/mesa_1.cert.pem
set K = $MESA_TARGET/runtime/certs-ca-signed/mesa_1.key.pem
set P = $MESA_TARGET/runtime/certs-ca-signed/test_list.cert
set R = $MESA_TARGET/runtime/certs-ca-signed/randoms.dat

# Secure Order Placer
if (-e $MESA_TARGET/logs/op_hl7ps_secure.log) rm -f $MESA_TARGET/logs/op_hl7ps_secure.log
$MESA_TARGET/bin/hl7_rcvr_secure -l $LOGLEVEL -M OP -C $C -K $K -P $P -R $R -a -z ordplc 2101 &


# Secure Order Filler
if (-e $MESA_TARGET/logs/of_hl7ps_secure.log) rm -f $MESA_TARGET/logs/of_hl7ps_secure.log
$MESA_TARGET/bin/hl7_rcvr_secure -l $LOGLEVEL -M OF -C $C -K $K -P $P -R $R -a -z ordfil 2201 &
$MESA_TARGET/bin/of_dcmps_secure -C $C -K $K -P $P -R $R 2251 &

# PD Supplier
rm -r $MESA_STORAGE/pd_supplier/*hl7
if (-e $MESA_TARGET/logs/pds_hl7ps_secure.log) rm -f $MESA_TARGET/logs/pds_hl7ps_secure.log
$MESA_TARGET/bin/hl7_rcvr_secure -C $C -K $K -P $P -R $R -d ihe-iti -M PDS -l $LOGLEVEL -a -z pd_supplier 3701 &

# PIX Manager
rm -r $MESA_STORAGE/xref/*hl7
if (-e $MESA_TARGET/logs/xr_hl7ps_secure.log) rm -f $MESA_TARGET/logs/pds_hl7ps_secure.log
$MESA_TARGET/bin/hl7_rcvr_secure -C $C -K $K -P $P -R $R -d ihe-iti -M XR -l $LOGLEVEL -a -z xref_mgr 3601 &

