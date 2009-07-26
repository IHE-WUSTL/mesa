install:	install-english

install-baseline:
	external/ctn/apps/scripts/createdirectory include
	external/ctn/apps/scripts/createdirectory lib
	external/ctn/apps/scripts/createdirectory $(MESA_TARGET)
	external/ctn/apps/scripts/createdirectory $(MESA_TARGET)/lib
	external/ctn/apps/scripts/createdirectory $(MESA_TARGET)/bin
	external/ctn/apps/scripts/createdirectory $(MESA_TARGET)/data
	external/ctn/apps/scripts/createdirectory $(MESA_TARGET)/db
	external/ctn/apps/scripts/createdirectory $(MESA_TARGET)/db-rismall
	external/ctn/apps/scripts/createdirectory $(MESA_TARGET)/pids
	cd runtime;	make install
	cd external;	make install
	cd libsrc;	make install
	cd lib;		make install
	cd testapps;	make install
	cd apps;	make install
	cd scripts;	make install
	cd javamesa;	make install
	cd javaexternal;	make install
	cd java_apps;	make install
#	cd mesa_tests;	make install
#	cd webmesa/ris_mall; make install
	cd webmesa/mesa-iti; make install
	cd html;	make install
	cd dbscripts/pgsql;	make install
	cd dbscripts/ris_mall;	make install
	cd templates;	make install
	@echo "MESA Build Complete"

ctnlib:
	cd external/ctn/libsrc;  make -f Makefile.mesa install

install-english: install-baseline
	cd dbscripts/pgsql;	make install

install-japanese: install-baseline
	cd dbscripts/pgsql-j;	make install

install-webmesa:
	cd webmesa/ris_mall; make install

install_brief:
	external/ctn/apps/scripts/createdirectory $(MESA_TARGET)
	external/ctn/apps/scripts/createdirectory $(MESA_TARGET)/lib
	external/ctn/apps/scripts/createdirectory $(MESA_TARGET)/bin
	external/ctn/apps/scripts/createdirectory $(MESA_TARGET)/data
	external/ctn/apps/scripts/createdirectory $(MESA_TARGET)/db
	external/ctn/apps/scripts/createdirectory $(MESA_TARGET)/pids
	cd runtime;	make install
	cd external;	make install
	cd libsrc;	make install
	@echo "MESA Build Complete"

install_secure:
	cd secure_libsrc;	make install
	cd secure_apps;		make install

install_sol7:
	make install
	make install_secure
	pushd mesa_tests; make install; popd
	pushd /opt/mesa; strip bin/*; popd
	pushd /opt/mesa; tar cf /tmp/mesa_sol7.tar .; popd
	time compress -v /tmp/mesa_sol7.tar

install_rh7:
	make install
	make install_secure
	pushd mesa_tests; make install; popd
	pushd /opt/mesa; strip bin/*; popd
	pushd /opt/mesa; zip -r /tmp/mesa_rh7.zip .; popd

install_rh9:
	make install
	make install_secure
	pushd mesa_tests; make install; popd
	pushd /opt/mesa; strip bin/*; popd
	pushd /opt/mesa; zip -r /tmp/mesa_rh9.zip .; popd


rebuild:
	$(MAKE) clean
	$(MAKE) install

rebuild_secure:
	$(MAKE) clean_secure
	$(MAKE) install_secure

all:
	cd external;	make
	cd libsrc;	make install
	cd testapps;	make
	cd apps;	make
	cd scripts;	make install
	cd testdata;	make install
	cd runtime;	make install
	cd dbscripts/pgsql;	make install
	@echo "MESA Build Complete"

clean:
	cd external;	make clean
	cd libsrc;	make clean
	cd testapps;	make clean
	cd apps;	make clean
	cd lib;		rm -f lib*.a

clean_secure:
	cd secure_libsrc;	make clean
	cd secure_apps;		make clean

mesa:
	cd libsrc;	make install
	cd testapps;	make
	cd apps;	make
	cd scripts;	make install
	cd testdata;	make install
	cd runtime;	make install
	cd dbscripts/pgsql;	make install

mesaclean:
	cd libsrc;	make clean
	cd testapps;	make clean
	cd apps;	make clean

headerexport:
	cd libsrc;	make headerexport
