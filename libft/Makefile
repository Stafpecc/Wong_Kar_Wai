NAME		:= libft.a

include libft.mk

BUILD_DIR	:= .build/
OBJS 		:= $(patsubst $(SRCSDIR)%.c,$(BUILD_DIR)%.o,$(SRCS))
DEPS		:= $(OBJS:.o=.d)

# ********** FLAGS AND COMPILATION FLAGS ************************************* #

CC			:= cc
CFLAGS		:= -Wall -Wextra -Werror
CPPFLAGS	:= -MMD -MP -I . -I incs/

AR			:= ar
ARFLAGS		:= -r -c -s

RM			:= rm -f
RMDIR		+= -r
MAKEFLAGS	+= --no-print-directory
DIR_DUP		= mkdir -p $(BUILD_DIR)

.DEFAULT_GOAL	:= all

# ********** COUNT FILES ***************************************************** #

NEED_REBUILD_SRC := $(shell find $(SRCSDIR) -name "*.c" -newer $(NAME) 2>/dev/null | wc -l)
NEWER_HEADERS := $(shell find incs/ libft/incs/ -name "*.h" -newer $(NAME) 2>/dev/null | wc -l)
EXECUTABLE_EXISTS := $(shell [ -f $(NAME) ] && echo 1 || echo 0)

RE_TARGET := $(filter re,$(MAKECMDGOALS))

ifneq ($(RE_TARGET),)
	NEED_REBUILD := $(words $(SRCS))
else
	ifeq ($(EXECUTABLE_EXISTS),0)
		NEED_REBUILD := $(words $(SRCS))
	else
		ifeq ($(NEWER_HEADERS),0)
			NEED_REBUILD := $(NEED_REBUILD_SRC)
		else
			NEED_REBUILD := $(words $(SRCS))
		endif
	endif
endif

# ********** RULES *********************************************************** #

-include $(DEPS)

.PHONY: init
init:
	@mkdir -p $(BUILD_DIR)
	@echo "$(NEED_REBUILD)" > $(BUILD_DIR)total_files
	@echo "0" > $(BUILD_DIR)current_file

.PHONY: all
all: init $(NAME)

$(NAME): Makefile $(OBJS)
	@$(AR) $(ARFLAGS) $(NAME) $(OBJS)
	@echo "\n\n$(GREEN_BOLD)✓ $(NAME) is ready ✨$(RESETC)\n"

$(BUILD_DIR)%.o: $(SRCSDIR)%.c
	@mkdir -p $(dir $@)
	@CURRENT=`cat $(BUILD_DIR)current_file`; \
	CURRENT=$$((CURRENT+1)); \
	echo "$$CURRENT" > $(BUILD_DIR)current_file; \
	TOTAL=`cat $(BUILD_DIR)total_files`; \
	POSITION=$$((CURRENT % 6)); \
	printf "$(ERASE)$(CYAN)["; \
	if [ "$$POSITION" -eq 0 ]; then \
		printf "⠋"; \
	elif [ "$$POSITION" -eq 1 ]; then \
		printf "⠙"; \
	elif [ "$$POSITION" -eq 2 ]; then \
		printf "⠹"; \
	elif [ "$$POSITION" -eq 3 ]; then \
		printf "⠸"; \
	elif [ "$$POSITION" -eq 4 ]; then \
		printf "⠼"; \
	else \
		printf "⠴"; \
	fi; \
	printf "] [%d/%d] $(RESETC)%s" "$$CURRENT" "$$TOTAL" "$<"
	@$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<

.PHONY: clean
clean:
	@$(RM) $(OBJS) $(DEPS)

.PHONY: fclean
fclean: clean
	$(RM) $(RMDIR) $(NAME) $(BUILD_DIR)
	@echo "$(RED_BOLD)✓ $(NAME) is fully cleaned!$(RESETC)"

.PHONY: re
re: fclean all

.SILENT: clean fclean

# ********** COLORS AND BACKGROUND COLORS ************************************ #

RESETC				:= \033[0m
ERASE				:=	\033[2K\r

GREEN_BOLD			:= \033[1;32m
RED_BOLD			:= \033[1;31m
CYAN				:= \033[0;36m
