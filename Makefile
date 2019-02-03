#***********************************************************************
# * Authors :		BARBEAUT Reynald
# *
#***********************************************************************

# Variables propres a cette application
BIN = ./BIN/
INCLUDE = ./INCLUDE/
SRC = ./SRC/
OBJ = ./OBJ/
LIB = ./LIB/

# Variables
CC = gcc -g
CFLAGS = -O4 -W -Wall
CPPFLAGS = -I$(INCLUDE)
LDLIBS = -L$(LIB) -lm -lfonctionsTCP
LDLIBSUDP = -L$(LIB) -lm -lfonctionsUDP
LDLIBSCOMMON = -L$(LIB) -lm -lcommon

# Cible principale
all : $(BIN)serveur $(BIN)client $(BIN)emetteur $(BIN)recepteur $(BIN)anneauTCP $(BIN)anneauUDP $(BIN)serveurProtocole $(BIN)clientProtocole


# Regle principale avec l'edition de lien
$(BIN)serveur: $(OBJ)serveur.o $(LIB)libfonctionsTCP.a
	$(CC) $(CPPFLAGS) $(CFLAGS) -o 	$@ $^ $(LDLIBS)

$(BIN)client: $(OBJ)client.o $(LIB)libfonctionsTCP.a
	$(CC) $(CPPFLAGS) $(CFLAGS) -o 	$@ $^ $(LDLIBS)

$(BIN)emetteur: $(OBJ)emetteur.o $(LIB)libfonctionsUDP.a
	$(CC) $(CPPFLAGS) $(CFLAGS) -o 	$@ $^ $(LDLIBSUDP)

$(BIN)recepteur: $(OBJ)recepteur.o $(LIB)libfonctionsUDP.a
	$(CC) $(CPPFLAGS) $(CFLAGS) -o 	$@ $^ $(LDLIBSUDP)

$(BIN)anneauTCP: $(OBJ)anneauTCP.o $(LIB)libfonctionsTCP.a
	$(CC) $(CPPFLAGS) $(CFLAGS) -o 	$@ $^ $(LDLIBSTCP)

$(BIN)anneauUDP: $(OBJ)anneauUDP.o $(LIB)libfonctionsUDP.a
	$(CC) $(CPPFLAGS) $(CFLAGS) -o 	$@ $^ $(LDLIBSUDP)

$(BIN)serveurProtocole: $(OBJ)serveurProtocole.o $(LIB)libfonctionsTCP.a $(LIB)libcommon.a
	$(CC) $(CPPFLAGS) $(CFLAGS) -o 	$@ $^ $(LDLIBS)

$(BIN)clientProtocole: $(OBJ)clientProtocole.o $(LIB)libfonctionsTCP.a $(LIB)libcommon.a
	$(CC) $(CPPFLAGS) $(CFLAGS) -o 	$@ $^ $(LDLIBS)


# Regle de construction des .o
$(OBJ)%.o : $(SRC)%.c $(INCLUDE)%.h
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(LIB)libfonctionsTCP.a : $(OBJ)fonctionsTCP.o
	ar rcs $(LIB)libfonctionsTCP.a $(OBJ)fonctionsTCP.o

$(LIB)libfonctionsUDP.a : $(OBJ)fonctionsUDP.o
	ar rcs $(LIB)libfonctionsUDP.a $(OBJ)fonctionsUDP.o
	
$(LIB)libcommon.a : $(OBJ)common.o
	ar rcs $(LIB)libcommon.a $(OBJ)common.o

# Nettoyage des fichiers intermediaires
clean :
	rm -f $(OBJ)*

# Suppression de tous les fichiers issus de la compilation
veryclean : clean
	rm -f $(BIN)*
	rm -f $(LIB)*