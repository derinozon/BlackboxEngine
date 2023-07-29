CCV = -std=c++17
#WEB SETTINGS
WC = em++
WSHELL = --shell-file res/shell.html
WBIND = -O0 --bind -s USE_GLFW=3 -s SINGLE_FILE=1 -s ALLOW_MEMORY_GROWTH=1 -s USE_WEBGL2=1 #-s MAX_WEBGL_VERSION=2 -sLLD_REPORT_UNDEFINED
# -s FULL_ES3=1 -s FULL_ES2=1 -s USE_WEBGL2=1#
WINCLUDE = -I./include -I./lib/ImGUI
WFILE = --preload-file ./res --use-preload-plugins
WEMBED = --embed-file ./res
WDEBUG = -g4 -s ASSERTIONS=2 -s SAFE_HEAP=1 -s STACK_OVERFLOW_CHECK=1

SRC_FILES := $(wildcard src/*.cpp lib/*.cpp lib/ImGUI/*.cpp)

IN = demos/main.cpp blackbox.cpp

web: demos/main.cpp $(SRC_FILES)
	$(WC) $(CCV) $(IN) $(SRC_FILES) $(WINCLUDE) $(WBIND) $(WSHELL) -o build/index.html
# $(WC) $(CCV) $(IN) $(SRC_FILES) $(WINCLUDE) $(WBIND) -o build/index.html
#-s ASSERTIONS=1 -s SAFE_HEAP=1 -s LLD_REPORT_UNDEFINED -s USE_FREETYPE=1

# Make this work in the future!
webs: demos/main.cpp $(SRC_FILES)
	$(WC) $(CCV) demos/main.cpp $(WINCLUDE) -L./build -lblackbox $(WBIND) $(WFILE) -o build/index.html -s LLD_REPORT_UNDEFINED
#-s FULL_ES2=1

# not working
webd: demos/main.cpp
	mkdir -p build
	g++ $(CCV) demos/main.cpp $(WINCLUDE) -L./build/ -lblackboxd