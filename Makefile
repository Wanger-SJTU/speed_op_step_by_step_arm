
#
# sample makefile
#
INC := inc
OPT_SRC := opt_gemm
UTILS_SRC := utils
OUT := build

TARGET := $(OUT)/main

CXX        := ${NDK_CXX}
CFLAGS     := -O3 -I$(INC)
LDFLAGS    := -lm


comm_objs := $(OUT)/utils.o $(OUT)/dclock.o $(OUT)/matmul_raw.o

perf_objs := $(OUT)/perf.o
eval_objs := $(OUT)/eval.o

test_objs := $(OUT)/gemm_4x4x4.o

$(OUT)/%.o: src/%.cpp
	$(CXX) $(CFLAGS) -c $< -o $@
	
$(OUT)/%.o: src/$(OPT_SRC)/%.cpp
	$(CXX) $(CFLAGS) -c $< -o $@

$(OUT)/%.o: src/$(UTILS_SRC)/%.cpp
	$(CXX) $(CFLAGS) -c $< -o $@

$(OUT)/%.o: src/gflops/%.cpp
	$(CXX) $(CFLAGS) -c $< -o $@


perf: clean $(perf_objs) $(test_objs) $(comm_objs)
	$(LINKER) $(perf_objs) $(test_objs) $(comm_objs) $(LDFLAGS)  -o $(TARGET)
	
raw: $(eval_objs) $(test_objs) $(comm_objs)
	$(CXX) $(PKG_CFLAGS) -o $@ $^ $(LDFLAGS)


clean:
	rm -rf build/*.o
