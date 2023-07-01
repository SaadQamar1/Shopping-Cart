//Name: Saad Qamar

#include <stdio.h>
#include <stdlib.h>

//This is used to create a random order to pick items used later on in the code
#include <time.h>

//Initial definitions of the values provided in the assignment
#define maxCartCount 100
#define maxItems  25
#define maxWeight  5.0
#define possiblenextProduct 1
#define initialValue 0

//Initial variables for the function
int totalProducts = initialValue;
int totalBags = initialValue;
float totalWeightCheck = initialValue;
int a = initialValue;

//The first struct is the grocery item which contains the name, weight and price of the product being chosen
typedef struct GrocercyItem{
	char *name;
	float price;
	float weightOfproduct;
	char RefOrFre;
}GroceryItem;


//The bag struct has an array of 25 which is the count of products as well as the actual number of the products. Also containing the total weight of the bag with the products inside it
typedef struct Bag {
	float totalWeight;
	int gProductCount;
	//int heaviestitem;
	GroceryItem *ProductCount[25];
} Bag;

//The final struct is linked to the bag struct using a double pointer and also has a bag count and others inside them
typedef struct Cart{
	GroceryItem *Productloose[100];
	int groceryProductCount;
	int bagCount;
	Bag **Bags;
}Cart;

//The add2Bag function adds an item to a bag and returns 1 and 0 accordingly
int add2Bag(GroceryItem *product, Bag **Bags){
//The first condition checks if the max limit of items has been reached
	if((*Bags)->gProductCount + possiblenextProduct >= maxItems){
		return 0;
	}
	//If the max limit hasn't been reached then the item is added and set into a spot as well as the weight is added to the total weight of the bag
	else{
		(*Bags)->totalWeight +=  (*product).weightOfproduct;
		(*Bags)->ProductCount[(*Bags)->gProductCount] = product;
		++(*Bags)->gProductCount;
	}
	return 1;
}

//The remove from bag function removes an item from the bag depending on if the product is in the bag
int remove4romBag(GroceryItem *product, Bag *Bags){
	int a = initialValue;
	//This loop keeps going until it loops the count of the products inside the bag
	while(a < (*Bags).gProductCount){
		//This checks if the product is equal to the product in the bag as the certain index based on the loop
		if((*Bags).ProductCount[a] == product){
			int b = initialValue;
			//This loop keeps going switch the spot of each item since one is being removed and decrease the count by 1
			for(b = a + possiblenextProduct; b < (*Bags).gProductCount; b++){
				(*Bags).ProductCount[b - possiblenextProduct] = (*Bags).ProductCount[b];
			} 
			//Decreasing the weight of the porduct that has been removed from the total weight of the bag
			(*Bags).totalWeight -=  (*product).weightOfproduct;
			--(*Bags).gProductCount;
			return 1;
		}
		a++;
	}
	return 0;	
}

//This function is used to remove the perishable items from the bags
void deletePerish(Cart *Carts){
	int a = initialValue;
	//This is used to loop the count of the bags used
	while(a < (*Carts).bagCount){
		int b = initialValue;
		//Keeps looping to remove the perishable from a single bag if there are multiple perishables and checks each item
		while(b < (*Carts).Bags[a]->gProductCount){
			if((*Carts).Bags[a]->ProductCount[b]->RefOrFre){
				remove4romBag((*Carts).Bags[a] -> ProductCount[b], (*Carts).Bags[a]);	
				b--;
			}
			b++;
		}	
		//If there are no products left in a bag due to the removal of perishables the bag will be removed
		if((*Carts).Bags[a]->gProductCount == 0){
		//Freeing the memory of the bag that is being removed
			free((*Carts).Bags[a]);
			//Again used to switch the bags since one has been removed
			int q = initialValue;
			for(q = a+1; q < (*Carts).bagCount; q++){
				(*Carts).Bags[q-1] = (*Carts).Bags[q];
			}
			--(*Carts).bagCount;
			a--;
		}
		a++;
	}
	
	//This is used to go through each product and check if the product is a perishable item
	int mq = initialValue;
	while(mq <(*Carts).groceryProductCount){
		if((*Carts).Productloose[mq]->RefOrFre){
		//As used before switch the position of each loose product
			for( int sq = mq + 1; sq < (*Carts).groceryProductCount; sq++){
				(*Carts).Productloose[sq-1] = (*Carts).Productloose[sq];
			}
			//Decreases the count of the grocery product count each time a product is perishable 
			--Carts->groceryProductCount;
			mq--;
		}
	mq++;
	}	
}	



