PGM=${ARCH}/but_driver.exe

# optional managers required
MANAGERS=all

# C source names, if any, go here -- minus the .c
CSRCS = init.c but.c
COBJS = $(CSRCS:%.c=${ARCH}/%.o)

H_FILES=system.h

OBJS=$(COBJS)

include $(RTEMS_MAKEFILE_PATH)/Makefile.inc
include $(RTEMS_CUSTOM)
include $(PROJECT_ROOT)/make/leaf.cfg

all:	${ARCH} $(PGM)

${PGM}: ${OBJS}
	$(make-exe)

clean:
	rm -rf *~
