LIBPATH := $(shell dirname "$(realpath "$(lastword $(MAKEFILE_LIST))")")
GRAPH_BLAS_PATH := $(LIBPATH)/vendor/GraphBLAS
LAGRAPH_PATH := $(LIBPATH)/vendor/LAGraph
BUILD := $(GRAPH_BLAS_PATH)/build
LAGRAPH_BUILD := $(LAGRAPH_PATH)/build
JOBS := $(shell nproc)

all: build lagraph
build: $(BUILD)
	cd $(GRAPH_BLAS_PATH) && \
	cmake -DCMAKE_C_COMPILER_LAUNCHER=ccache -DCMAKE_CXX_COMPILER_LAUNCHER=ccache \
	      -DCMAKE_BUILD_TYPE=Release \
	      -G Ninja -B build
	cmake --build $(BUILD) --parallel $(JOBS)

lagraph: $(LAGRAPH_BUILD)
	cd $(LAGRAPH_PATH) && \
	cmake -DGraphBLAS_DIR=$(BUILD) \
	      -DCMAKE_C_COMPILER_LAUNCHER=ccache -DCMAKE_CXX_COMPILER_LAUNCHER=ccache \
	      -DCMAKE_BUILD_TYPE=Release \
	      -G Ninja -B build
	cmake --build $(LAGRAPH_BUILD) --parallel $(JOBS)

clean:
	rm -rf $(BUILD) $(LAGRAPH_BUILD)

.PHONY: all build lagraph clean

