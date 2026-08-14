
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// --- STRUCTURE DEFINITIONS ---
// Defines the customer attributes for the library system
typedef struct {
    int C_ID;
    char name[50];
    char surname[50];
    int age;
    int wallet;
} Customer;

// Defines the book attributes with a rental status indicator
typedef struct {
    int B_ID;
    char name[100];
    char author[100];
    int age_limit;
    int price_per_week;
    int rented; // 0: Available, 1: Rented
} Book;

// Defines the contract logs for active rentals
typedef struct {
    int R_ID;
    int C_ID;
    int B_ID;
    char rented_date[20];
    int week;
} Rented;

void menu();
void createCustomer();
void depositMoney();
void addNewBook();
void rentBook();
void deliveryBook();
void burnBook();
void updateCustomer();
void updateBook();
void listRentingCustomers();
void listCustomers();
void listBooks();
void searchBook();



//Main screen
void menu(){
    printf("\n --- AGU LIBRARY BOOKING SYSTEM ---\n");
    printf("1. Create new costumer \n");
    printf("2. Deposit money \n");
    printf("3. Add new book \n");
    printf("4. Rent a book \n");
    printf("5. Delivery a book \n");
    printf("6. Burn book \n");
    printf("7. Update customer info \n");
    printf("8. Update book info \n");
    printf("9. List renting customers \n");
    printf("10. List all customers \n");
    printf ("11. list all books \n");
    printf("12. Search book \n");
    printf("0. Exit \n");

}

//Create Costomer Function
void createCustomer(){
    //Open the file in 'a+' mode : 'a' for append (add to end) and '+' for read
    FILE *file = fopen("customers.txt","a+");//open by read and adding mode
    if(file==NULL){
        printf("File could not be opened! \n");
        return;
    }
    Customer newC;
    Customer temp;
    int maxID = 0;
    int exists = 0 ;

    printf("\n --- New Costomer Registration --- ");
    printf("Name : ");
    scanf("%s" , newC.name);
    printf("Surname : ");
    scanf("%s" , newC.surname);
    printf("Age : ");
    scanf("%d", &newC.age);
    printf("Wallet balance : ");
    scanf("%d", &newC.wallet);

    //Wrap to the file to the beginning and check
    rewind(file);
    //Read the file line by line to check if the name/surname already exists.
    while (fscanf(file, "%d %s %s %d %d", &temp.C_ID, temp.name, temp.surname, &temp.age, &temp.wallet) != EOF) {
        // Check name and surname
        if (strcmp(temp.name, newC.name) == 0 && strcmp(temp.surname, newC.surname) == 0) {
            exists = 1;
            break;
        }
        // foolow the biggest id 
        if (temp.C_ID > maxID) {
            maxID = temp.C_ID;
        }
    }
    if (exists) {
        printf("Error: Customer is already registered with this name and surname!\n");
    } else {
        newC.C_ID = maxID + 1; // Increment the ID by one based on the last record in the file
        //Save the new customer information to the text file
        fprintf(file, "%d %s %s %d %d\n", newC.C_ID, newC.name, newC.surname, newC.age, newC.wallet);
        printf("Customer registered succesfully. ID: %d\n", newC.C_ID);
    }
    //Always close the file to save changes and free system resources
    fclose(file);

}

void depositMoney(){
    //Open the original file for reading('r')
    FILE *file = fopen("customers.txt" , "r");
    //Create a temporary file to write the updated data('w')
    FILE *tempFile = fopen("temp.txt" , "w ");

    if(file==NULL || tempFile==NULL ){
        printf("Error:Could not open a file! \n");
        return;
    }

    int targetID, amount, found=0;
    Customer temp ;

    printf("\n ---Deposit Money --- \n");
    printf("Enter Customer ID : ");
    scanf("%d" , &targetID);
    printf("Enter amount to deposit (TL) : ");
    scanf("%d" , &amount );//Required: No fractional transactions

    //Read customers line by line
    while(fscanf(file, "%d %s %s %d %d ", &temp.C_ID , temp.name , temp.surname ,&temp.age ,&temp.wallet) != EOF){
        if (temp.C_ID == targetID){
            //If the target matching update the balance
            temp.wallet += amount; //Added to the existing balance
            found = 1;
            printf("Balance updated for %s %s . New balance : %d TL \n " ,temp.name, temp.surname, temp.wallet);
        }
        //Write to the temporary file
        fprintf(tempFile, "%d %s %s %d %d \n", temp.C_ID, temp.name, temp.surname, temp.age, temp.wallet);
    }
    fclose(file);
    fclose(tempFile);

    //Replace old file with updated one
    remove("customer.txt");
    rename("temp.txt" , "customers.txt ");

    if(!found){
        printf("Error: Customers with ID %d not found! \n ", targetID);
    }
}

