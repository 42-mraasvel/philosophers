# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: mraasvel <mraasvel@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2021/06/08 14:56:13 by mraasvel      #+#    #+#                  #
#    Updated: 2021/06/14 16:23:59 by mraasvel      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

# Executable
NAME := philo

include ./makefile_settings/files.mk
include ./makefile_settings/settings.mk

# Rules
.PHONY: all
all: $(NAME)

# Compilation
$(NAME): $(OBJ)
	$(CC) -o $@ $(OBJ) $(CFLAGS) $(LFLAGS)
$(OBJ): $(ODIR)/%.o: $(SDIR)/%.c
	@mkdir -p $(@D)
	$(CC) -c -o $@ $< $(CFLAGS) $(IFLAGS)
$(DDIR)/%.d: $(SDIR)/%.c
	@mkdir -p $(@D)
	@$(CC) $< -MM -MF $@ -MT $(ODIR)/$*.o $(IFLAGS)

# Cleanup
.PHONY: clean fclean re
clean:
	$(RM) -r $(ODIR)
	$(RM) -r $(DDIR)
fclean: clean
	$(RM) $(NAME)
re: fclean
	$(MAKE) all

.PHONY: debug
debug: fclean
	$(MAKE) DEBUG=1

-include $(DEP)
