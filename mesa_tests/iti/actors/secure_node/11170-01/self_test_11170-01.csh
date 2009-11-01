#!/bin/csh

set LOGLEVEL = 4

if ($1 != "") set LOGLEVEL = $1

set C = $MESA_TARGET/runtime/certs-ca-signed/test_sys_1.cert.pem
set K = $MESA_TARGET/runtime/certs-ca-signed/test_sys_1.key.pem
set P = $MESA_TARGET/runtime/certs-ca-signed/mesa_list.cert
set R = $MESA_TARGET/runtime/certs-ca-signed/randoms.dat

# PIX Manager
$MESA_TARGET/bin/send_hl7_secure -d ihe-iti -C $C -K $K -P $P -R $R localhost 3601 \
../../../iti/msgs/adt/10501/10501.102.a04.hl7

$MESA_TARGET/bin/send_hl7_secure -d ihe-iti -C $C -K $K -P $P -R $R localhost 3601 \
../../../iti/msgs/adt/10501/10501.104.a04.hl7

$MESA_TARGET/bin/send_hl7_secure -d ihe-iti -C $C -K $K -P $P -R $R localhost 3601 \
../../../iti/msgs/adt/10501/10501.106.a04.hl7

echo "Should have CHIP, RALPH and ALICE in the xref_mgr database"
psql xref_mgr < scripts/patient.sql
