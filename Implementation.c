#include "Header.h"

/*this function create the list of the doses in the kitchen with price and quantity accordianly the instruction file*/
void CreateProducts(List* L, FILE* f) {
	char temp_name[MAX];/*set temporarity name*/
	dose* temp;/*set new temp node*/
	temp = (dose*)malloc(sizeof(dose));
	if (temp == NULL)
	{
		DeleteList(L);
		Error_Msg("Memmory!");
	}
	while (fscanf(f, "%s %d %f", temp_name, &(temp->Quantity), &(temp->Price)) != EOF) {
		if (temp->Price <= 0) {/*if price is not positive*/
			printf("Error!, price must be greate then 0.\n");
		}
		if (temp->Quantity < 0) {/*if Quantity is not positive*/
			printf("Error!, Quantity must be positive.\n");
		}
		temp->ProductName = (char*)malloc(strlen(temp_name) + 1);/*set memory allocation in size of temp_name*/
		if (temp->ProductName == NULL)
		{
			DeleteList(L);
			Error_Msg("Memmory!");
		}
		strcpy(temp->ProductName, temp_name);/*set the name of product if its a new name */
		if (CheckProductName(L, temp)) {
			printf("There is already product name like this. ");
		}
		if (L->tail == NULL) {/*list is empty*/
			L->tail = temp;
			temp->next = NULL;
			L->head = L->tail;
		}
		else {/*list is not empty*/
			L->tail->next = temp;
			L->tail = temp;
			L->tail->next = NULL;
		}
		temp = (dose*)malloc(sizeof(dose));/*create new node*/
		if (temp == NULL)
		{
			DeleteList(L);
			Error_Msg("Memmory!");
		}
	}
	free(temp);/*free the Unnecessary temp dose*/
}

/*this function add doses to the kitchen with amount*/
int AddItems(List* L, char* dose_name, int amount) {
	if (amount <= 0) {
		printf("Error! You entered non positive quantity.\n");
		return 1;
	}
	dose* head = L->head;/*set the head of the list*/
	while (head != NULL) {
		if (strcmp(head->ProductName, dose_name) == 0) {/*the product name is found*/
			head->Quantity += amount;
			return 0;
		}
		else
			head = head->next;/*forward the pointer*/
	}
	printf("We don't have %s,sorry\n",dose_name);
	return 1;
}

/*this function connection between the kitchen and resuturant and add an order to table*/
int OrderItem(List* doses, List* Tables, int TableNumber, char* ProductName, int Quantity) {
	if (Quantity <= 0) {
		printf("Quantity must be a positive number,sorry!\n");
		return 1;
	}
	dose* temp = (dose*)malloc(sizeof(dose));
	temp->ProductName = (char*)malloc(MAX);
	if (temp == NULL) {
		Error_Msg("Memmory allocation failed.");
		return 1;
	}
	strcpy(temp->ProductName, ProductName);
	temp->Quantity = Quantity;/*set Quantity to the new dose order*/
	temp->Price = 0;/*reset the price of the dose in the table*/

	if (Check_Order(TableNumber, doses, temp) == 1) /*if the check order failed (table number >50 or product name not found in the doses list*/
		return 1;/*return 1 (ERROR/NOT OK)*/
	else {/*else: if the order is OK (Quantity,TableNumber,ProductName) */
		Add_Order_To_Table(&(Tables[TableNumber]), temp);
		printf("%d %s were added to the table number %d\n", Quantity, ProductName, TableNumber);
		return 0;/*return'OK', after add the dose to the head of the table*/
	}
}
/*this function remove specific item in the list of orders*/
void RemoveItem(List* TableNumber, char* ProductName, int Quantity) {
	dose* head_p;/*set pointer to head of the list*/
	dose* p;/*set addition pointer to be prev*/
	head_p = TableNumber->head;
	p = head_p;/*pointer to save the previous node*/
	while (head_p != NULL) {
		if (strcmp(head_p->ProductName, ProductName) == 0) {/*if found the product to remove*/
			head_p->Quantity -= Quantity;
			if (head_p->Quantity == 0) {/*if all doses are cancel for the table and now there is Quantity of 0*/
				p->next = head_p->next;
				if (head_p == TableNumber->tail)
					TableNumber->tail = NULL;/*reset node to NULL after cancel the whole order */
			}
			else
				if (head_p->Quantity < 0)/*if the */
					break;
		}
		if (p->next == head_p)
			p = p->next;
		head_p = head_p->next;
	}
}
/*this function remove table order, clean it , and show receipt with some tip in the end*/
int RemoveTable(int index, List* Tables) {
	if (index < 0) {
		printf("You entered illegal index of table, sorry!\n");
		return 0;
	}
	float sum = 0;/*set sum of order to 0*/
	dose* temp = (dose*)malloc(sizeof(dose));
	temp->ProductName = (char*)malloc(MAX);
	temp = Tables[index].head;
	if (Tables[index].head == NULL) {/*if the table not order yet*/
		return 1;
	}
	while (temp != NULL) {
		printf("%d %s. ", temp->Quantity, temp->ProductName);
		sum += (temp->Price) * temp->Quantity;
		temp = temp->next;
	}
	while (Tables[index].head != NULL) {/*free all memory doses*/
		temp = Tables[index].head;
		Tables[index].head = Tables[index].head->next;
		free(temp->ProductName);/*free node memory allocated name*/
		free(temp);/*free node*/
	}
	printf("%.2f nis+%.2f nis for tips, please!\n", sum, sum / 10.0);
	return 0;
}
/*this function set all table list to NULL*/
void Set_NULL_Tables(List* Tables) {
	int i = 0;
	for (i = 0; i < MAX; i++) {/*reset the list of dishes of each tables in the resturant*/
		Tables[i].head = NULL;
		Tables[i].tail = NULL;
	}
}

