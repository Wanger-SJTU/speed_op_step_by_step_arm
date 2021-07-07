
#
# sample makefile
#
INC := ./inc
OPT_SRC := ./opt_gemm
UTILS_SRC := ./utils
OUT := ./build

TARGET := $(OUT)/main

CC         := clang++
LINKER     := $(CC) 
CFLAGS     := -O3 -I$(INC)
LDFLAGS    := -lm


comm_objs := $(OUT)/utils.o $(OUT)/dclock.o $(OUT)/matmul_raw.o

perf_objs := $(OUT)/perf.o
eval_objs := $(OUT)/eval.o

test_objs := $(OUT)/matmul_opt_2.o


$(OUT)/%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@
	
$(OUT)/%.o: $(OPT_SRC)/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

$(OUT)/%.o: $(UTILS_SRC)/%.cpp 
	$(CC) $(CFLAGS) -c $< -o $@

perf: clean $(perf_objs) $(test_objs) $(comm_objs)
	$(LINKER) $(perf_objs) $(test_objs) $(comm_objs) $(LDFLAGS)  -o $(TARGET)
	rm $(OUT)/*.o

test: $(eval_objs) $(test_objs) $(comm_objs)
	$(LINKER) $(eval_objs) $(test_objs) $(comm_objs) $(LDFLAGS)  -o $(TARGET)
	rm $(OUT)/*.o
	cd $(OUT) && ./main

run_perf: perf
	python perf
	
clean:
	rm -rf build
