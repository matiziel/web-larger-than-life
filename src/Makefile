CC = g++
CFLAGS = -g -Wall -std=c++11
PYTHONPATH = /usr/include/python3.6/
NAME = grid

$(NAME).so: $(NAME).o
	$(CC) -shared -W $(NAME).o -lboost_python3 -I $(PYTHONPATH) -o $(NAME).so

$(NAME).o: $(NAME).cpp $(NAME).h
	$(CC) $(CFLAGS) -fPIC -I $(PYTHONPATH) -c $(NAME).cpp -o $(NAME).o

clean:
	rm -f *.o

