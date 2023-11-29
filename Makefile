run:
	mkdir ./build
	@cd ./build;\
		cmake ..;\
		make
	@./build/orlets $(path)

debug:
	mkdir ./build
	@cd ./build;\
		cmake ..;\
		make
	@./build/orlets $(path) -d

dev:
	mkdir ./build
	@cd ./build;\
		cmake ..;\
		make
	@./build/orlets ./test.orlets -d
