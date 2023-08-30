# Makefile 

CXX = g++
CC  = g++

O = ./obj/

CFLAGS = -std=c++98
#-Wno-deprecated  
CPPFLAGS =  -std=c++98
CPPCFLAGS =  -std=c++11
LIBS = -lm
#LIB_PATH = -L../lib


# Linux
X11_INCLUDE = 
X11_LIB =  
IML_LIB =  


$(O)%.o : %.c
	$(CC) $(CPPCFLAGS) $(X11_INCLUDE) -c $*.c -o $@
$(O)%.o : %.cpp
	$(CC) $(CPPFLAGS) $(X11_INCLUDE) -c $*.cpp -o $@
$(O)%.o : %.cxx
	$(CC) $(CFLAGS) $(X11_INCLUDE) -c $*.cxx -o $@

	
CSRC   = $(wildcard ./*.c)
CPPSRC = $(wildcard ./*.cpp)
CXXSRC = $(wildcard ./*.cxx)

COBJS = $(CSRC:%.c=$(O)%.o)
CPPOBJS = $(CPPSRC:%.cpp=$(O)%.o)
CXXOBJS   = $(CXXSRC:%.cxx=$(O)%.o)

$(O)DP  : $(CPPOBJS) $(CXXOBJS) $(COBJS)
	$(CXX) $(CLAGS) $(LIB_PATH) -o DP $(CPPOBJS) $(CXXOBJS) $(COBJS) $(LIBS) $(X11_LIB)  $(LIB_IML_PATH) $(IML_LIB) $(LIB_DLIB)
clean:
	rm -f $(CPPOBJS) $(CXXOBJS) $(COBJS) DP
	rm -f $(CPPOBJS) $(CXXOBJS) $(COBJS) $(O)/*.o 