/*this function show error msg and exit the files*/
void Error_Msg(char* msg){
	printf("\n%s", msg);
	exit(1);
}


void DeleteList(List* L) {/*free all memory allocation from Manot.txt file*/
	dose* temp = L->head;
	while (L->head != NULL) {
		L->head = L->head->next;
		free(temp->ProductName);/*free product name memory allocation*/
		free(temp);/*free node*/
		temp = L->head;
	}
	L->tail = NULL;/*reset tail of Manot list*/
}

/*this function check if the quantity of dose is ready to be remove from table order */
int Check_Quantity_Cancel(List* L, dose* temp,int index) {
	dose* current = L->head;
	dose* prev = NULL;
	if (current != NULL && !(strcmp(current->ProductName, temp->ProductName))) {
		if (current->Quantity < temp->Quantity) {/*check if the request quantity is over the capacity*/
			printf("There is no %d %s in the table to cancel.\n", temp->Quantity, temp->ProductName);
			return 1;
		}
		if (current->Quantity == temp->Quantity) {/*check if the quantity is ready to be remove to 0, if yes its free the node */
			L->head = current->next; // Change head
			printf("%d %s was returned to the kitchen from table number %d\n", temp->Quantity, current->ProductName, index);
			free(current);
			return 0;
		}
		else {
			current->Quantity -= temp->Quantity;/*reduce the quantity of the dose*/
			printf("%d %s was returned to the kitchen from table number %d\n", temp->Quantity, current->ProductName, index);
			return 0;
		}
	}

	while (current != NULL && (strcmp(current->ProductName, temp->ProductName))) {/*forward the pointer if no found the product*/
		prev = current;
		current = current->next;
	}

	if (current == NULL) {/*check if the list is over*/
		printf("There is no %d %s in the table to cancel.\n", temp->Quantity, temp->ProductName);
		return 1;
	}

	if (current->Quantity < temp->Quantity) {/*check if the request quantity is over the capacity*/
		printf("There is no %d %s in the table to cancel.\n", temp->Quantity, temp->ProductName);
		return 1;
	}
	if (current->Quantity == temp->Quantity) {/*check if the quantity is ready to be remove to 0, if yes its free the node */
		printf("%d %s was returned to the kitchen from table number %d\n", temp->Quantity, current->ProductName, index);

		prev->next = current->next;
		free(current);
		L->tail = prev;
		return 0;
	}
	else {
		current->Quantity -= temp->Quantity;/*reduce the quantity of the dose*/
		printf("%d %s was returned to the kitchen from table number %d\n", temp->Quantity, current->ProductName, index);

		return 0;
	}

	prev->next = current->next;
}

