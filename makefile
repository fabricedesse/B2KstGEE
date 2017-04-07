######################################################################
# Project: TMVA - Toolkit for Multivariate Data Analysis             #
# Code   : Example usage for TMVA analyses                           #
######################################################################
BINS = Main
# ADD = create_tree.cxx
DIC = VELO.cxx Station.cxx create_tree.cxx

CXX = g++
CCFLAGS = -O2 -ggdb -std=c++11
# TMVA = -lTMVA -lTMVAGui
# ROOSTAT = -lRooStats


LD = g++
LDFLAGS =

LIBS = $(shell root-config --libdir)
INCS = $(shell root-config --incdir)


default : $(BINS) $(ADD)  $(DIC)

# $(INCS): % : %.cxx
# 	$(CXX)

$(BINS): % : %.cxx VELO.h Station.h create_tree.h
	@echo -n "Building $@ ... "
	$(CXX) $(CCFLAGS) $(DIC)  $(ADD) $<  $(addprefix -I, $(INCS))  $(shell root-config --libs)  $(ROOSTAT) -lMLP -lMinuit -lTreePlayer  -lXMLIO   -lm  -g -o $@
	@echo "Done"
	  ./$(BINS)


clean:
	rm -f *.o	$(BINS)

# app: main.o inc.o
#     cc -o app main.o inc.o

# main.o: main.c inc.h
#     cc -c main.c inc.h

# inc.o: inc.c inc.h
#     cc -c inc.c inc.h
