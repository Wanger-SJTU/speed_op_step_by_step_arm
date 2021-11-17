
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


comm_objs := $(INTERMEDIATE)/utils.o $(INTERMEDIATE)/dclock.o  

perf: ${OUT}/${PERF_ITEM}

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
	$(CXX)  -c $< -o $@ $(CPPFLAGS)


$(OUT)/${PERF_ITEM}: $(INTERMEDIATE)/${PERF_ITEM}.o $(INTERMEDIATE)/perf.o $(comm_objs) 
	$(CXX) $(PKG_CFLAGS) -o $@ $^ $(LDFLAGS)

$(OUT)/test: $(INTERMEDIATE)/${TEST_ITEM}.o  $(INTERMEDIATE)/eval.o $(INTERMEDIATE)/matmul_ref.o $(comm_objs)
	$(CXX) $(PKG_CFLAGS) -o $@ $^ $(LDFLAGS)
