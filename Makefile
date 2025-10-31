LIBPATH := $(shell dirname "$(realpath "$(lastword $(MAKEFILE_LIST))")")
GRAPH_BLAS_PATH := $(LIBPATH)/vendor/GraphBLAS
LAGRAPH_PATH := $(LIBPATH)/vendor/LAGraph
BUILD := $(GRAPH_BLAS_PATH)/build
LAGRAPH_BUILD := $(LAGRAPH_PATH)/build
JOBS := $(shell nproc)

build: graphblas lagraph src
graphblas: 
	mkdir -p $(BUILD) && \
	cd $(GRAPH_BLAS_PATH)  &&\
	cmake -DCMAKE_C_COMPILER_LAUNCHER=ccache -DCMAKE_CXX_COMPILER_LAUNCHER=ccache \
	      -DCMAKE_BUILD_TYPE=Release \
	      -G Ninja -B build
	cmake --build $(BUILD) --parallel $(JOBS)

lagraph: 
	mkdir -p $(LAGRAPH_BUILD) && \
	cd $(LAGRAPH_PATH)  && \
	cmake -DGraphBLAS_DIR=$(BUILD) \
	      -DCMAKE_C_COMPILER_LAUNCHER=ccache -DCMAKE_CXX_COMPILER_LAUNCHER=ccache \
	      -DCMAKE_BUILD_TYPE=Release \
	      -G Ninja -B build
	cmake --build $(LAGRAPH_BUILD) --parallel $(JOBS)

clean:
	rm -rf $(BUILD)/* $(LAGRAPH_BUILD)/* ./build
src:
	mkdir -p build
	gcc src/main.c     -I./vendor/GraphBLAS/Include     -I./vendor/LAGraph/include     -L./vendor/LAGraph/build/src     -L./vendor/GraphBLAS/build     -llagraph -lgraphblas     -o build/main

.PHONY: all build lagraph clean src