void addNewBook() {
    // Open books.txt in 'a+' mode to allow both reading (for duplication check) and appending (for adding new data)
    FILE *file = fopen("books.txt", "a+");
    if (file == NULL) {
        printf("Error: Could not open books.txt!\n");
        return;
    }

    Book newB;
    Book temp;
    int maxID = 0;
    int exists = 0;

    printf("\n--- Add New Book ---\n");
    printf("Book Name: "); 
    // Reads strings with spaces until a newline character is encountered
    scanf(" %[^\n]s", newB.name); 
    printf("Author: "); 
    scanf(" %[^\n]s", newB.author);
    printf("Age Limit: "); 
    scanf("%d", &newB.age_limit);
    printf("Price per Week (TL): "); 
    scanf("%d", &newB.price_per_week);
    
    // Default status: 0 means 'Available' (not rented) as per assignment specifications
    newB.rented = 0; 

    // Move the file pointer back to the very beginning to parse existing records safely
    rewind(file);
    
    // CRITICAL: Notice the leading space before %d (" %d"). This clears leftover newlines and buffers.
    // The format matches listBooks exactly: spaces around each '|' pipe separator are strictly preserved.
    while (fscanf(file, " %d | %[^|] | %[^|] | %d | %d | %d\n", 
           &temp.B_ID, temp.name, temp.author, &temp.age_limit, &temp.price_per_week, &temp.rented) != EOF) {
        
        // Prevent duplicate entries by comparing both title and author names
        if (strcmp(temp.name, newB.name) == 0 && strcmp(temp.author, newB.author) == 0) {
            exists = 1;
            break;
        }
        // Calculate the next ID using auto-increment logic
        if (temp.B_ID > maxID) {
            maxID = temp.B_ID;
        }
    }

    if (exists) {
        printf("Error: This book already exists in the library database!\n");
    } else {
        // Increment the unique identifier by one based on the highest existing ID
        newB.B_ID = maxID + 1; 
        
        // CRITICAL: Write the structural data with clear '|' pipe layout to match the exact fscanf reader configuration
        fprintf(file, "%d | %s | %s | %d | %d | %d\n", 
                newB.B_ID, newB.name, newB.author, newB.age_limit, newB.price_per_week, newB.rented);
        printf("Success: Book added to the system with ID: %d\n", newB.B_ID);
    }

    // Close the stream to secure and flush structural updates down to the disk
    fclose(file);

}
void rentBook(){
    int cID, bID, weeks;
    printf("\n --- Rent a book --- \n");
    printf("Enter customer ID : ");
    scanf("%d", &cID);
    printf("Enter book ID : ");
    scanf("%d", &bID);
    printf("Enter rental duration (weeks) : ");
    scanf("%d", &weeks);

    //Customer check:Find age and wallet
    FILE *fCust = fopen("customers.txt", "r");
    Customer targetC;
    int foundC = 0 ;
    //Search for the specific customer ID in the records
    while (fscanf(fCust, "%d %s %s %d %d ", &targetC.C_ID,targetC.name, targetC.surname, &targetC.age, &targetC.wallet) != EOF){
        if(targetC.C_ID ==cID){
            foundC = 1;
            break;
        }
    }
    fclose(fCust);

    if(!foundC){
        printf("Error: Customer not found! \n");
        return;
    }

    //Book Check: Find price,age limit, and reneal status
    FILE *fBook = fopen("books.txt" , "r");
    Book targetB;
    int foundB = 0;
    //Search for the specific book ID in the records
    while(fscanf(fBook, " %d | %[^|] | %[^|] | %d | %d | %d \n" , &targetB.B_ID, targetB.name, targetB.author, &targetB.age_limit, &targetB.price_per_week,&targetB.rented) != EOF){
        if(targetB.B_ID== bID){
            foundB = 1 ;
            break;
        }
    }
    fclose(fBook);

    if(!foundB){
        printf("Error: Book not found! \n");
        return;
    }

    //Validation rules
    //Rule: It is impossible to rent a book that is already rented
    if(targetB.rented == 1){
        printf("Error: This book is already rented! \n");
        return;
    }
    //Check age limit : Verify if the customer's age meets the books requirements
    if(targetC.age < targetB.age_limit){
        printf("Error : Customer does not meet the age limit (%d)! \n" , targetB.age_limit);
        return;
    }
    //Check wallet balance : Calculate total price and verify if the customer can afford it
    int totalCost = targetB.price_per_week * weeks;
    if(targetC.wallet < totalCost){
        printf("Error: Insufficient wallet balance! Required : %d TL \n" ,
        totalCost);
        return;
    }

    //Update Book  file : Set rented to 1 
    fBook = fopen("books.txt", "r");
    FILE *fTempB = fopen("temp_books.txt", "w" );
    Book b;
    while (fscanf(fBook, "%d | %[^|] | %[^|] | %d | %d | %d\n", &b.B_ID, b.name, b.author, &b.age_limit, &b.price_per_week, &b.rented) != EOF) {
        if (b.B_ID == bID) b.rented = 1;
        fprintf(fTempB, "%d | %s | %s | %d | %d | %d\n", b.B_ID, b.name, b.author, b.age_limit, b.price_per_week, b.rented);
    }
    fclose(fBook);
    fclose(fTempB);
    remove("book.txt");
    rename("temp_books.txt", "books.txt");

    //Update Customer file : Deduct the rental cost from the customers wallet
    fCust = fopen ("customers.txt", "r");
    FILE *fTempC = fopen("temp_customers.txt" , "w");
    Customer c;
    while (fscanf(fCust, "%d %s %s %d %d", &c.C_ID, c.name, c.surname, &c.age, &c.wallet) != EOF) {
        if (c.C_ID == cID) c.wallet -= totalCost; //Update balance
        fprintf(fTempC, "%d %s %s %d %d\n", c.C_ID, c.name, c.surname, c.age, c.wallet);
    }
    fclose(fCust); fclose(fTempC);
    remove("customers.txt"); rename("temp_customers.txt", "customers.txt");

    //Record to rented.txt : Store the transaction
    FILE *fRent = fopen("rented.txt " , "a+");
    Rented r ;
    int maxRID = 0;
    rewind(fRent);
    //Find the last Rental ID (R_ID) to perform auto-increment
    while (fscanf(fRent, "%d %d %d %s %d", &r.R_ID, &r.C_ID, &r.B_ID, r.rented_date, &r.week) != EOF) {
        if (r.R_ID > maxRID) maxRID = r.R_ID;
    }
    // R_ID auto increment 
    fprintf(fRent, "%d %d %d %s %d\n", maxRID + 1, cID, bID, "2026-05-09", weeks); 
    fclose(fRent);

    printf("Success: Book rented successfully. Total cost: %d TL deducted.\n", totalCost);
}

