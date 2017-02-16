# Variables

CXX = g++
CXXFLAGS = -c -std=c++1y
TARGET = account 

OBJECTS = main.o AccountController.o Account.o 



# Makefile scripts

$(TARGET) : $(OBJECTS)
	$(CXX) -o $(TARGET) $(OBJECTS)

main.o : main.h AccountController.h main.cpp
	$(CXX) $(CXXFLAGS) main.cpp

AccountController.o : main.h AccountController.h Account.h NormalAccount.h HighCreditAccount.h AccountController.cpp
	$(CXX) $(CXXFLAGS) AccountController.cpp	

Account.o : main.h Account.h Account.cpp
	$(CXX) $(CXXFLAGS) Account.cpp

clean : 
	rm $(OBJECTS)
