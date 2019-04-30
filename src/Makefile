CC = g++
CFLAGS = -O3 -Wall -std=c++11
PYTHONPATH = /usr/include/python3.6/
NAME = Board
MODULE = board

$(MODULE).so: $(NAME).o
	$(CC) -shared -W $(NAME).o -lboost_python3 -I $(PYTHONPATH) -o $(MODULE).so

$(NAME).o:  $(NAME).cpp $(NAME).h 
	$(CC) $(CFLAGS) -fPIC -I $(PYTHONPATH) -c $(NAME).cpp -o $(NAME).o

clean:
	rm -f *.o
run:
	rm board.so -f
	make clean
	make
	python3 main.py
