.PHONY: clean \
				help \
				setup \
				upload \
				verify

.SILENT:

# remove builded files
clean:
	tsk/clean

# show some help
help:
	tsk/help

# install third-party libraries
setup:
	tsk/setup

# verify, build and upload the project
upload:
	tsk/upload

# verify the project
verify:
	tsk/verify
