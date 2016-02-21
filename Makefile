CPP=clang++
LATEROPTS=-Wall -Wextra
CPPOPTS=-std=c++11 -Wall -Wextra -Wfatal-errors
FRAMEWORKS=-framework CoreFoundation -framework ImageIO -framework QuickLook

all:
	$(CPP) $(CPPOPTS) -o ql-thumbnail ql-thumbnail.cpp $(FRAMEWORKS)

clean:
	$(RM) ql-thumbnail