void deliveryBook(){
    int rID,weeks_status;
    printf("\n --- Delivery a book --- \n");
    printf("Enter Rental ID (R_ID) : ");
    scanf("%d", &rID);
    printf("Enter weeks(e.g., 1 for one week early, -1 for one weeklate) : ");
    scanf("%d" , &weeks_status);

    //File pointers for synchoronization
    //We need to manege active rentals, history, books, and customers
    FILE *fRented = fopen("rented.txt" , "r");
    FILE *fTempR = fopen("temp_rented.txt", "w");
    FILE *fHistory =fopen("history.txt" , "a");//'a' for appending completed records

    Rented r ;
    int foundR = 0 , targetCID= -1, targetBID = -1 ;

    if(!fRented || fTempR || !fHistory){
        printf("Error: File operations failed! |n");
        return;
    }

    //Find record in rented.txt, move it to history.txt, and remove from rented.txt
    while(fscanf(fRented, "%d %d %d %s %d ", &r.R_ID ,& r.C_ID , &r.B_ID , r.rented_date, &r.week ) != EOF){
        if(r.R_ID == rID){
            foundR =1 ;
            targetCID = r.C_ID;
            targetBID = r.B_ID;

            //Save history.txt
            fprintf(fHistory, " %d %d %d %s %d \n" , r.R_ID , r.C_ID, r.B_ID , r.rented_date, r.week);

        }else{
            //Keep other active rentals in the system
            fprintf(fTempR, " %d %d %d %s %d \n" , r.R_ID, r.C_ID, r.B_ID ,r.rented_date, r.week);
        }
    }
    fclose(fRented);
    //Remove completed rental from active records
    fclose(fTempR);
    fclose(fHistory);
    remove("rented.txt");
    rename("temp_rented.txt", "rented.txt");

    if(!foundR){
        printf("Error : Rental record with ID %d not found! \n" , rID);
        return;
    }

    //Update books.txt: Set "rented" status back to 0 (Availavle)
    FILE *fBook = fopen("books.txt", "r");
    FILE *fTempB = fopen("temp_books.txt", "w");
    Book b;
    int pricePerWeek = 0;

    while(fscanf(fBook, "%d | %[^|] | %[^|] | %d | %d | %d \n", &b.B_ID, b.name, b.author, &b.age_limit, &b.price_per_week, &b.rented) != EOF){
        if(b.B_ID == targetBID){
            b.rented = 0;//Book is now available
            pricePerWeek= b.price_per_week;
        }
        fprintf(fTempB, "%d | %s | %s | %d | %d | %d\n", b.B_ID, b.name, b.author, b.age_limit, b.price_per_week, b.rented);
    }
    fclose(fBook);
    fclose(fTempB);
    remove("books.txt");
    rename("temp_books.txt", "books.txt");

    //Update customers.txt : Apply refund(early) or penelty(late)

    FILE *fCust = fopen ("customers.txt", "r");
    FILE *fTempC = fopen ("temp_customers.txt" , "w");
    Customer c;
    //Calculate adjustment: Early returns adds money(+), late return subtracts money(-)
    int adjustment = weeks_status * pricePerWeek;

    while(fscanf(fCust, "%d %s %s %d %d" , &c.C_ID, c.name, c.surname , &c.age, &c.wallet) != EOF){
        if (c.C_ID == targetCID){
            c.wallet += adjustment ; //Positive for refund, negative for penalty
            printf("Transaction successful for %s %s. New wallet balance: %d TL \n" ,c.name, c.surname, c.wallet);
        }
        fprintf(fTempC, "%d %s %s %d %d \n", c.C_ID, c.name, c.surname, c.age, c.wallet);
    }
    fclose(fCust);
    fclose(fTempC);
    remove("customers.txt");
    rename("temp_customers.txt", "customers.txt");
    printf("Book delivery processed succesfully. \n");
}
void burnBook(){
    int bID;
    printf(" \n ---Burn Book --- \n");
    printf("Enter book ID to burn : ");
    scanf("%d", &bID);

    FILE *file = fopen("books.txt", "r");
    FILE *tempFile = fopen("temp_books.txt", "w");

    if(file==NULL || tempFile == NULL){
        printf("Error: Could not open file! \n");
        return;
    }

    Book b;
    int found = 0;
    int isRented = 0;

    //Check if the book exists and its rental status
    while (fscanf(file, "%d | %[^|] | %[^|] | %d | %d | %d\n", 
           &b.B_ID, b.name, b.author, &b.age_limit, &b.price_per_week, &b.rented) != EOF) {
        
        if (b.B_ID == bID) {
            found = 1;
            if (b.rented == 1) {
                isRented = 1;
                // Since we can't burn it, we must keep it in the file
                fprintf(tempFile, "%d | %s | %s | %d | %d | %d\n", 
                        b.B_ID, b.name, b.author, b.age_limit, b.price_per_week, b.rented);
            }
            // If b.B_ID == bID and NOT rented, we just don't write it to tempFile (effectively deleting it)
        } else {
            // Write all other books to the temporary file
            fprintf(tempFile, "%d | %s | %s | %d | %d | %d\n", 
                    b.B_ID, b.name, b.author, b.age_limit, b.price_per_week, b.rented);
        }
    }
    fclose(file),
    fclose(tempFile);
    // file management: Update the system with the new book list
    if(!found){
        printf("Error: Book with ıd %D NOT FOUND! \n" , bID);
        remove("temp_books.txt");//Delete the temp file, no changes neede
    }else if(isRented){
        printf("Error: Cannot burn the book because it is currently rented! \n"),
        remove("temp.books.txt");//Discard changes as the operation is invalid
    }else{
        //Finelize the delation by replacing the original file
        remove("books.txt");
        rename("temp_books.txt", "books.txt");
        printf("Success : Book with ID %d has been burmed (removed) from the system. \n", bID);
    }
}

