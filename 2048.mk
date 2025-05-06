override SRCSDIR	:= srcs/
override SRCS		= $(addprefix $(SRCSDIR), $(SRC))

override GAMEDIR	:= game/
override DISPLAYDIR	:= display/

SRC	+= $(addsuffix .c, $(MAIN))

override MAIN		:= \
	main \

SRC += $(addprefix $(GAMEDIR), $(addsuffix .c, $(GAMESRC)))

override GAMESRC	:= \
	game \
	highscore \

SRC += $(addprefix $(DISPLAYDIR), $(addsuffix .c, $(DISPLAYSRC)))

override DISPLAYSRC	:= \
	display \
	menu \
	end_menu \
	options \
	print \
