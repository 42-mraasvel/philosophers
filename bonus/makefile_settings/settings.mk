# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    settings.mk                                        :+:    :+:             #
#                                                      +:+                     #
#    By: mraasvel <mraasvel@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2021/06/10 10:26:06 by mraasvel      #+#    #+#                  #
#    Updated: 2021/06/11 15:12:42 by mraasvel      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

ifndef SETTINGS_MK
SETTINGS_MK = 1

# Compilation
CC = gcc
IFLAGS = -I$(IDIR)
LFLAGS = -lpthread
CFLAGS = -Wall -Wextra -Werror

# Debug flags based on OS
ifeq ($(shell uname -s),Linux)
	DFLAGS := -O0 -g -fsanitize=address -fsanitize=leak
else
	DFLAGS := -O0 -g -fsanitize=address
endif


# Add debug flag if specified
ifdef DEBUG
	CFLAGS += $(DFLAGS)
endif

RM = /bin/rm -f

endif
