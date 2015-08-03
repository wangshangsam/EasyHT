ROOT = $(PWD)
DIR += ./example/kernel/
DIR += ./example/user/

all:
	for subdir in $(DIR); do \
		cd $$subdir; \
		make all; \
		cd $(ROOT); \
	done

clean:
	for subdir in $(DIR); do \
		cd $$subdir; \
		make clean; \
		cd $(ROOT); \
	done
