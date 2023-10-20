#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Car                          //structure of the node
{
    int mileage, returndate;
    char plate[8];
    struct Car *next;
};

struct Car *getNewCar(char n_plate[], int n_mileage, int n_returndate)      //creates a new node 
{
    struct Car *newCar = NULL;
    newCar = malloc(sizeof(struct Car));
    if(newCar != NULL)
    {
        newCar -> next = NULL;
        newCar -> mileage = n_mileage;
        newCar -> returndate = n_returndate;
        strcpy(newCar -> plate,n_plate);
    }
    else
    {
        printf("Allocation failure! \n");
    }
    return newCar;
}

void printList(struct Car *c, char *comment)
{
    printf("Printing %s List: \n",comment);
    struct Car *t;
    t = c;
    if(t == NULL)
    {
        printf("List is empty\n");
    }
    else 
    {
        while(t)                                        //traverses through the linked list printing the information
        {
            printf("%s\n",t -> plate);
            printf("%d\n",t -> mileage);
            printf("%d\n",t -> returndate);
            printf("\n");
            t = t -> next;
        }
    }
}

struct Car *loadRepairList(struct Car *head)
{
    FILE *file = fopen("inRepair.txt","r");
    char plateno[8] = " ";
    int n_mileage, n_returndate,lines = 1;
    if(NULL == file)
        printf("file can't be opened.\n");
    char ch;
    while ((ch = fgetc(file)) != EOF)               //generates the number of lines in the file
    {
        if (ch == '\n')
        {
            lines++;
        }
    }
    int nocars = ((lines/3)-1);                     //calculates the number of cars stored in current file
    rewind(file);
    struct Car *added = NULL;
    for(int i = 1; i < nocars; i++)
    {
        fscanf(file,"%s",plateno);                                  //reads information from the file and stores it to its variable
        fscanf(file,"%d",&n_mileage);
        fscanf(file,"%d",&n_returndate);
        if(head == NULL)
        {
            head = getNewCar(plateno,n_mileage,n_returndate);               //adds a new head node
            if(head != NULL)
            {
                added = head;                                               
            }
        }
        else
        {
            added -> next = getNewCar(plateno,n_mileage,n_returndate);          //adds a new node to be linked on
            if(added -> next != NULL)
            {
                added = added -> next;                                          //links the nodes
            }
        }
    }
    return head;
}

struct Car *loadRentedList(struct Car *head)
{
    FILE *file = fopen("Rented.txt","r");
    char plateno[7] = " ";
    int n_mileage, n_returndate,lines = 1;
    if(NULL == file)
        printf("file can't be opened.\n");
    char ch;
    while ((ch = fgetc(file)) != EOF)
    {
        if (ch == '\n')
        {
            lines++;
        }
    }
    int nocars = ((lines/3)-1);
    rewind(file);
    struct Car *added = NULL;
    for(int i = 1; i < nocars; i++)
    {
        fscanf(file,"%s",plateno);
        fscanf(file,"%d",&n_mileage);
        fscanf(file,"%d",&n_returndate);
        if(head == NULL)
        {
            head = getNewCar(plateno,n_mileage,n_returndate);
            if(head != NULL)
            {
                added = head;
            }
        }
        else
        {
            added -> next = getNewCar(plateno,n_mileage,n_returndate);
            if(added -> next != NULL)
            {
                added = added -> next;
            }
        }
    }
    return head;
}

struct Car *loadAvailableList(struct Car *head)
{
    FILE *file = fopen("Available.txt","r");
    char plateno[7] = " ";
    int n_mileage, n_returndate,lines = 1;
    if(NULL == file)
        printf("file can't be opened.\n");
    char ch;
    while ((ch = fgetc(file)) != EOF)
    {
        if (ch == '\n')
        {
            lines++;
        }
    }
    int nocars = ((lines/3)-1);
    rewind(file);
    struct Car *added = NULL;
    for(int i = 1; i < nocars; i++)
    {
        fscanf(file,"%s",plateno);
        fscanf(file,"%d",&n_mileage);
        fscanf(file,"%d",&n_returndate);
        if(head == NULL)
        {
            head = getNewCar(plateno,n_mileage,n_returndate);
            if(head != NULL)
            {
                added = head;
            }
        }
        else
        {
            added -> next = getNewCar(plateno,n_mileage,n_returndate);
            if(added -> next != NULL)
            {
                added = added -> next;
            }
        }
    }
    return head;
}


