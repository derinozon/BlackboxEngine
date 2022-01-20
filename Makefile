CCV = -std=c++17
#WEB SETTINGS
WC = em++
WSHELL = --shell-file res/shell.html
WBIND = -O0 --bind -s USE_GLFW=3 -s SINGLE_FILE=1 -s ALLOW_MEMORY_GROWTH=1
WINCLUDE = -I"/usr/local/Cellar/glm/0.9.9.8/include" -I./include -I./lib/ImGUI -I/usr/local/include/
WFILE = --preload-file ./res --use-preload-plugins
WDEBUG = -g4 -s ASSERTIONS=2 -s SAFE_HEAP=1 -s STACK_OVERFLOW_CHECK=1

SRC_FILES := $(wildcard src/*.cpp lib/*.cpp lib/ImGUI/*.cpp)

IN = main.cpp engine.cpp


web: main.cpp $(SRC_FILES)
	mkdir -p build
	$(WC) $(CCV) $(IN) $(SRC_FILES) $(WINCLUDE) $(WBIND) -s MAX_WEBGL_VERSION=2 $(WSHELL) $(WFILE) -o build/index.html
#-s ASSERTIONS=1 -s SAFE_HEAP=1 -s LLD_REPORT_UNDEFINED -s USE_FREETYPE=1

webs: main.cpp $(SRC_FILES)
	mkdir -p build
	$(WC) $(CCV) main.cpp -L"build/libmain.a" $(WINCLUDE) $(WBIND) -s FULL_ES2=1 $(WSHELL) $(WFILE) -o build/index.html

# not working
webd: main.cpp $(SRC_FILES)
	mkdir -p build
	$(WC) $(CCV) $(IN) $(SRC_FILES) $(WINCLUDE) $(WBIND) -s FULL_ES2=1 $(WSHELL) $(WFILE) -o build/index.html