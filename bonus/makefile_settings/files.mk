# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    files.mk                                           :+:    :+:             #
#                                                      +:+                     #
#    By: mraasvel <mraasvel@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2021/06/10 10:25:56 by mraasvel      #+#    #+#                  #
#    Updated: 2021/06/14 17:47:41 by mraasvel      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

ifndef FILES_MK
FILES_MK = 1

# Directories
SDIR := src
ODIR := obj
DDIR := dep
IDIR := includes
LDIR := libs

# Files
SRC :=	src/forked_routine.c \
		src/shared/ft_itoa.c \
		src/shared/utils.c \
		src/shared/time_handling.c \
		src/shared/get_input.c \
		src/shared/print_msg.c \
		src/shared/ft_atoi.c \
		src/semaphore_init.c \
		src/main.c \
		src/philo_routine.c \
		src/create_children.c \
		src/process_init.c

OBJ := $(patsubst $(SDIR)/%.c,$(ODIR)/%.o,$(SRC))
DEP := $(patsubst $(SDIR)/%.c,$(DDIR)/%.d,$(SRC))

HDF :=	includes/philo.h \
		includes/proto.h \
		includes/ft_semaphore.h

endif
