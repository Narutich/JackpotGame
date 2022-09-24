#This is a makefile

all:
	g++ game.c finishGameJackpot.h finishGameNotMoney.h finishGameDevil.h -o game
	./game
	rm game
build: game
	g++ game.c finishGameJackpot.h finishGameNotMoney.h finishGameDevil.h -o game
run: game
	./game
clean:
	rm game
