
all: clientk serverk

consumer: consumer.c
	gcc -Wall -o serverk serverk.c -lrt


producer: producer.c
	gcc -Wall -o clientk clientk.c -lrt

clean: 
	rm -fr *~ clientk serverk
