include $(MESA_MAKE)

CFLAGS = $(C_OPTS)
CXX_FLAGS = $(C_OPTS)
L_FLAGS = $(L_OPTS)

APPS = syslog_client

app:	$(APPS)

syslog_client:	syslog_client.o
	$(CXX) -g -o syslog_client syslog_client.o $(L_FLAGS) -lsyslog $(LIBS_MESA_SSL)

relink:
	$(CXX) -o syslog_client syslog_client.o $(L_FLAGS) -lsyslog $(LIBS_MESA_SSL)

C = $(MESA_TARGET)/runtime/certs-ca-signed/test_sys_1.cert.pem
K = $(MESA_TARGET)/runtime/certs-ca-signed/test_sys_1.key.pem
P = $(MESA_TARGET)/runtime/certs-ca-signed/mesa_list.cert
R = $(MESA_TARGET)/runtime/certs-ca-signed/randoms.dat

install:	$(APPS)
	$(INSTALL) syslog_client $(MESA_BIN)

clean:
	rm -rf $(APPS) core *.o

t1:	syslog_client
	./syslog_client -f 10 -s 0 localhost 4000 startup.xml

t2:	syslog_client
	./syslog_client -m 1 -f 10 -s 0 localhost 4000 startup.xml

t3:	syslog_client
	./syslog_client -m 1 -f 10 -s 0 localhost 4000 syslog.txt

t101:	syslog_client
	./syslog_client -c -r 5424 -m 1 localhost 4000 "<xml>payload</xml>"

t102:	syslog_client
	./syslog_client -c -r 5424 -x TCP -m 1 localhost 4000 "<xml>payload</xml>"

t103:	syslog_client
	./syslog_client -l 4 -C $(C) -K $(K) -P $(P) -R $(R) -c -r 5424 -x 5425 -m 1 localhost 4000 "<xml>payload</xml>"

t104:	syslog_client
	./syslog_client -c -r 5424 -x 5426 -m 1 localhost 4001 "<xml>payload</xml>"


nextgen2:	syslog_client
	./syslog_client -f 5 -s 4 nextgen2 514 x1.xml
