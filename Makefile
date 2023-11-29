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

dev:
	@cd ./build;\
		cmake ..;\
		make
	@./build/orlets ./test.orlets -d
