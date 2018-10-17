
all: 
	$(MAKE) -C src
	$(MAKE) -C testenv
	cd swig && ./build
	
clean:
	$(MAKE) clean -C src
	$(MAKE) clean -C testenv
	cd swig && ./build clean