/*this function check the requst of cancel order before send to function to cancel, 
its check the table number, check if the table isn't order yet,
check if the product to cancel is exist */
int Check_Before_Cancel(List* L, int TableNumber, char* ProductName, int Quantity, List* Tables) {/*check if the order is prepare to canceling*/
	dose* temp = (dose*)malloc(sizeof(dose));
	temp->ProductName = (char*)malloc(MAX);
	if (temp == NULL) {
		Error_Msg("Memmory allocation failed.");
		return 1;
	}
	strcpy(temp->ProductName, ProductName);
	temp->Quantity = Quantity;

	if (TableNumber > 50) {/* wrong index*/
		printf("wrong index");
		return 1;
	}
	if (Tables[TableNumber].head == NULL) {/*if the table has not order yet */
		printf("The table number %d is not ordered yet\n", TableNumber);
		return 1;
	}
	if (CheckProductName(L, temp) == 0) {/*no product name found in the doses list*/
		printf("We don't have %s to cancel,sorry\n", temp->ProductName);
		return 1;
	}
	if (CheckProductName(&Tables[TableNumber], temp) == 0) {/*no product name found in the table order list*/
		printf("Table %d has not order %s at all.\n", TableNumber, temp->ProductName);
		return 1;
	}
	if (Quantity <= 0) {
		printf("Quantity not positive number.\n");
		return 1;
	}
	if (Check_Quantity_Cancel(&Tables[TableNumber], temp,TableNumber) == 0) {/*if the order ready to cancel (the table order this dose, the quantity in positive and not over what the table order)*/
		return 0;/*All check got succseed! The order can be canceled.*/
	}
	return 1;

}
/*this function cancel order from table after check if the order is ready to cancel with help from another functions*/
int Cancel_Order(List* L, int TableNumber, char* ProductName, int Quantity, List* Tables) {
	if (Check_Before_Cancel(L, TableNumber, ProductName, Quantity, Tables) == 1)/*there is a problem to cancel the order*/
		return 0;

}

/*this function check is the specific product is inside the list of doses in term of quantity,
if yes its reduce the amount of it in the kitchen*/
int CheckProductQuantity(List* L, dose* temp) {
	dose* head = L->head;
	while (head != NULL) {
		if (strcmp(head->ProductName, temp->ProductName) == 0) { /*if there is the same name in the list*/
			if (head->Quantity < temp->Quantity) {/*if the avaible quantity is under the requseted one return 1*/
				printf("We dont have %d of %s in the kitchen, sorry we just have %d!\n", temp->Quantity, temp->ProductName, head->Quantity);
				return 1;
			}
			else {
				head->Quantity -= temp->Quantity;/*reduce the quantity of doses in the kitchen*/
				return 0;
			}
		}
		head = head->next;/*forward the head pointer*/
	}
	return 0;
}
/*this function check is the table number is illgal, check if the product name is inside the list of dises,
and finally check if there is enough quantity of specific dose*/
int Check_Order(int TableNumber, List* doses, dose* temp) {/*check the specific order to table return 1 when got error*/
	if (TableNumber > MAX) {
		printf("Error! index table is not legal (>50).");
		return 1;
	}
	if (CheckProductName(doses, temp) == 0) {/*if there is no ProductName in the doses list */
		printf("We don't have %s,sorry!\n", temp->ProductName);
		return 1;
	}
	if (CheckProductQuantity(doses, temp) == 1) {/*if the product quantity in not avaible (ERROR)*/
		return 1;
	}
	return 0;/*return 0 when the order is OK, table number <50 and productname was found, and the quantity is OK.*/
}

/*this function check if the product name is in the list of doses or note*/
int CheckProductName(List* L, dose* temp) {
	dose* head = L->head;
	while (head != NULL) {
		if (strcmp(head->ProductName, temp->ProductName) == 0) { /*if there is the same name in the list*/
			temp->Price = head->Price;
			return 1;
		}
		head = head->next;
	}
	return 0;/*no product name found */
}

/*this function add an order to a specific table in the restuarnt*/
int Add_Order_To_Table(List* list, dose* temp) {
	dose* temp_head = list->head;/*set temp pointer to head*/
	if (list->head == NULL) {/*add dose(temp) to the head of the list*/
		list->head = temp;
		temp->next = NULL;
		list->tail = temp;
		return 0;
	}
	else {/*if the list is not empty */
		while (temp_head!= NULL) {
			if (strcmp(temp_head->ProductName, temp->ProductName) == 0) {/*if the product found in the orders*/
				temp_head->Quantity += temp->Quantity;/*add quantity to a specific dose in the kitchen*/
				return 0;
			}
			temp_head = temp_head->next;/*forward the pointer*/
		}
		list->tail->next = temp;/*reset the tail */
		temp->next = NULL;
		list->tail = temp;
		
	}
}








