EXEC = gk8_blockchain
APP_OBJS = 	Blockchain.o \
			BlockchainUser.o \
			Miner.o \
			SecuredTransaction.o \
			SignaturesGenerator.o \
			Trader.o \
			main.o

LIBS = -lpthread
all: $(EXEC)
CC=gcc -g
CXX=g++ -g

gk8_blockchain: $(APP_OBJS)
	g++ -std=c++14 -g $(LDFLAGS) -o $@ $(APP_OBJS) $(LDLIBS$(LDLIBS_$@)) $(LIBS) $(CFLAGS)

clean:
	rm -f *.o  $(EXEC) *.gdb *.elf *.a