//The cart function adds an item to the grocery cart
int addGroceryItem2Cart(GroceryItem *product, Cart* Carts){
	//This if statement checks if the cart is gonna go over the 100 limit if another item is added thus returning 0 instead of adding another item
	if((*Carts).groceryProductCount + possiblenextProduct  >= maxCartCount){
		return 0;
	}
	//If there is space to be added the item is added and the grocery product count is increased since the count of items has increased additionally also sets the product into product lose
	else{
		Carts->Productloose[(*Carts).groceryProductCount] = product;
		++(*Carts).groceryProductCount;
		return 1;
	}
	if((*Carts).groceryProductCount == 0){
		return 0;
	}
}

//This function simply displays the product with its name weight and price
void ProductDisplay(GroceryItem *product) {
	printf("%s weighing %.3fkg with price %.2f\n", (*product).name, product->weightOfproduct, product -> price);
}


//This function displays the header of the bag which contains the bag number and total weight of the bag
void BagDisplay(Bag *Bags, int CountBag){
	printf("BAG %d  (Total Weight =  %0.3f kg ): \n", CountBag, (*Bags).totalWeight);
	int a = initialValue;
	while(a < (*Bags).gProductCount){
		ProductDisplay((*Bags).ProductCount[a]);
		a++;
	}			
}

//This displays the cart while also using the product display and bag display since it will output the final look being given out
void CartDisplay(Cart *Carts){
	int a = initialValue;
	//Loops based on the count of the grocery products in the cart
	while(a < (*Carts).groceryProductCount){
		ProductDisplay((*Carts).Productloose[a]);
		a++;
	}
	int b = initialValue;
	//Loops as many times as the amount of bags that are used
	printf("\n");
	while(b < (*Carts).bagCount){
		printf("\n");
		BagDisplay((*Carts).Bags[b],b);
		b++;
	}
}


//This function helps put everything together and pack them together
void GeneratePackedBags(Cart *Carts){
	//This loops the number of times as the number of items in the count
	while(a < (*Carts).groceryProductCount){
	//If the weight of the next item goes over the max weight of the bag when added to the total weight of the bag at the time it continues
	//This is mainly to check the amount of bags we need to allocate memory that will be needed
		if(((*Carts).Productloose[a] -> weightOfproduct) > maxWeight){
			a++;
			continue;
		}
		//If there are no bags it is 1 to start the count
		else{
			if(totalBags == initialValue || totalBags < initialValue){
				totalBags = 1;
			}
		}
		//Checking if the total products and the next one will go over the max item limit and checking if the weight of the product will go over which would require a new bag if it does go over the limit 
		if((totalWeightCheck + (*Carts).Productloose[a]->weightOfproduct) > maxWeight || totalProducts +possiblenextProduct > maxItems ){
			totalBags = totalBags + 1;
			totalProducts=1;
			totalWeightCheck = (*Carts).Productloose[a] -> weightOfproduct;
		}
		else{
			totalProducts++;
			totalWeightCheck += (*Carts).Productloose[a]->weightOfproduct;
		}
		a++;
	}
	(*Carts).bagCount = totalBags;
	
	//Allocating memory based on the total bags required from the loop above
	Bag **Bags = NULL;
	Bags = (Bag **) malloc(sizeof(Bag*) * totalBags);
	if (Bags == NULL) {
		printf("Memory Allocation error! \n");
		exit(0);
 	} 
 	int r = initialValue;
 	//Loops through each bag to allocate memory for each one
	while(r < totalBags){
		Bags[r] = (Bag *) malloc(sizeof(Bag));
		if (Bags == NULL) {
			printf("Memory Allocation error! \n");
			exit(0); 
	}
	//Reintializing the values
	(*Bags[r]).gProductCount = initialValue;
	(*Bags[r]).totalWeight = initialValue;

	r++;
	}
	//Initializing the variables
	int bagbeingFilled = initialValue;
	int additional = initialValue;
	float weightCheck2 = initialValue;
	int totalProducts2 = initialValue;
	//This loop is very similar to the one above as this time it actually adds the product to a bag 
	while(additional < (*Carts).groceryProductCount){
		for(int q = additional; q < (*Carts).groceryProductCount; q++){
			if(((*Carts).Productloose[q] -> weightOfproduct) > maxWeight){
				additional++;
				continue;
			}
			if(weightCheck2 + (*Carts).Productloose[q] -> weightOfproduct > maxWeight || totalProducts2 + possiblenextProduct > maxItems ){
				bagbeingFilled = bagbeingFilled + 1;
				weightCheck2 = (*Carts).Productloose[q]->weightOfproduct;
				//resetting the variable to recount for a new bag
				totalProducts2 = 1;
				add2Bag((*Carts).Productloose[q] ,&Bags[bagbeingFilled]);
			}
			//If the limits are not reached the product is simply added which leads a change in the weight and the count of the total products in the bag
			else{
				add2Bag((*Carts).Productloose[q] , &Bags[bagbeingFilled]);
				totalProducts2 = totalProducts2 + 1;
				weightCheck2 = weightCheck2 + (*Carts).Productloose[q] -> weightOfproduct;
			}
			//This for loop is used to switch around the loose products as many times as the count of the loose products
			for(int s = q + 1; s < (*Carts).groceryProductCount; s++){
				int index = s-1;
				(*Carts).Productloose[index] = (*Carts).Productloose[s];
			}
			//Due to the above loop there will be a decrement
			--(*Carts).groceryProductCount;
			q--;
		}
	}
	(*Carts).Bags = Bags;
}


