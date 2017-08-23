.PHONY: setup \
				upload \
				verify

.SILENT:

# install third-party libraries
setup:
	tsk/setup

# verify, build and upload the project
upload:
	tsk/upload

# verify the project
verify:
	tsk/verify
