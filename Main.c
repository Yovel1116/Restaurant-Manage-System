#include "Header.h"

int main() {
	List L;/*set list of Manot*/
	List Tables[MAX];/*set 50 tables with list of doses */
	Set_NULL_Tables(Tables);/*reset all tables lists to NULL*/
	L.head = NULL;/*reset L list to NULL*/
	L.tail = NULL;/*reset L list to NULL*/

	char f_activate;/*set char for active some functions*/
	char ProductName[MAX];/*set name of product in size of MAX*/
	int Quantity, Tableindex;/*set int varible for table index and quantity per dose*/

	FILE* Manot_file;/*set pointer to text file*/
	FILE* Instruct_file;/*set pointer to text file*/

	Manot_file = fopen("Manot.txt", "rt");
	Instruct_file = fopen("Instructions.txt", "rt");
	if (Manot_file == NULL || Instruct_file == NULL)/*show error msg and close if some of the files cant open*/
		Error_Msg("input file is wrong");

	while (fscanf(Instruct_file, "%c", &f_activate) != EOF) {/*first get number of function to activate*/
		while (f_activate == '\n') {/*Skip over newline charcaters*/
			f_activate = fgetc(Instruct_file);}
		switch (f_activate){

		case '1':/*Active function number 1*/
			CreateProducts(&L, Manot_file);/*create new list of products from Manot.txt file*/
			printf("The kitchen was created\n");
			break;

		case '2':/*Active function number 2*/
			if (fscanf(Instruct_file, "%s %d", ProductName, &Quantity) != 2) {
				DeleteList(&L);
				Error_Msg("Error!");}
			if (AddItems(&L, ProductName, Quantity) == 0)/*check if the function add quantity*/
				printf("%d %s were added to the kitchen\n", Quantity, ProductName);
			break;

		case '3':/*Active function number 3*/
			if (fscanf(Instruct_file, "%d %s %d",&Tableindex, ProductName, &Quantity) != 3) {
				DeleteList(&L);
				Error_Msg("Error!");}
			OrderItem(&L, &Tables, Tableindex, ProductName, Quantity);/*send to order item the list of doses, Tables, specific table, and product*/
			break;

		case '4':/*Active function number 4*/
			if (fscanf(Instruct_file, "%d %s %d", &Tableindex, ProductName, &Quantity) != 3) {
				DeleteList(&L);
				Error_Msg("Error!");
			}
			Cancel_Order(&L, Tableindex, ProductName, Quantity, &Tables);
			break;

		case '5':/*Active function number 5*/
			if (fscanf(Instruct_file, "%d", &Tableindex) != 1) {
				DeleteList(&L);
				Error_Msg("Error!");}
			if (RemoveTable(Tableindex, &Tables) == 1)  /*if there is a problem to remove the table*/
				printf("The table number %d is not order yet\n", Tableindex);

		default:
			break;
		}
	}

	fclose(Instruct_file);/*close text files*/
	fclose(Manot_file);/*close text files*/
	DeleteList(&L);/*free list of Manot file memory allocation*/
}
