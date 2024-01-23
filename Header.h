#ifndef Header
#define Header
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX 50/*define MAX for size of name and tables*/

typedef struct dose {/*set struct of dose with name price quantity and pointer to next node*/
	char* ProductName;/*product name with memory allocation*/
	float Price;/*product price*/
	int Quantity;/*quantity of each product*/
	struct dose* next;/*pointer to next node*/
}dose;

typedef struct List {/*set struct of list of doses*/
	dose* head;/*set pointer to head*/
	dose* tail;/*set pointer to tail*/
}List;

void CreateProducts(List*, FILE*);/*function to create list of products*/
int AddItems(List*, char*, int);/*function to add quantity to dose in the kitchen*/
int OrderItem(List*, List**, int, char*, int);/*function to add order to table from the kitchen*/
void RemoveItem(List*, char*, int);/*function to remove item from the table*/
int RemoveTable(int, List*);/*function to remove and close table and get reciept*/

void Set_NULL_Tables(List*);/*function to reset all tables lists to NULL*/
void Error_Msg(char*);/*function to show error msg and exit*/
void DeleteList(List*);/*function to delete list*/

int Check_Quantity_Cancel(List*, dose*,int);/*function to check the quantity of item*/
int Check_Before_Cancel(List*,int,char*,int, List*);/*check if the order is prepare to canceling*/
int Cancel_Order(List*,int, char*, int,List*);/*function to cancel an order after using function to help*/

int CheckProductQuantity(List*, dose*);/*check product order quantity*/
int Check_Order(int, List*, dose*);/*function to check all must requments about the order before cancel*/
int CheckProductName(List*, dose*);/*function to check same product names*/
int Add_Order_To_Table(List*, dose*);/*function to add an order to specific table in the list*/
#endif
