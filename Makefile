# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lrobino <lrobino@student.le-101.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/28 00:13:18 by lrobino           #+#    #+#              #
#    Updated: 2020/03/11 16:16:51 by lrobino          ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

##	AUTHOR
AUTHOR			= lrobino

##	VERSION
VERSION			= 1.0

##	THE DIRECTORY OF YOUR FINAL TARGET
TARGET_DIR		= .

##	TARGET NAMES FOR BOTH EXECUTABLE AND LIBRARY COMPILATION
TARGET_LIB		= libgnl.a
TARGET_EXE		= test-printf.out

##	CHOOSE WHICH TARGET TO USE BY DEFAULT
TARGET			= $(TARGET_LIB)

##	SOURCES DIRECTORY OF YOUR PROJECT (USE '.' IF THEY ARE IN THE CURRENT FOLDER)
SRC_DIR			= .

##	SOURCES OF YOUR PROJECT
SRCS			= get_next_line.c	\
				  get_next_line_utils.c

##	BINARIES DIRECTORY OF YOUR PROJECT
BIN_DIR			= bin


##	PUT THE DIRECTORIES OF YOUR HEADER FILES HERE
HEADERS_DIR		= .

##	HEADERS OF YOUR PROJET /!\ USE FULL PATH FROM CURRENT FOLDER /!\ 
HEADERS			= get_next_line.h

##	LIBS DIRECTORY OF YOUR PROJECT (USE '-' IF YOUR PROJECT DO NOT USE LIBRARY)
LIB_DIR			= -

##	LIBS THAT YOU ARE USING
LIBS			= -

################################################################################
####					DO NOT EDIT THINGS BELOW THIS						####
################################################################################

##

OBJS			= $(addprefix $(BIN_DIR)/,$(SRCS:.c=.o))

INCLUDES		= $(addprefix -I,$(HEADERS_DIR))

ifneq	($(LIB_DIR), -)
	LIBFILES		= $(addprefix $(LIB_DIR)/,$(addsuffix .a,$(LIBS)/$(LIBS)))
endif

##

RM				= rm -rf
CC				= gcc -c
GCC				= gcc
AR				= ar rcus
CFLAGS			= -Wall -Wextra -Werror
OUT				= --output

C_RESET= \033[0m

BGREEN = \033[1;32m
GREEN = \033[0;32m
YELLOW	= \033[0;33m
BYELLOW = \033[1;33m
PURPLE = \033[0;35m
BPURPLE = \033[1;35m
BRED	= \033[1;31m
RED		= \033[0;31m
BLUE	= \033[0;34m
BBLUE	= \033[1;34m

m_MAKE		= $(C_RESET)[$(BBLUE) $(TARGET) $(C_RESET)] [$(PURPLE)MAKE$(C_RESET)] :
m_INFO		= $(C_RESET)[$(BBLUE) $(TARGET) $(C_RESET)] [$(PURPLE)INFO$(C_RESET)] :
m_LINK		= $(C_RESET)[$(BBLUE) $(TARGET) $(C_RESET)] [$(PURPLE)LINK$(C_RESET)] :
m_COMP		= $(C_RESET)[$(BBLUE) $(TARGET) $(C_RESET)] [$(PURPLE)COMP$(C_RESET)] :

m_WARN		= $(C_RESET)[$(BBLUE) $(TARGET) $(C_RESET)] [$(BYELLOW)WARN$(C_RESET)] :$(YELLOW)
m_REMV		= $(C_RESET)[$(BBLUE) $(TARGET) $(C_RESET)] [$(BRED)CLEAN$(C_RESET)] :$(BYELLOW)
m_ERR		= $(C_RESET)[$(BRED) $(TARGET) $(C_RESET)] [$(BRED)ERROR$(C_RESET)] :$(BYELLOW)



all : version $(TARGET)
	
	@echo "$(C_RESET) Done."

##
##	LIB TARGET COMPILER	
##
lib : $(TARGET_LIB)
$(TARGET_LIB) : $(LIB_DIR)/ $(LIBFILES) $(BIN_DIR) $(OBJS)
	@echo "$(m_LINK) Linking library : $(TARGET_LIB)"
	@$(AR) $(TARGET_LIB) $(OBJS) $(LIBFILES)
	@echo "$(m_LINK) Link success !"


##
##	EXECUTABLE TARGET COMPILER
##
exe : $(TARGET_EXE)
$(TARGET_EXE) : $(LIB_DIR)/ $(LIBFILES) $(BIN_DIR) $(OBJS)
	@echo "$(m_LINK) Making target $(TARGET_EXE)"
	@$(GCC) $(OUT) $(TARGET_EXE) $(CFLAGS) $(OBJS) $(LIBFILES)
	@echo "$(m_LINK) Link success !"

##
##	BINS
##
$(BIN_DIR) :
	@mkdir -p $(BIN_DIR)
	@echo "$(m_WARN) $(BIN_DIR)/ Not found, created one.$(C_RESET)";



$(BIN_DIR)/%.o : %.c $(HEADERS)
	@$(CC) $< $(CFLAGS) $(OUT) $@ $(INCLUDES)
	@echo "$(m_COMP) Compiled : $<"



##
##	LIB
##
$(LIB_DIR)/ :
ifneq	($(LIB_DIR), -)
	@echo "$(m_ERR) Could not find $(LIB_DIR)/ directory !"
endif


$(LIB_DIR)/%/libft.a : $(LIB_DIR)/%
	@echo "$(m_MAKE) COMPILING LIB : $<$(C_RESET)"
	@$(MAKE) -C $<



##
##	CLEAN
##
cl : clean
clean :
	@$(RM) $(BIN_DIR)
	@echo "$(m_REMV) Removed .o files."



fc : fclean
fclean : clean
	@$(RM) $(TARGET_LIB)
	@$(RM) $(TARGET_LIB).dSYM
	@$(RM) $(TARGET_EXEC)
	@$(RM) $(TARGET_EXEC).dSYM
	@echo "$(m_REMV) Removed target : '$(TARGET_LIB)'"



##
##	UTILS
##
norm : version
	@echo "$(m_INFO) Norme for : '$(TARGET_LIB)'\n-->"
	@norminette



v : version
version :
	@printf "\e[1;1H\e[2J"
	@echo "$(BBLUE)#################################################################################"
	@echo "#                                                                               #"
	@echo "#           :::      ::::::::                                                   #"
	@echo "#         :+:      :+:    :+:                                                   #"
	@echo "#       +:+ +:+         +:+                                                     #"
	@echo "#     +#+  +:+       +#+                                                        #"
	@echo "#   +#+#+#+#+#+   +#+                                                           #"
	@echo "#         #+#    #+#                                                            #"
	@echo "#        ###   ######## - Lyon                                                  #"
	@echo "#                                                                               #"
	@echo "#$(C_RESET)>-----------------------------------------------------------------------------<$(BBLUE)#"
	@printf "#$(C_RESET)   Project : %-20.20s                                              $(BBLUE)#\n" $(TARGET_LIB)
	@printf "#$(C_RESET)   Version : %-15.15s                       Author : %-10.10s         $(BBLUE)#\n" $(VERSION) $(AUTHOR)
	@echo "#################################################################################$(C_RESET)\n\n"

##
##	SHORTCUTS
##
re : version fclean all

################################################################################

.PHONY	: all re fclean fc clean version v exe lib
