CXX=clang++
CXXOPTS=-std=c++11 -Wall -Wextra -Wfatal-errors
FRAMEWORKS=-framework CoreFoundation -framework ImageIO -framework QuickLook

all:
	$(CXX) $(CXXOPTS) -o ql-thumbnail ql-thumbnail.cpp $(FRAMEWORKS)

clean:
	$(RM) ql-thumbnail
