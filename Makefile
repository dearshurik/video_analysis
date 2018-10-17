
all: 
	$(MAKE) -C src
	$(MAKE) -C testenv
	
clean:
	$(MAKE) clean -C src
	$(MAKE) clean -C testenv
