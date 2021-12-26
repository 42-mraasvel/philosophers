# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    files.mk                                           :+:    :+:             #
#                                                      +:+                     #
#    By: mraasvel <mraasvel@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2021/06/08 14:56:44 by mraasvel      #+#    #+#                  #
#    Updated: 2021/06/14 16:19:29 by mraasvel      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

# Double inclusion protection
ifndef FILES_MK
FILES_MK = 1

# Directories
SDIR := src
ODIR := obj
DDIR := dep
IDIR := includes
LDIR := libs

# .c files
SRC :=	src/philo_util.c \
		src/shared/ft_itoa.c \
		src/shared/utils.c \
		src/shared/time_handling.c \
		src/shared/get_input.c \
		src/shared/print_msg.c \
		src/shared/ft_atoi.c \
		src/main.c \
		src/create_threads.c \
		src/mutex_init.c \
		src/philo_routine.c \
		src/monitor_thread.c

# .o files and header dependencies
OBJ :=	$(patsubst $(SDIR)/%.c,$(ODIR)/%.o,$(SRC))
DEP :=	$(patsubst $(SDIR)/%.c,$(DDIR)/%.d,$(SRC))

HDF :=	includes/philo.h \
		includes/proto.h

endif
