LIBPATH := $(shell dirname "$(realpath "$(lastword $(MAKEFILE_LIST))")")
GRAPH_BLAS_PATH := $(LIBPATH)/vendor/GraphBLAS
BUILD := $(GRAPH_BLAS_PATH)/build
JOBS := $(shell nproc)

build: graphblas src
graphblas: 
	mkdir -p $(BUILD) && \
	cd $(GRAPH_BLAS_PATH)  &&\
	cmake -DCMAKE_C_COMPILER_LAUNCHER=ccache -DCMAKE_CXX_COMPILER_LAUNCHER=ccache \
	      -DCMAKE_BUILD_TYPE=Release \
	      -G Ninja -B build
	cmake --build $(BUILD) --parallel $(JOBS)

clean:
	rm -rf $(BUILD)/* ./build
src:
	mkdir -p build
	gcc src/main.c     -I./vendor/GraphBLAS/Include       -L./vendor/GraphBLAS/build     -lgraphblas  -lm   -o build/main

.PHONY: all build lagraph clean src