void updateCustomer(){
    int targetID, found = 0;
    printf("\n --- Update Customer Information --- \n");
    printf("Enter customer ID to update : ");
    scanf("%d" , &targetID);
    //Open the source file for reading and a temporary file for the updated verison
    FILE *file = fopen("customers.txt", "r");
    FILE *tempFile = fopen("temp_customers.txt" , "w");

    if(file==NULL || tempFile== NULL){
        printf("Error: File operations failed ! \n");
        return;
    }

    Customer c;
    //Read each customers from the file
    while(fscanf(file, "%d %s %s %d %d" , &c.C_ID, c.name, c.surname, &c.age, &c.wallet) != EOF){
        //If the ID matches, ask the user for new personal details
        if(c.C_ID == targetID){
            found = 1;
            printf("Enter new name : ");
            scanf("%s", c.name);
            printf("Enter new surname : ");
            scanf("%s",c.surname);
            printf("Enter new age : ");
            scanf("%d", &c.age);
            //C_ID and wallet remain unchanged
        }
        //Write the data(either new or original) to the temporary file
        fprintf(tempFile, "%d %s %s %d %d \n", c.C_ID, c.name, c.surname, c.age, c.wallet);
    }
    
    fclose(file);
    fclose(tempFile);
    //Synchorinize files: replace the old database with the updated temporary file
    if (found){
        remove("customers.txt");
        rename("temp_customers.txt", "customers.txt");
        printf("Customer information updated succesfully! \n");
    }else{
        remove("temp_customers.txt");
        printf("Error: Customer with ID %d not found! \n" ,  targetID);
    }
}

