include $(MESA_MAKE)

CFLAGS = $(C_OPTS)
CXX_FLAGS = $(C_OPTS)
L_FLAGS = $(L_OPTS)

APPS = syslog_server

app:	$(APPS)

syslog_server:	syslog_server.o
	$(CXX) -o syslog_server syslog_server.o $(L_FLAGS) $(LIBS_MESA)

relink:
	$(CXX) -o syslog_server syslog_server.o $(L_FLAGS) $(LIBS_MESA)

install:	$(APPS)
	$(INSTALL) syslog_server $(MESA_BIN)

clean:
	rm -rf $(APPS) core *.o *.?pp~

t1:	syslog_server
	./syslog_server 4000

t2:	syslog_server
	./syslog_server -l 4 -r 5424 4000

t3:	syslog_server
	./syslog_server -l 4 -r 5424 -x TCP 4000

t4:	syslog_server
	./syslog_server -l 4 -r 5424 -x 5425 4000

t5:	syslog_server
	./syslog_server -l 4 -r 5424 -x 5426 4001
