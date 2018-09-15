#* ************************************************************************** *#
#*                                                                            *#
#*                                                        :::      ::::::::   *#
#*   Makefile                                           :+:      :+:    :+:   *#
#*                                                    +:+ +:+         +:+     *#
#*   By: dlouise <davidlouiz@gmail.com>             +#+  +:+       +#+        *#
#*                                                +#+#+#+#+#+   +#+           *#
#*   Created: 2015/09/12 02:05:18 by dlouise           #+#    #+#             *#
#*   Updated: 2015/09/23 21:59:08 by dlouise          ###   ########.fr       *#
#*                                                                            *#
#* ************************************************************************** *#

.PHONY : clean, fclean, re
.SUFFIXES :

NAME = matrix

SRC =	main.cpp\
		  matrix.cpp

OBJ = $(SRC:.cpp=.o)

all : $(NAME)

$(NAME) : $(OBJ)
	g++ $(OBJ) -Wall -Werror -Wextra -o $@

%.o : %.cpp
	g++ -c $^ -Wall -Werror -Wextra -o $@

clean :
	rm -f $(OBJ)

fclean : clean
	rm -f $(NAME)

re : fclean all