int check(struct Car *head, char plate_n[])                     //function to check if the plate number inserted by user is in the required list
{
    struct Car *ptr, *temp;
    ptr = head;
    if(strcmp(ptr -> plate, plate_n) == 0)
    {
        return 1;                                               //returns 1 if the car is in the list
    }
    else
    {
        ptr = ptr -> next; 
        temp = head;
        while(ptr -> next != NULL)
        {
            if(strcmp(ptr -> plate, plate_n) == 0)
            {
                return 1;
            }
            else
            {
                ptr = ptr -> next;
                temp = temp -> next;
            }
        }
        if(ptr -> next == NULL)
        {
            return 0;                                               //returns 0 if the car is not in the list and so prompts user to enter plate number again
        }
    }
    return 0;
}

int checkFunc1(struct Car *available, struct Car *rented, struct Car *repair, char plate_n[])
{
    int x;
    x = (check(available, plate_n)) + (check(rented,plate_n)) + (check(repair,plate_n));            //adds the return value from the check functions for each list to make sure the new plate number is not already existent in on the lists and if more than 0 then it exists in one of the lists and so program will prompt user to enter another plate number
    return x;

}

struct Car *swap(struct Car *head, struct Car *ptr2, struct Car *ptr3, struct Car *prev3)       //function to swap nodes 
{
    head = ptr3;
    prev3 -> next = ptr2;
    struct Car *temp = ptr3 -> next;
    ptr3 -> next = ptr2 -> next;
    ptr2 -> next = temp;
    return head;
}

struct Car *recursiveSort(struct Car *head, int prompt)                             //function that recursively sorts the nodes depending on the return date from lowest to highest
{
    if(head -> next == NULL)
    {
        return head;
    }
    struct Car *ptr, *min;
    struct Car *prevMin = NULL;                                         //stores the node before the minimum node
    min = head;
    for(ptr = head; ptr->next != NULL; ptr = ptr -> next)               //traverses the list till the end
    {
        if(prompt == 2)
        {
            if((ptr -> next -> returndate) < (min ->returndate))            //checks if the return date of the next node is less than the minimum node
            {
                min = ptr -> next;
                prevMin = ptr;
            }
        }
        if(prompt == 3 || prompt == 1)
        {
            if((ptr -> next -> mileage) < (min ->mileage))            //checks if the return date of the next node is less than the minimum node
            {
                min = ptr -> next;
                prevMin = ptr;
            }
        }
    }
    if(min != head)
    {
        head = swap(head, head, min, prevMin);
    }
    head -> next = recursiveSort(head -> next,prompt);
    return head;
}

struct Car *sort(struct Car *head, int prompt)
{
    if(head == NULL)
    {
        return NULL;
    }
    head = recursiveSort(head,prompt);
    return head;
}

struct Car *addNewCar(struct Car *head, char plate_n[], int mileage_n, int return_n, int prompt)        //function that adds a new car to the list
{
    struct Car *temp = NULL;
    temp = (struct Car *)malloc(sizeof(struct Car));
    struct Car *ptr = NULL;
    ptr = head;
    if(prompt == 1)                                         //adds a new car to the available list if the prompt is 1
    {   
        temp = getNewCar(plate_n, mileage_n, 0);            //adds the new car to the available list
        while(ptr -> next != NULL)
        {
            ptr = ptr -> next;
        }
        ptr -> next = temp;
        return head;
    }
    if(prompt == 3)                                         //adds a new car to the repair list if the prompt is 3
    {
        temp = getNewCar(plate_n,mileage_n,0);              //adds the new car to the repair list
        while(ptr -> next != NULL)
        {
            ptr = ptr -> next;
        }
        ptr -> next = temp;
        return head;
    }
    return head;
}

