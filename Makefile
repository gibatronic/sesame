.DEFAULT_GOAL := help

.PHONY: build \
				clean \
				help \
				setup \
				upload

.SILENT:

# compile the project
build:
	tsk/build

# remove builded files
clean:
	tsk/clean

# show some help
help:
	tsk/help

# install third-party libraries
setup:
	tsk/setup

# upload the project
upload: build
	tsk/upload
