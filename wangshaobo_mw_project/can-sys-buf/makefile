CC = sparc-elf-gcc

SEND = can_sys.c send_buf.c
RECEIVE = can_sys.c receive_buf.c

all: send receive

send: $(SEND)
	$(CC) $(SEND) -o send

receive: $(RECEIVE)
	$(CC) $(RECEIVE) -o receive

clean:
	rm  send receive
