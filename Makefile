CC= g++
HEADERS_DIR= /usr/local/include/tvmonitor
LIB_DIR= /usr/local/lib
PROGS= libtvmonitor.so tunertest

INCLUDES=	\
			include/BandEntry.h \
			include/TVMonitorException.h \
			include/TVTunerInputV4L2.h \
			include/VideoInput.h \
			include/TunerSettings.h
			
SOURCES=	\
			src/BandEntry.cpp \
			src/TVMonitorException.cpp \
			src/TVTunerInputV4L2.cpp \
			src/TunerSettings.cpp
			
LIBS= 		-lcpputil

INSTALL_HEADERS = $(INCLUDES)

ALL: $(PROGS)

libtvmonitor.so: $(INCLUDES) $(SOURCES)
	$(CC) $(SOURCES) $(LIBS)\
		-shared -fPIC -o libtvmonitor.so
		
tunertest: libtvmonitor.so tunertest.cpp
	$(CC) tunertest.cpp -L. -ltvmonitor -g -o tunertest
		
		
clean:
	rm -f $(PROGS)
	
uninstall:
	rm -rf $(HEADERS_DIR)
	rm -rf $(LIB_DIR)/libtvmonitor.so
		
install: libtvmonitor.so
	install -d $(HEADERS_DIR)
	install -t $(HEADERS_DIR) $(INSTALL_HEADERS)
	install -t $(LIB_DIR) libtvmonitor.so