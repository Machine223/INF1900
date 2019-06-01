# #le nom de la librairie
# PROJECTNAME=libRobot 
# #les fichiers sources
# PRJSRC= $(wildcard *.cpp) 
# #le nom du fichier a generer libRobot.a
# OPTLEVEL=s
# TRG=$(PROJECTNAME).a 
# #on execute Makefile.commun qui se trouve au repertoire parent
# include ../Makefile.commun 
# $(TRG): $(OBJDEPS)
# 	ar crs $(TRG) $(OBJDEPS)
PROJECTNAME=libRobot
PRJSRC= $(wildcard *.cpp)
OPTLEVEL=s
TRG=$(PROJECTNAME).a
include ../Makefile.commun
$(TRG): $(OBJDEPS)
	ar crs $(TRG) $(OBJDEPS)