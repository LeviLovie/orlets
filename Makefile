run:
	@cd ./build;\
		cmake ..;\
		make
	@./build/orlets

fresh:
	@cd ./build;\
		cmake .. --fresh;\
		make
	@./build/orlets
