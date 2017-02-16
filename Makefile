# Variables

CPP = g++
CPPFLAGS = -c -std=c++1y
TARGET = account 

OBJECTS = main.o AccountController.o Account.o 



# Makefile scripts

$(TARGET) : $(OBJECTS)
	$(CPP) -o $(TARGET) $(OBJECTS)

main.o : main.h AccountController.h main.cpp
	$(CPP) $(CPPFLAGS) main.cpp

AccountController.o : main.h AccountController.h Account.h NormalAccount.h HighCreditAccount.h AccountController.cpp
	$(CPP) $(CPPFLAGS) AccountController.cpp	

Account.o : main.h Account.h Account.cpp
	$(CPP) $(CPPFLAGS) Account.cpp

clean : 
	rm $(OBJECTS)
