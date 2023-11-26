run:
	@cd ./build;\
		cmake ..;\
		make
	@./build/orlets $(path)

debug:
	@cd ./build;\
		cmake ..;\
		make
	@./build/orlets $(path) -d

fresh:
	@cd ./build;\
		cmake .. --fresh;\
		make
	@./build/orlets $(path)