int main(){

	//Baes coded provided
	GroceryItem testItems[12];
	char *sampleItemNames[] = {"Smart-Ones Frozen Entrees", "SnackPack Pudding", "Breyers Chocolate Icecream", "Nabob Coffee", "Gold Seal Salmon", "Ocean Spray Cranberry Cocktail", "Heinz Beans Original", "Lean Ground Beef", "5-Alive FrozenJuice", "Coca-Cola 12 pack", "Toilet Paper - 48 pack", "Crate of milk"};
	float sampleItemPrices[] = {1.99, 0.99, 2.99, 3.99, 1.99, 2.99, 0.79, 4.94, 0.75, 3.49, 40.96, 12.99};
	float sampleItemWeights[] = {0.311, 0.396, 2.27, 0.326, 0.213, 2.26, 0.477, 0.75, 0.426, 5.112, 10.89f, 6.18f};
	float sampleItemPerish[] = {1, 0, 1, 0, 0, 0, 0, 1, 1, 0, 0, 1};
	
	Cart TheFinalCart;
	TheFinalCart.groceryProductCount = initialValue;
	TheFinalCart.bagCount = initialValue;
	
	int a;
	int itemCount = 12;
	for (a = 0; a < itemCount; ++a) {
		testItems[a].name = sampleItemNames[a];
		testItems[a].price = sampleItemPrices[a];
		testItems[a].weightOfproduct = sampleItemWeights[a];
		testItems[a].RefOrFre = sampleItemPerish[a];
	}	

	//Random generator for the 12 items to be chosen 50 times
	srand(time(NULL));
	int b;
	for (b = 0; b < 50; b++) {
		int randomGen = (int)(rand()%(itemCount));
		addGroceryItem2Cart(&testItems[randomGen ], &TheFinalCart);
  	}
  	
  	//Outputs the list of the products
	printf("\n Products! \n ");
	printf("\n");
	printf("||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
	CartDisplay(&TheFinalCart);	
	  
	//This packs the bags 
	GeneratePackedBags(&TheFinalCart);
  	 
  	//This gives the products in a packed format in bags  
	printf("\n Packed! \n ");
	printf("\n");
	printf("||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
	CartDisplay(&TheFinalCart);
	
	//This function removes all the perishables from the bags
	deletePerish(&TheFinalCart);
	
	//Output for all the bags after the perishables have been removed
	printf("\n Bags AFter Deleted Perishables!\n ");
	printf("\n");
	printf("||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
	CartDisplay(&TheFinalCart);
	
	//This is to free up the space after the program has run and allocated space for everything that was needed
	int c;
	for (c = 0; a < TheFinalCart.bagCount; c++) {
		free(TheFinalCart.Bags[c]);
	}
	free(TheFinalCart.Bags);
	return 0;
}

	





























	