struct Car *transfer(struct Car *head, char plate_n[])          //function that transfers a car from the repair list to the available list
{
    struct Car *repairhead = NULL;
    struct Car *ptr, *m, *ptr2;
    struct Car *temp = NULL;
    char plateno[8];
    int mileageno, returnno;
    repairhead = loadRepairList(repairhead);
    ptr2 = head;
    ptr = repairhead;
    while(ptr2 -> next != NULL)
    {
        ptr2 = ptr2 -> next;                                    //traverses to the end of the available list
    }
    if(strcmp(ptr -> plate,plate_n) == 0)                       //checks to see if the current node is the car we want to transfer
    {
        strcpy(plateno,ptr->plate);
        mileageno = ptr -> mileage;
        returnno = ptr -> returndate;
        temp = getNewCar(plateno,mileageno,returnno);           //if yes it adds the car to the end of the available list
        ptr2 -> next = temp;
        return head;
    }
    else                                                        //if no it continues to traverse through the repair list until it find the car we want to transfer
    {
        ptr = ptr -> next;
        m = repairhead;
        while(ptr != NULL)
        {
            if(strcmp(ptr -> plate, plate_n) == 0)
            {
                strcpy(plateno,ptr->plate);
                mileageno = ptr -> mileage;
                returnno = ptr -> returndate;
                temp = getNewCar(plateno,mileageno,returnno);
                ptr2 -> next = temp;
                return head;
            }
            else
            {
                ptr = ptr -> next;
                m = m -> next;
            }
        }
    }
    return head;
}

struct Car *deleteCar(struct Car *head, char plate_n[], int mileage_n, int return_n, int prompt)        //function to delete a car from a list
{
    struct Car *temp, *ptr;
    ptr = head;
    if(prompt == 2)
    {  
        if(strcmp(ptr -> plate,plate_n) == 0)                       //checks to see if the car in the head node is the one we want to delete
        {
            ptr = ptr -> next;
            head = ptr;                                             //if yes it deletes the head node and makes it the next one
            return head;                        
        }
        else
        {
            ptr = ptr -> next;
            temp = head;
            while(ptr != NULL)                                      //traverse through the list to find car we want to delete
            {
                if(strcmp(ptr -> plate, plate_n) == 0)
                {
                    ptr = ptr -> next;
                    temp -> next = ptr;                             //connects the predecessor of the node we want to delete with the next node
                    return head;
                }
                else
                {
                    ptr = ptr -> next;
                    temp = temp -> next;
                }

            }
        }
        
    }
    if(prompt == 3)
    {  
        if(strcmp(ptr -> plate,plate_n) == 0)
        {
            ptr = ptr -> next;
            head = ptr;
            return head;
        }
        else
        {
            ptr = ptr -> next;
            temp = head;
            while(ptr != NULL)
            {
                if(strcmp(ptr -> plate, plate_n) == 0)
                {
                    ptr = ptr -> next;
                    temp -> next = ptr;
                    return head;
                }
                else
                {
                    ptr = ptr -> next;
                    temp = temp -> next;
                }

            }
        }
    }
    return head;
}

struct Car *deleteCarAvailable(struct Car *head)                    //function that deletes the first car available from the list
{
    struct Car *ptr;
    ptr = head; 
    ptr = ptr -> next;
    head = ptr;
    return head;
}

struct Car *addRentedCar(struct Car *head, int return_n)            //function that adds the newly rented car to the rented list
{
    struct Car *availabletemp = NULL;
    char plateno[8];
    struct Car *ptr, *temp, *ptravailable;
    int mileageno;
    availabletemp = loadAvailableList(availabletemp);
    ptravailable = availabletemp;
    strcpy(plateno,ptravailable->plate);
    mileageno = ptravailable -> mileage;
    ptravailable = ptravailable -> next;
    availabletemp = ptravailable;
    temp = getNewCar(plateno,mileageno,return_n);
    ptr = head;
    while(ptr -> next != NULL)
    {
        ptr = ptr -> next;
    }
    ptr -> next = temp;
    return head;
}


