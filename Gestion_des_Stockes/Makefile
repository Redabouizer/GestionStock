
NAME		= GestionStock

CC			= c++
FLAGS		= -Wall -Wextra -Werror  
RM			= rm -rf

OBJDIR = .GestionStock


FILES	=	main \
			DataBase \
			Class/Depot \
			Class/Fournisseur \
			Class/Paiement \
			Class/Produit \
			Class/Stock \
			Class/ProduitElectronique \
			Fonctionnalites/GestionProduits \
			Fonctionnalites/GestionStock \
			Fonctionnalites/GestionPaiement \
			Fonctionnalites/GestionFournisseur
			
			
			
			

SRC			= $(addsuffix .cpp, $(FILES))
OBJ			= $(addprefix $(OBJDIR)/, $(FILES:=.o))
HEADER		= Header.hpp

#Colors:
GREEN		=	\e[92;5;118m
YELLOW		=	\e[93;5;226m
GRAY		=	\e[33;2;37m
RESET		=	\e[0m
CURSIVE		=	\e[33;3m


all: $(NAME)

$(NAME): $(OBJ) $(HEADER)
	@$(CC) $(OBJ) $(OPTS) -o $(NAME)
	@printf "$(_SUCCESS) $(GREEN)- Executable ready.\n$(RESET)"

$(OBJDIR)/%.o: %.cpp $(HEADER)
	@mkdir -p $(dir $@)
	@$(CC) $(FLAGS) $(OPTS) -c $< -o $@

clean:
	@$(RM) $(OBJDIR) $(OBJ)
	@printf "$(YELLOW)    - Object files removed.$(RESET)\n"

fclean: clean
	@$(RM) $(NAME)
	@printf "$(YELLOW)    - Executable removed.$(RESET)\n"

re: fclean all