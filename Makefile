all:
	@echo "Making CLient..."; make -f Makefile.client
	@echo "Making Server..."; make -f Makefile.server

clean:
	@echo "Cleaning..."
	@rm -f build/* bin/*
