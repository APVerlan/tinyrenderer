SYSCONF_LINK = g++
CPPFLAGS     = -std=c++17
LDFLAGS      =
LIBS         = -lm 

DESTDIR = ./
SOURCEDIR = ./sources/
TARGET  = main

OBJECTS := $(patsubst %.cpp,%.o,$(wildcard $(SOURCEDIR)*.cpp) main.cpp)

all: $(DESTDIR)$(TARGET)

$(DESTDIR)$(TARGET): $(OBJECTS)
	$(SYSCONF_LINK) -Wall $(LDFLAGS) -o $(DESTDIR)$(TARGET) $(OBJECTS) $(LIBS)

$(OBJECTS): %.o: %.cpp
	$(SYSCONF_LINK) -Wall $(CPPFLAGS) -c $(CFLAGS) $< -o $@

clean:
	-rm -f $(OBJECTS)
	-rm -f $(TARGET)

fclean: clean
	-rm -f *.tga

re: clean all

.PHONY: fclean re all clean