int income(struct Car *head, char plate_n[], int mileage_n)             //function that calculates the income after a rented car is returned
{
    struct Car *ptr, *temp;
    int km = 0, charge = 0;
    ptr = head;
    if(strcmp(ptr -> plate,plate_n) == 0)                               //checks to see if the head node is the car that is returned and calculates the income
    {
        km = mileage_n - (ptr -> mileage);
        if(km <= 200)
        {
            charge = 80;
            return charge;
        }
        else
        {
            int diff = km - 200;
            charge = 80 + (0.15*diff);
            return charge;
        }
    }
    else
    {
        ptr = ptr -> next;                                              //traverses list until it finds the car that is returned and calculates the income
        temp = head;
        while(ptr != NULL)
        {
            if(strcmp(ptr -> plate, plate_n) == 0)
            {
                km = mileage_n - (ptr -> mileage);
                if(km <= 200)
                {
                    charge = 80;
                    return charge;
                }
                else
                {
                    int diff = km - 200;
                    charge = 80 + (0.15*diff);
                    return charge;
                }
            }
            else
            {
                ptr = ptr -> next;
                temp = temp -> next;
            }
        }
    }
    return charge;
}

void saveToFile(struct Car *head, int prompt)                           //function that overwrites the files with the new updated lists
{
  struct Car *t;
  t = head;
  if (prompt == 1) 
  {
    FILE *fp = fopen("Available.txt", "w");
    if(t == NULL)
    {
      printf("List is empty\n");
    }
    else
    {
      while(t)                                                          //traverses through the list writing the information to the file
      {
        fprintf(fp,"%s\n",t -> plate);
        fprintf(fp, "%d\n", t -> mileage);
        fprintf(fp, "%d\n", t-> returndate);
        fprintf(fp, "\n", NULL);
        t = t -> next;
      }
    }
    fclose(fp);
  }
  if (prompt == 2) 
  {
    FILE *fp = fopen("Rented.txt", "w");
    if(t == NULL)
    {
      printf("List is empty\n");
    }
    else
    {
      while(t)
      {
        fprintf(fp,"%s\n",t -> plate);
        fprintf(fp, "%d\n", t -> mileage);
        fprintf(fp, "%d\n", t-> returndate);
        fprintf(fp, "\n", NULL);
        t = t -> next;
      }
    }
    fclose(fp);
  }
  if (prompt == 3) 
  {
    FILE *fp = fopen("inRepair.txt", "w");
    if(t == NULL)
    {
      printf("List is empty\n");
    }
    else
    {
      while(t)
      {
        fprintf(fp,"%s\n",t -> plate);
        fprintf(fp, "%d\n", t -> mileage);
        fprintf(fp, "%d\n", t-> returndate);
        fprintf(fp, "\n", NULL);
        t = t -> next;
      }
    }
    fclose(fp);
  }
}


void quit()
{
    exit(0);
}

