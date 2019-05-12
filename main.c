
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Session.h"
#define MAX_OPTIONS 16

void print_options()
{
	printf("\n");
	printf("0. New Session\n");
	printf("1. New Tab\n");
	printf("2. Show Tab\n");
	printf("3. Next Tab\n");
	printf("4. Prev Tab\n");
	printf("5. Tab Move Left\n");
	printf("6. Tab Move Right\n");
	printf("7. New Address\n");
	printf("8. Show New Address\n");
	printf("9. Next Site\n");
	printf("10. Prev Site\n");
	printf("11. Show Site\n");
	printf("12. Close Tab\n");
	printf("13. Close Session\n");
	printf("14. New Site\n");
	printf("15. Open New Tab\n");
	printf("16. Session 2\n");

	printf("\nEnter your input (0-%d): ", MAX_OPTIONS);
}

int get_option()
{
	int option;

	option = -1;
	while (option < 0 || option > MAX_OPTIONS) {       //out of limits
		print_options();
		scanf("%d",&option);
	}
	return option;
}

int main(int argc, char *argv[]) {
	int option;
	InfoSessionPtr 	MySession1=NULL, MySession2=NULL;
	char * Add;
	Add = (char*)malloc(sizeof(char)*40); //address string
	//strcpy(Add,"google.com");
	while(1){
		option = get_option();
		switch (option) {
		case 0:
			printf("Choose the site you want to visit.\n");
			scanf("%s",Add);
			MySession1 = SessionNew(Add);
			printf("\nNew Session Created!\n");
			break;
		case 1:
			SessionNewTab(MySession1);
			printf("\nNew Tab Created!\n");
			break;
		case 2:
			SessionTabShow(MySession1);
			break;
		case 3:
			SessionTabNext(MySession1);
			break;
		case 4:
			SessionTabPrev(MySession1);
			break;
		case 5:
			SessionTabMoveLeft(MySession1);
			break;
		case 6:
			SessionTabMoveRight(MySession1);
			break;
		case 7:
			printf("Choose the site you want to visit.\n");
			scanf("%s",Add);
			SessionNewOpeningAddress(Add,MySession1);
			break;
		case 8:
			SessionShowOpeningAddress(MySession1);
			break;
		case 9:
			SessionSiteNext(MySession1);
			break;
		case 10:
			SessionSitePrev(MySession1);
			break;
		case 11:
			SessionSiteShow(MySession1);
			break;
		case 12:
			SessionTabClose(MySession1);
			break;
		case 13:
			SessionClose(MySession1);
			break;
		case 14:
			printf("Choose the site you want to visit.\n");
			scanf("%s",Add);
			SessionNewAddress(Add,MySession1);
			printf("\nNew Site Created!\n");
			break;
		case 15:
			printf("Choose the site you want to visit.\n");
			scanf("%s",Add);
			SessionOpenNewTab(Add,MySession1);
			break;
		case 16:
			printf("Choose the site you want to visit.\n");
			scanf("%s",Add);
			MySession2 = SessionNew(Add);
			printf("\nNew Session Created!\n");
			break;

		}

}

	return 0;
}
