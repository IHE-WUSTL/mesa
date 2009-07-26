include $(MESA_MAKE)

CFLAGS = $(C_OPTS)
CXX_FLAGS = $(C_OPTS)

CLASS_FILES = MAuditMessage MAuditMessageFactory MDICOMAuditMessage \
MSyslogClient MSyslogFactory MSyslogMessage \
MBeginTransferDICOMInstances

OBJS = $(CLASS_FILES:=.o)
HEADERS = $(CLASS_FILES:=.hpp)

libsyslog.a: $(OBJS) $(HEADERS)
	ar cvr libsyslog.a $(OBJS)

MAuditMessage.o: MAuditMessage.cpp MAuditMessage.hpp

MAuditMessageFactory.o: MAuditMessageFactory.cpp MAuditMessageFactory.hpp

MDICOMAuditMessage.o: MDICOMAuditMessage.cpp MDICOMAuditMessage.hpp

MSyslogClient.o: MSyslogClient.cpp MSyslogClient.hpp

MSyslogFactory.o: MSyslogFactory.cpp MSyslogFactory.hpp

MSyslogMessage.o: MSyslogMessage.cpp MSyslogMessage.hpp

# Start the audit events
MBeginTransferDICOMInstances.o: MBeginTransferDICOMInstances.cpp MBeginTransferDICOMInstances.hpp

install: libsyslog.a
	cp libsyslog.a $(MESA_LIB)
	$(INSTALLINCLUDE) $(HEADERS) $(MESA_INCLUDE)

doc:
	$(MESA_CLASS2HTML) $(HEADERS)

doc-install: doc
	cp *.html $(MESA_CLASS_DOCS)/syslog

clean:
	rm -rf Template.DB libsyslog.a $(OBJS) *.html *.?pp~

headerexport:
	$(INSTALLINCLUDE) MSyslogMessage.hpp $(MESA_INCLUDE)
