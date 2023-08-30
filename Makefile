CC = g++
CFLAGS = -Wall -std=c++11 -O3 -c -D IL_STD -fopenmp -DCOMPLEX='std::complex<double>'

# Attempts to detect gcc major version. If older than 5.
CCV5 := $(shell expr `gcc -dumpversion | cut -f1 -d.` \< 5)

# Warning: gcc version older than 5 should not be used for development,
# as -fpermissive can let nonconformant code compile.
ifeq "$(CCV5)" "1"
$(info ****************Using -fpermissive. Don't use this gcc for development.*******************)
CFLAGS += -fpermissive
endif

SYSTEM     = x86-64_linux
LIBFORMAT  = static_pic


SPARSELIB_PATH = SparseLib++-1.7
INC=-I$(SPARSELIB_PATH)/mv/include  -I$(SPARSELIB_PATH)/include

LIB_IML = -lsparse -lmv -lspblas 
LIB_BOOST = -lboost_regex

SRC = src/
SRC_DIRS = $(SRC)

BIN_DIR = bin

LDFLAGS = -Wall -O3 -g -fopenmp
TARGET = PlacementPlotter

HDR_FILES:= $(wildcard $(SRC_DIRS)/*.h)
CPP_FILES:= $(wildcard $(SRC_DIRS)/*.cpp)
OBJ_FILES:= $(patsubst $(SRC_DIRS)/%.cpp, $(BIN_DIR)/%.o, $(CPP_FILES))
SPARSELIB_FILES = $(SPARSELIB_PATH)/lib/libspblas.a $(SPARSELIB_PATH)/lib/libsparse.a $(SPARSELIB_PATH)/lib/libmv.a

CFLAGS += $(shell pkg-config --cflags freetype2) # evaluates to the correct include flags for the freetype headers

default: $(TARGET)

# all: bin  $(OBJ_FILES) $(TARGET)
all: lib $(CPP_FILES) $(TARGET)

$(BIN_DIR)/%.o : $(SRC_DIRS)/%.cpp 
	$(CC) $(CFLAGS) $(INC) -o $@ $<

$(TARGET) : $(OBJ_FILES) # $(SPARSELIB_FILES)
	$(MAKE) -C $(SPARSELIB_PATH) sp
	$(CC) $(LDFLAGS) $(OBJ_FILES) $(LIB_BOOST) -L$(SPARSELIB_PATH)/lib $(LIB_IML) -o $(TARGET)

clean:
	rm -rvf $(SPARSELIB_FILES)
	rm -rvf $(BIN_DIR)/*.o
	$(MAKE) -C $(SPARSELIB_PATH) clean
	rm -rvf $(TARGET)

