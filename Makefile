IDIR=include
CXX=g++
CXXLAGS=-I$(IDIR)
SRCDIR=src
ODIR=src/obj

_DEPS = pencil.hpp
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = testPencil.o pencil.o 
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


$(ODIR)/%.o: $(SRCDIR)/%.cpp $(DEPS)
	$(CXX) -c -o $@ $< $(CXXFLAGS)

testSuite: $(OBJ)
	$(CXX) -o $@ $^ $(CXXFLAGS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 
