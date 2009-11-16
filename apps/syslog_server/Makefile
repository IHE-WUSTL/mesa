include $(MESA_MAKE)

CFLAGS = $(C_OPTS) -DRFC5425
CXX_FLAGS = $(C_OPTS) -DRFC5425
L_FLAGS = $(L_OPTS)

APPS = syslog_server

app:	$(APPS)

syslog_server:	syslog_server.o
	$(CXX) -o syslog_server syslog_server.o $(L_FLAGS) $(LIBS_MESA_SSL)

relink:
	$(CXX) -o syslog_server syslog_server.o $(L_FLAGS) $(LIBS_MESA_SSL)

install:	$(APPS)
	$(INSTALL) syslog_server $(MESA_BIN)

C = $(MESA_TARGET)/runtime/certs-ca-signed/mesa_1.cert.pem
K = $(MESA_TARGET)/runtime/certs-ca-signed/mesa_1.key.pem
P = $(MESA_TARGET)/runtime/certs-ca-signed/test_list.cert
R = $(MESA_TARGET)/runtime/certs-ca-signed/randoms.dat

clean:
	rm -rf $(APPS) core *.o *.?pp~

t1:	syslog_server
	./syslog_server 4000

t2:	syslog_server
	./syslog_server -l 4 -r 5424 4000

t102:	syslog_server
	./syslog_server -l 4 -r 5424 -x TCP 4000

t103:	syslog_server
	./syslog_server -l 4 -r 5424 -x 5425 -C $(C) -K $(K) -P $(P) -R $(R) 4000

t104:	syslog_server
	./syslog_server -l 4 -r 5424 -x 5426 4001
