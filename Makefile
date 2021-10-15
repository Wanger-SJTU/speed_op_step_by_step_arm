
#
# sample makefile
#
INC := inc
OPT_SRC := opt_gemm
UTILS_SRC := utils
OUT := build

TARGET := $(OUT)/main

# CXX        := ${NDK_CXX}
CFLAGS     := -O0 -I$(INC)
LDFLAGS    := -lm


comm_objs := $(OUT)/utils.o $(OUT)/dclock.o  $(OUT)/perf.o

eval_objs := $(OUT)/eval.o

test_objs := $(OUT)/gemm_4x4x4.o

$(OUT)/%.o: src/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CFLAGS) -c $< -o $@
	
$(OUT)/%.o: src/$(OPT_SRC)/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CFLAGS) -c $< -o $@

$(OUT)/%.o: src/$(UTILS_SRC)/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CFLAGS) -c $< -o $@

$(OUT)/gflops: src/gflops/test.S src/gflops/gflps_main.c
	@mkdir -p $(@D)
	${NDK_AS} -o $(OUT)/test.o src/gflops/test.S
	${NDK_CC} -c src/gflops/gflps_main.c -o $(OUT)/main.o
	${NDK_CC} -o $(OUT)/gflops $(OUT)/main.o $(OUT)/test.o 

clean:
	rm -rf main *.o


$(OUT)/raw_perf: $(comm_objs)  $(OUT)/matmul_raw.o
	$(CXX) $(PKG_CFLAGS) -o $@ $^ $(LDFLAGS)



.PHONY: $(OUT)/raw_perf

all: 

clean:
	rm -rf build/
