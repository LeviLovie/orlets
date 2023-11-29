run:
	mkdir -p ./build
	@cd ./build;\
		cmake ..;\
		make
	@./build/orlets $(path)

debug:
	mkdir -p ./build
	@cd ./build;\
		cmake ..;\
		make
	@./build/orlets $(path) -d

dev:
	mkdir -p ./build
	@cd ./build;\
		cmake ..;\
		make
	@./build/orlets ./test.orlets -d
