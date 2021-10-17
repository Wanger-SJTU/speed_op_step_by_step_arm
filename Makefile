
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


default: clean $(OUT)/raw_perf $(OUT)/opt_1

test:

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


$(OUT)/raw_perf: $(comm_objs)  $(OUT)/matmul_raw.o
	$(CXX) $(PKG_CFLAGS) -o $@ $^ $(LDFLAGS)

$(OUT)/opt_1: $(comm_objs)  $(OUT)/matmul_opt_1.o
	$(CXX) $(PKG_CFLAGS) -o $@ $^ $(LDFLAGS)

clean:
	rm -rf build/