void updateBook(){
    int targetID, found= 0 ;
    printf ("\n --- Update book information --- \n"),
    printf("Enter book Id to the update : ");
    scanf("%d", &targetID);

    FILE *file = fopen("books.txt", "r");
    FILE *tempFile = fopen("temp_books.txt", "w");

    if(file == NULL || tempFile == NULL){
        printf("Error: File operations failed ! \n");
        return;
    }

    Book b;
    //Read ever book using the pipe separator
    while(fscanf(file, "%d | %[^|] | %[^|] | %d | %d | %d \n", &b.B_ID, b.name, b.author, &b.age_limit, &b.price_per_week, &b.rented) != EOF){
        if(b.B_ID== targetID){
            found=1;
            //Ask for new book details while keeping the ID and Rental status intact
            printf("Enter new name : ");
            scanf(" %[^\n]s",b.name);
            printf("Enter new author : ");
            scanf(" %[^\n]s", b.author);
            printf("Enter new age limit : ");
            scanf(" %d", &b.age_limit);
            printf("Enter new price per week : ");
            scanf("%d", &b.price_per_week);
            //B_ID and rented status remain unchanged
        }
        //Save the record to the temp file in the standardized format
        fprintf(tempFile, "%d | %s | %s | %d | %d | %d |n", b.B_ID, b.name, b.author, b.age_limit, b.price_per_week, b.rented);
    }
    fclose(file);
    fclose(tempFile);

    if (found){
        remove("books.txt");
        rename("temp_books.txt", "books.txt");
        printf("Book information updated succesfully! \n");
    }else{
        remove("temp_books.txt");
        printf("Error : Book with ID %d not found! \n", targetID);
    }
}

