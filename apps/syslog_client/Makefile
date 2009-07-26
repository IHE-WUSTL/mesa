include $(MESA_MAKE)

CFLAGS = $(C_OPTS)
CXX_FLAGS = $(C_OPTS)
L_FLAGS = $(L_OPTS)

APPS = syslog_client

app:	$(APPS)

syslog_client:	syslog_client.o
	$(CXX) -o syslog_client syslog_client.o $(L_FLAGS) -lsyslog $(LIBS_MESA)

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

nextgen2:	syslog_client
	./syslog_client -f 5 -s 4 nextgen2 514 x1.xml
