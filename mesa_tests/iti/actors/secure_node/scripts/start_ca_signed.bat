
set LOGLEVEL=4

set C=%MESA_TARGET%\runtime\certs-ca-signed\mesa_1.cert.pem
set K=%MESA_TARGET%\runtime\certs-ca-signed\mesa_1.key.pem
set P=%MESA_TARGET%\runtime\certs-ca-signed\test_list.cert
set R=%MESA_TARGET%\runtime\certs-ca-signed\randoms.dat

REM Secure Order Placer
delete %MESA_TARGET%\logs\op_hl7ps_secure.log
start %MESA_TARGET%\bin\hl7_rcvr_secure -l %LOGLEVEL% -M OP -C %C% -K %K% -P %P% -R %R% -a -z ordplc 2101


REM Secure Order Filler
delete %MESA_TARGET%\logs\of_hl7ps_secure.log
start %MESA_TARGET%\bin\hl7_rcvr_secure -l %LOGLEVEL% -M OF -C %C% -K %K% -P %P% -R %R% -a -z ordfil 2201
start %MESA_TARGET%\bin\of_dcmps_secure -C %C% -K %K% -P %P% -R %R% 2251

# PD Supplier
delete %MESA_TARGET%\logs\pds_hl7ps_secure.log
start %MESA_TARGET%\bin\hl7_rcvr_secure -C %C% -K %K% -P %P% -R %R% -d ihe-iti -M PDS -l %LOGLEVEL% -a -z pd_supplier 3701

# PIX Manager
delete %MESA_TARGET%\logs\pds_hl7ps_secure.log
start %MESA_TARGET%\bin\hl7_rcvr_secure -C %C% -K %K% -P %P% -R %R% -d ihe-iti -M XR -l %LOGLEVEL% -a -z xref_mgr 3601