void listRentingCustomers(){
    //Open the rental records file for reading
    FILE *fRent = fopen("rented.txt", "r");
    if(fRent == NULL){
        printf(" \n No active rentals found. \n");
        return;
    }
    Rented r;
    Customer c;
    Book b;
    int foundAny = 0;

    printf("\n --- List of customers who rent a book --- \n");
    //Table header with specific column widths for a clean look
    printf("%-5s | %-20s | %-30s | %-10s \n", "R_ID","Customer name","Book name","weeks");
    printf("------------------------------------------------\n");

    // read the rented.txt files line by line
    while(fscanf(fRent, "%d %d %d %s %d", &r.R_ID, &r.C_ID, &r.B_ID, r.rented_date, &r.week) != EOF){
        foundAny=1;
        char customerFullName[100] ="Unknown";
        char bookTitle[100]="Unknown";

        //for finding customer name opent to the customers.txt
        FILE *fCust = fopen("customers.txt", "r");
        if(fCust){
            while(fscanf(fCust,"%d %s %s %d %d", &c.C_ID, c.name, c.surname, &c.age, &c.wallet) != EOF){
                if(c.C_ID == r.C_ID){
                    sprintf(customerFullName, "%s %s", c.name, c.surname);
                    break;
                }
            }
            fclose(fCust);
        }

        //for finding book name open books.txt
        FILE *fBook = fopen("books.txt", "r");
        if(fBook){
            while (fscanf(fBook, "%d | %[^|] | %[^|] | %d | %d | %d \n", &b.B_ID, b.name, b.author, &b.age_limit, &b.price_per_week, &b.rented) != EOF){
                if(b.B_ID == r.B_ID){
                    strcpy(bookTitle, b.name);
                    break;
                }
            }
            fclose(fBook);
        }
        //Display the synchoronized data from all three files
        printf("%-5d | %-20s | %-30s | %-10d \n", r.R_ID, customerFullName, bookTitle, r.week);

    }
    if(!foundAny){
        printf("No active rentals recorded in the system. \n");
    }
    fclose(fRent);
}

void listCustomers(){
    //Open the customers database file in read mode
    FILE *file= fopen("customers.txt", "r");
    //Check if the file exists or is accesibble
    if(file == NULL){
        printf("\n No customers found or the file 'customers.txt' does not exist. \n");
        return;
    }
    Customer c; 
    int count = 0;

    printf("\n --- List of all customers --- \n");
    //print the table healers in alignment
    printf("%-5s | %-15s | %-15s | %-5s | %-10s \n", "ID", "Name", "Surname", "Age", "Wallet(TL)");
    printf("---------------------------------------------------\n");

    //Read to the file to the end
    while(fscanf(file, "%d %s %s %d %d ", &c.C_ID, c.name, c.surname, &c.age, &c.wallet) != EOF){
        //Print each customer record using the same alignment as the header
        printf("%-5d | %-15s | %-15s | %-5d | %-10d \n", c.C_ID, c.name, c.surname, c.age , c.wallet);
        count++;
    }
    //Inform the user if the file was empty
    if(count==0){
        printf("The customer list is currently empty. \n");
    }else{
        printf("--------------------------------------------------\n");
        printf("Total customers: %d\n", count);
    }
    //Close the file to free system memory
    fclose(file);

}

