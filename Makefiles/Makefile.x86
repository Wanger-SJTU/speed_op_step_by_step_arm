
#
# sample makefile
#
INC := inc
COMMON_SRC := common
UTILS_SRC := utils
OUT := build/x86
INTERMEDIATE :=$(OUT)/intermediate

CPPFLAGS := -std=c++11 -O3 -I$(INC)
LDFLAGS := -lm


comm_objs := $(INTERMEDIATE)/utils.o $(INTERMEDIATE)/dclock.o  $(INTERMEDIATE)/perf.o


default: perf
# raw

perf: 	transpose

opt: 	$(OUT)/opt_1 \
		$(OUT)/opt_2 \

raw:	$(OUT)/raw_m_n_k \
		$(OUT)/raw_n_m_k \
		$(OUT)/raw_m_k_n \
		$(OUT)/raw_k_m_n \
		$(OUT)/raw_n_k_m \
		$(OUT)/raw_k_n_m 

transpose:	$(OUT)/transpose_m_n_k \
			$(OUT)/transpose_n_m_k \
			$(OUT)/transpose_m_k_n \
			$(OUT)/transpose_k_m_n \
			$(OUT)/transpose_n_k_m \
			$(OUT)/transpose_k_n_m 


gflops: $(OUT)/gflops

test: $(OUT)/test

clean: 
	rm -rf $(OUT)


$(INTERMEDIATE)/%.o: src/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CPPFLAGS) -c $< -o $@
	
$(INTERMEDIATE)/%.o: src/$(COMMON_SRC)/%.cpp
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


$(OUT)/raw_m_n_k: $(comm_objs)  $(INTERMEDIATE)/matmul_raw_mnk.o
	$(CXX) $(PKG_CFLAGS) -o $@ $^ $(LDFLAGS)

$(OUT)/raw_n_m_k: $(comm_objs)  $(INTERMEDIATE)/matmul_raw_nmk.o
	$(CXX) $(PKG_CFLAGS) -o $@ $^ $(LDFLAGS)

$(OUT)/raw_m_k_n: $(comm_objs)  $(INTERMEDIATE)/matmul_raw_mkn.o
	$(CXX) $(PKG_CFLAGS) -o $@ $^ $(LDFLAGS)

$(OUT)/raw_k_m_n: $(comm_objs)  $(INTERMEDIATE)/matmul_raw_kmn.o
	$(CXX) $(PKG_CFLAGS) -o $@ $^ $(LDFLAGS)

$(OUT)/raw_k_n_m: $(comm_objs)  $(INTERMEDIATE)/matmul_raw_knm.o
	$(CXX) $(PKG`_CFLAGS) -o $@ $^ $(LDFLAGS)

$(OUT)/raw_n_k_m: $(comm_objs)  $(INTERMEDIATE)/matmul_raw_nkm.o
	$(CXX) $(PKG_CFLAGS) -o $@ $^ $(LDFLAGS)


$(OUT)/transpose_m_n_k: $(comm_objs)  $(INTERMEDIATE)/matmul_transpose_mnk.o
	$(CXX) $(PKG_CFLAGS) -o $@ $^ $(LDFLAGS)

$(OUT)/transpose_n_m_k: $(comm_objs)  $(INTERMEDIATE)/matmul_transpose_nmk.o
	$(CXX) $(PKG_CFLAGS) -o $@ $^ $(LDFLAGS)

$(OUT)/transpose_m_k_n: $(comm_objs)  $(INTERMEDIATE)/matmul_transpose_mkn.o
	$(CXX) $(PKG_CFLAGS) -o $@ $^ $(LDFLAGS)

$(OUT)/transpose_k_m_n: $(comm_objs)  $(INTERMEDIATE)/matmul_transpose_kmn.o
	$(CXX) $(PKG_CFLAGS) -o $@ $^ $(LDFLAGS)

$(OUT)/transpose_k_n_m: $(comm_objs)  $(INTERMEDIATE)/matmul_transpose_knm.o
	$(CXX) $(PKG`_CFLAGS) -o $@ $^ $(LDFLAGS)

$(OUT)/transpose_n_k_m: $(comm_objs)  $(INTERMEDIATE)/matmul_transpose_nkm.o
	$(CXX) $(PKG_CFLAGS) -o $@ $^ $(LDFLAGS)


$(OUT)/matmul_opt_mnk_1x4: $(comm_objs)  $(INTERMEDIATE)/matmul_opt_mnk_1x4.o
	$(CXX) $(PKG_CFLAGS) -o $@ $^ $(LDFLAGS)

$(OUT)/matmul_opt_mnk_1x8: $(comm_objs)  $(INTERMEDIATE)/matmul_opt_mnk_1x8.o
	$(CXX) $(PKG_CFLAGS) -o $@ $^ $(LDFLAGS)

$(OUT)/opt_2: $(comm_objs)  $(INTERMEDIATE)/matmul_opt_2.o
	$(CXX) $(PKG_CFLAGS) -o $@ $^ $(LDFLAGS)

$(OUT)/test: $(INTERMEDIATE)/matmul_opt_2.o  $(INTERMEDIATE)/eval.o $(INTERMEDIATE)/matmul_ref.o $(INTERMEDIATE)/utils.o $(INTERMEDIATE)/dclock.o 
	$(CXX) $(PKG_CFLAGS) -o $@ $^ $(LDFLAGS)
