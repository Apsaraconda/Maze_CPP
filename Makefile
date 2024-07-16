.PHONY: all install uninstall dvi dist
DIST = $$(pwd)/../dist
DIR=Maze_CPP#  путь установки
INSTALL_PATH = $(DIR)
OS := $(shell uname -s)

ifeq ($(OS),Linux)
	OPEN_CMD = xdg-open
endif
ifeq ($(OS),Darwin)
	OPEN_CMD = open
endif


all: install 

install: uninstall
	mkdir $(DIR) && cd $(DIR) && cmake -DCMAKE_BUILD_TYPE=Release  ../src && cmake --build .

uninstall:
	rm -rf $(DIR)

run:
ifeq ($(OS),Linux)
	cd $(INSTALL_PATH) && ./Maze_CPP
endif
ifeq ($(OS),Darwin)
	cd $(INSTALL_PATH)/Maze_CPP.app/Contents/MacOS && $(OPEN_CMD) ./Maze_CPP
endif

latex_install:
ifeq ($(OS),Linux)
	sudo apt install texlive-latex-base
	sudo apt install texlive-lang-cyrillic
	sudo fmtutil-sys --all
endif
ifeq ($(OS),Darwin)
	brew install --cask mactex
endif

libs_install:
ifeq ($(OS),Linux)
	sudo apt-get install qt6-base-dev libglu1-mesa-dev freeglut3-dev mesa-common-dev
endif

dvi:
	latex ./readme.tex
	$(OPEN_CMD) ./readme.dvi

dist: uninstall install
	rm -rf Dist_Maze_CPP/
	mkdir Dist_Maze_CPP/
ifeq ($(OS), Linux)	
	mv $(INSTALL_PATH) Dist_Maze_CPP
endif
ifeq ($(OS),Darwin)
	mv $(INSTALL_PATH)/Maze_CPP.app Dist_Maze_CPP
endif	
	tar -czf Maze_CPP.tar.gz Dist_Maze_CPP
	rm -rf Dist_Maze_CPP/
	rm -rf $(INSTALL_PATH)

git_add:
	git add *.tex
	git add Makefile
	git add src/CMakeLists.txt
	git add src/*.cc
	git add src/*.h
	git add src/*.ui
	git add src/maze/*.cc
	git add src/maze/*.h
	git add materials/*.jpg
	git add README.md