int main()
{
    int code,mileage_number, return_number, charge, total_income = 0;
    char plate_number[8];
    struct Car *head_available = NULL;
    struct Car *head_rented = NULL;
    struct Car *head_repair = NULL;
    head_available = loadAvailableList(head_available);                                     //creates the lists from the loaded files
    head_rented = loadRentedList(head_rented);
    head_repair = loadRepairList(head_repair);
    printf("1 - add a new car to the available-for-rent list\n");
    printf("2 - add a returned car to the available-for-rent list\n");
    printf("3 - add a returned car to the repair list\n");
    printf("4 - transfer a car from the repair list to the available-for-rent list\n");
    printf("5 - rent the first available car\n");
    printf("6 - print all the lists\n");
    printf("7 - quit\n");
    while(1)
    {
        printf("Enter transaction code you would like to use: ");
        scanf("%d",&code);
        while(code > 7 || code < 1)
        {
            printf("Invalid transaction code try again!\n");
            printf("Enter transcation code you would like to use: ");
            scanf("%d",&code);
        }   
        if(code == 1)
        {
            printf("Enter plate number (7 characters or numbers): ");
            scanf("%s",plate_number);
            while(strlen(plate_number) > 7)
            {
                printf("Invalid plate number please try again! ");
                printf("Enter plate number (7 characters or numbers): ");
                scanf("%s",plate_number);
            }
            while(checkFunc1(head_available,head_rented,head_repair,plate_number) > 0)
            {
                printf("Car already exists, please try again! ");
                printf("Enter plate number (7 characters or numbers): ");
                scanf("%s",plate_number);
            }
            printf("Enter mileage: ");
            scanf("%d",&mileage_number);
            head_available = addNewCar(head_available,plate_number,mileage_number, return_number, 1);
            head_available = sort(head_available,1);
            printf("Added a new car to available list!\n");
        }
        if(code == 2)
        {
            printf("Enter plate number (7 characters or numbers): ");
            scanf("%s",plate_number);
            while(strlen(plate_number) > 7)
            {
                printf("Invalid plate number please try again! ");
                printf("Enter plate number (7 characters or numbers): ");
                scanf("%s",plate_number);
            }
            while(check(head_rented,plate_number) == 0)
            {
                printf("Car already exists, please try again! ");
                printf("Enter plate number (7 characters or numbers): ");
                scanf("%s",plate_number);
            }
            printf("Enter mileage: ");
            scanf("%d",&mileage_number);
            charge = income(head_rented, plate_number, mileage_number);
            total_income += charge;
            head_rented = deleteCar(head_rented,plate_number, mileage_number,return_number, 2);
            head_available = addNewCar(head_available,plate_number,mileage_number, return_number, 1);
            head_available = sort(head_available,1);
            printf("Added a returned car to available list and charge was: %d.\n", charge);
        }
        if(code == 3)
        {
            printf("Enter plate number (7 characters or numbers): ");
            scanf("%s",plate_number);
            while(strlen(plate_number) > 7)
            {
                printf("Invalid plate number please try again! ");
                printf("Enter plate number (7 characters or numbers): ");
                scanf("%s",plate_number);
            }
            while(check(head_rented,plate_number) == 0)
            {
                printf("Car already exists, please try again! ");
                printf("Enter plate number (7 characters or numbers): ");
                scanf("%s",plate_number);
            }
            printf("Enter mileage: ");
            scanf("%d",&mileage_number);
            charge = income(head_rented, plate_number, mileage_number);
            total_income += charge;
            head_rented = deleteCar(head_rented,plate_number, mileage_number,return_number, 2);
            head_repair = addNewCar(head_repair, plate_number, mileage_number,return_number,3);
            head_repair = sort(head_repair,1);
            printf("Added a returned car to repair list and charge was: %d\n",charge);
        }
        if(code == 4)
        {
            printf("Enter plate number (7 characters or numbers): ");
            scanf("%s",plate_number);
            while(strlen(plate_number) > 7)
            {
                printf("Invalid plate number please try again! ");
                printf("Enter plate number (7 characters or numbers): ");
                scanf("%s",plate_number);
            }
            while(check(head_repair,plate_number) == 0)
            {
                printf("Car already exists, please try again! ");
                printf("Enter plate number (7 characters or numbers): ");
                scanf("%s",plate_number);
            }
            head_repair = deleteCar(head_repair, plate_number, mileage_number, return_number,3);
            transfer(head_available,plate_number);
            head_available = sort(head_available,1);
            printf("Transferred car from repair list to available list!\n");
        }
        if(code == 5)
        {
            printf("Enter expected return date (yymmdd): ");
            scanf("%d",&return_number);
            head_available = deleteCarAvailable(head_available);
            head_rented = addRentedCar(head_rented,return_number);
            head_rented = sort(head_rented,2);
            printf("Rented the first available car!\n");
        }
        if (code == 6)
        {
            printf("\n");
            printList(head_available,"Available");
            printList(head_rented, "Rented");
            printList(head_repair, "Repair");
        }
        
        if (code == 7)
        {
            saveToFile(head_available,1);
            saveToFile(head_rented,2);
            saveToFile(head_repair,3);
            printf("Total Income: %d\n",total_income);
            printf("Code Quitting!\n");
            quit();
        }
    }
}