void listBooks(){
    // Open the book records file in read-only mode
    FILE *file = fopen("books.txt", "r");
    
    // Check if the file exists or can be opened to prevent segmentation faults
    if (file == NULL) {
        printf("\nNo books found or the file 'books.txt' does not exist.\n");
        return;
    }

    Book b;
    int count = 0;

    printf("\n--- List of All Books ---\n");
    // Table headers with precise column formatting for aligned columns
    printf("%-5s | %-25s | %-20s | %-8s | %-12s | %-10s\n", 
           "ID", "Book Name", "Author", "Age L.", "Price/Week", "Status");
    printf("--------------------------------------------------------------------------------------------\n");

    // CRITICAL: The leading space before %d (" %d") is vital. 
    // It skips any leftover whitespaces, tabs, or newline characters (\n) from previous inputs,
    // which completely prevents the program from getting stuck in an infinite loop.
    while (fscanf(file, " %d | %[^|] | %[^|] | %d | %d | %d\n", 
           &b.B_ID, b.name, b.author, &b.age_limit, &b.price_per_week, &b.rented) != EOF) {
        
        // Ternary operator converts numeric status (1 or 0) into human-readable text
        printf("%-5d | %-25s | %-20s | %-8d | %-12d | %-10s\n", 
               b.B_ID, 
               b.name, 
               b.author, 
               b.age_limit, 
               b.price_per_week, 
               (b.rented == 1 ? "Rented" : "Available"));
        count++;
    }

    // Inform the user about the total results found
    if (count == 0) {
        printf("The library collection is currently empty.\n");
    } else {
        printf("--------------------------------------------------------------------------------------------\n");
        printf("Total Books in Library: %d\n", count);
    }

    // Always close the file to release system resources
    fclose(file);
}

void searchBook() {
    FILE *file = fopen("books.txt", "r");
    if (file == NULL) {
        printf("\nNo books found to search.\n");
        return;
    }

    int searchType;
    char searchTerm[100];
    int searchAge;
    int found = 0;
    Book b;

    // Sub-menu for searching by different criteria as requested in the project specs
    printf("\n--- Search Book ---\n");
    printf("1. Search by Name\n");
    printf("2. Search by Author\n");
    printf("3. Search by Age Limit\n");
    printf("Select search type: ");
    scanf("%d", &searchType);

    // Handle different input types based on user selection
    if (searchType == 1 || searchType == 2) {
        printf("Enter search term: ");
        scanf(" %[^\n]s", searchTerm); // Read string with spaces
    } else if (searchType == 3) {
        printf("Enter age limit: ");
        scanf("%d", &searchAge);
    } else {
        printf("Invalid search type selected!\n");
        fclose(file);
        return;
    }

    printf("\n--- Search Results ---\n");
    printf("%-5s | %-25s | %-20s | %-8s | %-12s | %-10s\n", 
           "ID", "Book Name", "Author", "Age L.", "Price/Week", "Status");
    printf("--------------------------------------------------------------------------------------------\n");

    // Scan all books and compare them against the search criteria
    while (fscanf(file, "%d | %[^|] | %[^|] | %d | %d | %d\n", 
           &b.B_ID, b.name, b.author, &b.age_limit, &b.price_per_week, &b.rented) != EOF) {
        
        int match = 0;
        // Use 'strstr' for string matching (checks if search term is part of the name/author)
        if (searchType == 1 && strstr(b.name, searchTerm) != NULL) match = 1;
        else if (searchType == 2 && strstr(b.author, searchTerm) != NULL) match = 1;
        else if (searchType == 3 && b.age_limit == searchAge) match = 1;

        if (match) {
            printf("%-5d | %-25s | %-20s | %-8d | %-12d | %-10s\n", 
                   b.B_ID, b.name, b.author, b.age_limit, b.price_per_week, 
                   (b.rented == 1 ? "Rented" : "Available"));
            found = 1;
        }
    }

    if (!found) {
        printf("No records found matching your search term.\n");
    }

    fclose(file);
}
//Main Function

int main(){
    int choice;

    while(1){
        menu();
        printf("Please choose your operation : ");
        scanf("%d" , &choice);

        switch(choice){
            case 1 : createCustomer();
            break;
            case 2 : depositMoney();
            break;
            case 3 : addNewBook();
            break;
            case 4 : rentBook();
            break;
            case 5 : deliveryBook();
            break;
            case 6 : burnBook();
            break;
            case 7 : updateCustomer();
            break;
            case 8 : updateBook();
            break;
            case 9 : listRentingCustomers();
            break;
            case 10 : listCustomers();
            break;
            case 11 : listBooks();
            break;
            case 12 : searchBook();
            break;
            case 0 : exit(0);
            default : printf("Invalid selection!!! \n");
        }
    }
    return 0;
}