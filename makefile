OBJ = shoppingCart.o

all: shoppingCart
	gcc -o shoppingCart shoppingCart.o
	
shoppingCart:
	gcc -c shoppingCart.c
clean:
	rm -f $(OBJ)
	rm -f shoppingCart
