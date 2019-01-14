EXE_DSETS = testdsets
EXE_SQUAREMAZE = testsquaremaze

CPP_FILES_DSET_STUDENT = dsets.cpp
CPP_FILES_DEST_PROVIDED = testdsets.cpp
CPP_FILES_SQUAREMAZE_STUDENT = dsets.cpp
CPP_FILES_SQUAREMAZE_STUDENT += maze.cpp
CPP_FILES_SQUAREMAZE_PROVIDED = testsquaremaze.cpp
CPP_FILES_SQUAREMAZE_PROVIDED += $(wildcard utilities/*.cpp)
CPP_FILES_SQUAREMAZE_PROVIDED += $(wildcard utilities/lodepng/*.cpp)

OBJS += $(CPP_FILES_DSET_STUDENT:.cpp=.o)
OBJS += $(CPP_FILES_DEST_PROVIDED:.cpp=.o)

OBJS_SQUAREMAZE +=$(CPP_FILES_SQUAREMAZE_STUDENT:.cpp=.o)
OBJS_SQUAREMAZE +=$(CPP_FILES_SQUAREMAZE_PROVIDED:.cpp=.o)

CPP_TESTS += $(wildcard dsets.cpp)
CPP_TESTS += $(wildcard maze.cpp)
CPP_TESTS += $(wildcard utilities/*.cpp)
CPP_TESTS += $(wildcard utilities/lodepng/*.cpp)
CPP_TESTS += $(wildcard tests/*.cpp)
OBJS_TEST = $(CPP_TESTS:.cpp=.o)


CXX = clang++
LD = clang++
WARNINGS = -pedantic -Wall -Werror -Wfatal-errors -Wextra -Wno-unused-parameter -Wno-unused-variable
CXXFLAGS = -std=c++1y -stdlib=libc++ -g -O0 $(WARNINGS) -MP -MMD -c
LDFLAGS = -std=c++1y -stdlib=libc++ -lc++abi -lpthread
ASANFLAGS = -fsanitize=address -fno-omit-frame-pointer

all: $(EXE_DSETS) $(EXE_SQUAREMAZE)

# MP7.1
$(EXE_DSETS): $(OBJS)
	$(LD) $(OBJS) $(LDFLAGS) -o $(EXE_DSETS)
# MP7.2
$(EXE_SQUAREMAZE): $(OBJS_SQUAREMAZE)
	$(LD) $(OBJS_SQUAREMAZE) $(LDFLAGS) -o $(EXE_SQUAREMAZE)
test: $(OBJS_TEST)
	$(LD) $(OBJS_TEST) $(LDFLAGS) -o test

%.o: %.cpp %.h
	$(CXX) $(CXXFLAGS) $< -o $@

# include auto-generated dependencies
-include *.d
-include tests/*d

clean:
	rm -rf $(EXE_DSETS) $(EXE_SQUAREMAZE) *.exe test *.o *.d tests/*.o tests/*.d utilities/*.d utilities/*.o utilities/lodepng/*.o utilities/lodepng/*.d


.PHONY: clean
