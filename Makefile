run:
	@cd ./build;\
		cmake ..;\
		make
	@./build/orlets $(path)

fresh:
	@cd ./build;\
		cmake .. --fresh;\
		make
	@./build/orlets $(path)
