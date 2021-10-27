
#
# sample makefile
#
INC := inc
OPT_SRC := opt_gemm
UTILS_SRC := utils
OUT := build
INTERMEDIATE :=$(OUT)/intermediate

#CXX := ${NDK_#CXX}
CFLAGS := -O3 -I$(INC) -std=c++14
LDFLAGS := -lm


comm_objs := $(INTERMEDIATE)/utils.o $(INTERMEDIATE)/dclock.o  $(INTERMEDIATE)/perf.o


default: clean perf raw
# raw


perf: 	$(OUT)/opt_1 \
		$(OUT)/opt_2 \

raw:	$(OUT)/raw_m_n_k_perf \
		$(OUT)/raw_n_m_k_perf \
		$(OUT)/raw_m_k_n_perf \
		$(OUT)/raw_k_m_n_perf \
		$(OUT)/raw_n_k_m_perf \
		$(OUT)/raw_k_n_m_perf 

gflops: $(OUT)/gflops

test: $(OUT)/test

$(OUT)/test: $(INTERMEDIATE)/matmul_opt_2.o $(INTERMEDIATE)/eval.o $(INTERMEDIATE)/matmul_ref.o $(INTERMEDIATE)/utils.o $(INTERMEDIATE)/dclock.o 
	$(CXX) $(PKG_CFLAGS) -o $@ $^ $(LDFLAGS)

$(INTERMEDIATE)/%.o: src/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CFLAGS) -c $< -o $@
	
$(INTERMEDIATE)/%.o: src/$(OPT_SRC)/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CFLAGS) -c $< -o $@

$(INTERMEDIATE)/%.o: src/$(UTILS_SRC)/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CFLAGS) -c $< -o $@

$(OUT)/gflops: src/gflops/test.S src/gflops/gflps_main.c
	@mkdir -p $(@D)
	${NDK_AS} -o $(INTERMEDIATE)/test.o src/gflops/test.S
	${NDK_CC} -c src/gflops/gflps_main.c -o $(INTERMEDIATE)/main.o
	${NDK_CC} -o $(OUT)/gflops $(INTERMEDIATE)/main.o $(INTERMEDIATE)/test.o 


$(OUT)/raw_m_n_k_perf: $(comm_objs)  $(INTERMEDIATE)/matmul_raw_0.o
	$(CXX) $(PKG_CFLAGS) -o $@ $^ $(LDFLAGS)

$(OUT)/raw_n_m_k_perf: $(comm_objs)  $(INTERMEDIATE)/matmul_raw_1.o
	$(CXX) $(PKG_CFLAGS) -o $@ $^ $(LDFLAGS)

$(OUT)/raw_m_k_n_perf: $(comm_objs)  $(INTERMEDIATE)/matmul_raw_2.o
	$(CXX) $(PKG_CFLAGS) -o $@ $^ $(LDFLAGS)

$(OUT)/raw_k_m_n_perf: $(comm_objs)  $(INTERMEDIATE)/matmul_raw_3.o
	$(CXX) $(PKG_CFLAGS) -o $@ $^ $(LDFLAGS)

$(OUT)/raw_k_n_m_perf: $(comm_objs)  $(INTERMEDIATE)/matmul_raw_4.o
	$(CXX) $(PKG`_CFLAGS) -o $@ $^ $(LDFLAGS)

$(OUT)/raw_n_k_m_perf: $(comm_objs)  $(INTERMEDIATE)/matmul_raw_5.o
	$(CXX) $(PKG_CFLAGS) -o $@ $^ $(LDFLAGS)

$(OUT)/opt_1: $(comm_objs)  $(INTERMEDIATE)/matmul_opt_1.o
	$(CXX) $(PKG_CFLAGS) -o $@ $^ $(LDFLAGS)

$(OUT)/opt_2: $(comm_objs)  $(INTERMEDIATE)/matmul_opt_2.o
	$(CXX) $(PKG_CFLAGS) -o $@ $^ $(LDFLAGS)

clean:
	rm -rf build/
