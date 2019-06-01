#le nom de notre projet
PROJECTNAME=testLibrary
#les fichiers sources

PRJSRC= main.cpp

#l`emplacement des fichier a inclure
INC= -I../src_lib
#on utilise la librairie libRobot.a
LIBS= -L../src_lib -lRobot
OPTLEVEL=s
#le nom de fichier a executer testLibrary.out
TRG=$(PROJECTNAME).out
#on execute le Makefile.commun
include ../Makefile.commun
#la generation de l executable
$(TRG): $(OBJDEPS)
	$(CC) $(LDFLAGS) -o $(TRG) $(OBJDEPS) -lm $(LIBS)
