build: configure
	$(MAKE) -f Makefile.directory build

rebuild: configure
	$(MAKE) -f Makefile.directory rebuild

build_missing: configure
	$(MAKE) -f Makefile.directory build_missing

clean: configure
	$(MAKE) -f Makefile.directory clean

test: configure
	$(MAKE) -f Makefile.directory test

configure:
	for directory in `find . -type d ! -path '*/rapidcheck*' ! -path '*/.*' ! -path '.'` ; do \
		cat Makefile.directory > "$$directory/Makefile" ; \
	done ; \
	for mainfile in `find . -name main.cpp ! -path '*/rapidcheck/*'` ; do \
		maindir=$$(echo "$$mainfile" | rev | cut -d/ -f 2- | rev) ; \
		rapidcheck_relpath=$$(echo "$$mainfile" | rev | cut -d/ -f 2- | rev | sed 's/[^\/]\+/\\\.\\\./g' | cut -d/ -f 2- | sed 's/\//\\\//g') ; \
		cat Makefile.project | sed "s/RAPIDCHECK_PATH/$$rapidcheck_relpath\/rapidcheck/g" > "$$maindir/Makefile" ; \
		test -f "$$maindir/algos.txt" || (echo "DEFAULT" > "$$maindir/algos.txt") ; \
	done

