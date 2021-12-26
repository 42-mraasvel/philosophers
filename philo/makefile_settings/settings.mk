# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    settings.mk                                        :+:    :+:             #
#                                                      +:+                     #
#    By: mraasvel <mraasvel@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2021/06/08 14:56:41 by mraasvel      #+#    #+#                  #
#    Updated: 2021/09/29 16:35:26 by mraasvel      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

# Double inclusion protection
ifndef SETTINGS_MK
SETTINGS_MK = 1

# Compilation settings
CC = gcc
CFLAGS = -Wall -Wextra -Werror -O0
LFLAGS = -lpthread
IFLAGS = -I$(IDIR)

# Debug flags based on OS
ifeq ($(shell uname -s),Linux)
	DFLAGS := -O0 -g -fsanitize=address -fsanitize=leak
else
	DFLAGS := -O0 -g -fsanitize=address
endif

# Add debug flags if DEBUG define is present, else add optimized flag
ifdef DEBUG
	CFLAGS += $(DFLAGS)
endif

RM = /bin/rm -f

endif
