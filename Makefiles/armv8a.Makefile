
#
# sample makefile
#
INC := inc
OPT_SRC := common
UTILS_SRC := utils
OUT := build/armv8
INTERMEDIATE :=$(OUT)/intermediate

CXX:=${NDK_CXX}
CPPFLAGS := -Wall -fpermissive -std=c++11 -O3 -march=armv8-a -ftree-vectorize -I$(INC)
LDFLAGS := -lm


comm_objs := $(INTERMEDIATE)/utils.o $(INTERMEDIATE)/dclock.o  $(INTERMEDIATE)/perf.o


default: clean perf
# raw

perf: 

opt: 	$(OUT)/opt_1 \
		$(OUT)/opt_2 \

raw:	$(OUT)/raw_m_n_k_perf \
		$(OUT)/raw_n_m_k_perf \
		$(OUT)/raw_m_k_n_perf \
		$(OUT)/raw_k_m_n_perf \
		$(OUT)/raw_n_k_m_perf \
		$(OUT)/raw_k_n_m_perf 

gflops: $(OUT)/gflops

test: $(OUT)/test

clean: 
	rm -rf $(OUT)


$(INTERMEDIATE)/%.o: src/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CPPFLAGS) -c $< -o $@
	
$(INTERMEDIATE)/%.o: src/$(OPT_SRC)/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CPPFLAGS) -c $< -o $@

$(INTERMEDIATE)/%.o: src/$(UTILS_SRC)/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CPPFLAGS) -c $< -o $@

$(OUT)/gflops: src/gflops/test.S src/gflops/gflps_main.c
	@mkdir -p $(@D)
	${NDK_AS} -o $(INTERMEDIATE)/test.o src/gflops/test.S
	${NDK_CC} -c src/gflops/gflps_main.c -o $(INTERMEDIATE)/main.o
	${NDK_CC} -o $(OUT)/gflops $(INTERMEDIATE)/main.o $(INTERMEDIATE)/test.o 


$(OUT)/raw_m_n_k_perf: $(comm_objs)  $(INTERMEDIATE)/matmul_raw_mnk.o
	$(CXX) $(PKG_CFLAGS) -o $@ $^ $(LDFLAGS)

$(OUT)/raw_n_m_k_perf: $(comm_objs)  $(INTERMEDIATE)/matmul_raw_nmk.o
	$(CXX) $(PKG_CFLAGS) -o $@ $^ $(LDFLAGS)

$(OUT)/raw_m_k_n_perf: $(comm_objs)  $(INTERMEDIATE)/matmul_raw_mkn.o
	$(CXX) $(PKG_CFLAGS) -o $@ $^ $(LDFLAGS)

$(OUT)/raw_k_m_n_perf: $(comm_objs)  $(INTERMEDIATE)/matmul_raw_kmn.o
	$(CXX) $(PKG_CFLAGS) -o $@ $^ $(LDFLAGS)

$(OUT)/raw_k_n_m_perf: $(comm_objs)  $(INTERMEDIATE)/matmul_raw_knm.o
	$(CXX) $(PKG`_CFLAGS) -o $@ $^ $(LDFLAGS)

$(OUT)/raw_n_k_m_perf: $(comm_objs)  $(INTERMEDIATE)/matmul_raw_nkm.o
	$(CXX) $(PKG_CFLAGS) -o $@ $^ $(LDFLAGS)

$(OUT)/opt_1: $(comm_objs)  $(INTERMEDIATE)/matmul_opt_1.o
	$(CXX) $(PKG_CFLAGS) -o $@ $^ $(LDFLAGS)

$(OUT)/opt_2: $(comm_objs)  $(INTERMEDIATE)/matmul_opt_2.o
	$(CXX) $(PKG_CFLAGS) -o $@ $^ $(LDFLAGS)

$(OUT)/test: $(INTERMEDIATE)/matmul_opt_2.o  $(INTERMEDIATE)/eval.o $(INTERMEDIATE)/matmul_ref.o $(INTERMEDIATE)/utils.o $(INTERMEDIATE)/dclock.o 
	$(CXX) $(PKG_CFLAGS) -o $@ $^ $(LDFLAGS)
