#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
typedef struct Product
{
    int category;
    int product_id;
    char name[50];
    int seller_id;
    int stock;
    float price;
    float reviews;
    int total_sold;
    int number_of_reviews;
    int delivery_status;
    struct Product *next;
} product;
typedef struct Checkout
{
    int product_id;
    int amount;
    float price;
} checkout;
typedef struct Customer
{
    int customer_id;
    char name[50];
    char password[50];
    float balance;
    checkout check_out_items[50];
    int index;
    struct Customer *next;
} customer;
typedef struct seller_items
{
    int product_id;
    int stock;
    float price;
} seller_item;
typedef struct Seller
{
    int seller_id;
    char name[50];
    char pass[50];
    seller_item item_data[50];
    int index;
    seller_item undelivered[50];
    int undelivered_index;
    struct Seller *next;
} seller;
int seller_ID = 0;
int customer_ID = 0;
product *ptr;
customer *head;
seller *pointer;
int customer_logged_in = 0;
int seller_logged_in = 0;

const char *categories[] =
    {
        "Electronics",
        "Books",
        "Clothing",
        "Home & Kitchen",
        "Sports & Outdoors",
        "Toys & Games",
        "Automotive",
        "Beauty & Personal Care",
        "Health & Household",
        "Grocery & Gourmet Food",
        "Pet Supplies",
        "Office Products",
        "Garden & Outdoor",
        "Tools & Home Improvement",
        "Musical Instruments",
        "Baby",
        "Arts, Crafts & Sewing",
        "Industrial & Scientific",
        "Luggage & Travel Gear",
        "Jewelry"};
///////////////////Function Declarations////////
void clear();
int id_generator();
void pause();
void save_product_data();
void populate_product_data();
void save_seller_data();
void populate_seller_data();
void save_customer_data();
void populate_customer_data();
void popular_item();
void front_display();
void search_by_categories();
void customer_portal_display();
void customer_sign_up();
void customer_sign_in();
void seller_login_portal();
void seller_sign_up();
void seller_signin();
void customer_front_display();
void balance();
void give_reviews();
void my_cart();
int deliver_status(int id);
void product_name(int id);
void seller_front_display();
void delivery_products();
void add_products();
void my_items();
void search_items();
void buy_item(int product_id);
int check_seller_username(char *str);
int check_customer_username(char *str);
//////////////////
void clear()
{
    system("cls");
}
int id_generator()
{
    srand(time(NULL));
    int random_id = rand() % 9000 + 1000;
    return random_id;
}
void pause()
{
    fflush(stdin);
    printf("\nPress Enter To continue.....");
    getchar();
}
void save_product_data()
{
    FILE *file = fopen("product_data.bin", "wb");
    if (file == NULL)
    {
        printf("Error opening product data file.\n");
        return;
    }

    product *current_product = ptr->next;
    while (current_product != NULL)
    {
        fwrite(current_product, sizeof(product), 1, file);
        current_product = current_product->next;
    }

    fclose(file);
}
void populate_product_data()
{
    FILE *file = fopen("product_data.bin", "rb");
    if (file == NULL)
    {
        printf("Error opening product data file.\n");
        return;
    }

    product *new_customer = (product *)malloc(sizeof(product));
    product *temp = ptr;
    while (fread(new_customer, sizeof(product), 1, file))
    {
        temp->next = (product *)malloc(sizeof(product));
        temp = temp->next;
        memcpy(temp, new_customer, sizeof(product));
        temp->next = NULL;
    }

    fclose(file);
}
void save_seller_data()
{
    FILE *file = fopen("seller_data.bin", "wb");
    if (file == NULL)
    {
        printf("Error opening seller data file.\n");
        return;
    }

    seller *current_seller = pointer->next;
    while (current_seller != NULL)
    {
        fwrite(current_seller, sizeof(seller), 1, file);
        current_seller = current_seller->next;
    }

    fclose(file);
}
void populate_seller_data()
{
    FILE *file = fopen("seller_data.bin", "rb");
    if (file == NULL)
    {
        printf("Error opening seller data file.\n");
        return;
    }

    seller *new_customer = (seller *)malloc(sizeof(seller));
    seller *temp = pointer;
    while (fread(new_customer, sizeof(seller), 1, file))
    {
        temp->next = (seller *)malloc(sizeof(seller));
        temp = temp->next;
        memcpy(temp, new_customer, sizeof(seller));
        temp->next = NULL;
    }

    fclose(file);
}
void save_customer_data()
{
    FILE *file = fopen("customer_data.bin", "wb");
    if (file == NULL)
    {
        printf("Error opening customer data file.\n");
        return;
    }

    customer *current_customer = head->next;
    while (current_customer != NULL)
    {
        fwrite(current_customer, sizeof(customer), 1, file);
        current_customer = current_customer->next;
    }

    fclose(file);
}
void populate_customer_data()
{
    FILE *file = fopen("customer_data.bin", "rb");
    if (file == NULL)
    {
        printf("Error opening customer data file.\n");
        return;
    }
    customer *new_customer = (customer *)malloc(sizeof(customer));
    customer *temp = head;
    while (fread(new_customer, sizeof(customer), 1, file))
    {
        temp->next = (customer *)malloc(sizeof(customer));
        temp = temp->next;
        memcpy(temp, new_customer, sizeof(customer));
        temp->next = NULL;
    }

    fclose(file);
}
int main()
{
    // Initialize ptr, head, and pointer with dynamic memory allocation
    ptr = (product *)malloc(sizeof(product));
    ptr->next = NULL;

    head = (customer *)malloc(sizeof(customer));
    head->next = NULL;

    pointer = (seller *)malloc(sizeof(seller));
    pointer->next = NULL;

    populate_customer_data();
    populate_product_data();
    populate_seller_data();
    front_display();
}
void popular_item()
{
    clear();
    product *temp = ptr;
    temp = temp->next;
    int arr[1000] = {0};
    int i = 0;
    while (temp != NULL)
    {
        if (temp->number_of_reviews > 0)
        {
            if (temp->reviews / temp->number_of_reviews >= 4)
            {
                printf("+----------------------+--------------------------+\n");
                printf("| %-20s | %-24s |\n", "Item Number", "Item Name");
                printf("+----------------------+--------------------------+\n");
                printf("| %-20d | %-24s |\n", i + 1, temp->name);
                printf("+----------------------+--------------------------+\n");
                printf("| %-20s | %-24s |\n", "Review", "Average Rating");
                printf("+----------------------+--------------------------+\n");
                printf("| %-20s | %-24.1f |\n", " ", temp->reviews / temp->number_of_reviews);
                printf("+----------------------+--------------------------+\n");
                arr[i++] = temp->product_id;
            }
        }
        temp = temp->next;
    }
    if (customer_logged_in)
    {
        if (i)
        {
            printf("+--------------------------+\n");
            printf("|   Choose to buy:         |\n");
            printf("+--------------------------+\n");

            int chh;
            scanf(" %d", &chh);
            buy_item(arr[chh - 1]);
        }
        printf("+-----------------------+\n");
        printf("|     No Items Found    |\n");
        printf("+-----------------------+\n");
        pause();
        customer_front_display();
    }
    if (i == 0)
    {
        printf("+-----------------------+\n");
        printf("|     No Items Found    |\n");
        printf("+-----------------------+\n");
    }
    pause();
    front_display();
}
void front_display()
{
    clear();
    printf("+------------------------+\n");
    printf("| 1. See Popular Items   |\n");
    printf("+------------------------+\n");
    printf("| 2. Search Items        |\n");
    printf("+------------------------+\n");
    printf("| 3. Categories          |\n");
    printf("+------------------------+\n");
    printf("| 4. Customer Portal     |\n");
    printf("+------------------------+\n");
    printf("| 5. Seller Portal       |\n");
    printf("+------------------------+\n");
    printf("| >>");
    int ch;
    scanf(" %d", &ch);
    switch (ch)
    {
    case 1:
        popular_item();
        break;
    case 2:
        search_items();
        break;
    case 3:
        search_by_categories();
        break;
    case 4:
        customer_portal_display();
        break;
    case 5:
        seller_login_portal();
        break;
    default:
        front_display();
        break;
    }
}
void search_by_categories()
{
    clear();
    for (int i = 0; i < 20; i++)
    {
        printf("[%d] %s\n", i + 1, categories[i]);
    }
    int ch;
    printf("\n+-----------------------+\n");
    printf("| Choose a category:    |\n");
    printf("+-----------------------+\n");
    printf(">>");
    scanf(" %d", &ch);
    product *item = ptr;
    int arr[1000] = {0};
    int i = 0;
    while (item != NULL)
    {
        if (ch == item->category)
        {
            printf("[%d] Item Name : %s \n", i + 1, item->name);
            arr[i++] = item->product_id;
        }
        item = item->next;
    }

    if (customer_logged_in)
    {
        if (i != 0)
        {
            printf("+-------------------+\n");
            printf("| Choose to buy:    |\n");
            printf("+-------------------+\n");
            printf(">>");
            int chh;
            scanf(" %d", &chh);
            buy_item(arr[chh - 1]);
        }
        pause();
        customer_front_display();
    }
    pause();
    front_display();
}
void customer_portal_display()
{
    clear();
    printf("+-------------------+\n");
    printf("|   Customer Portal |\n");
    printf("+-------------------+\n");
    printf("| [1] Sign_up       |\n");
    printf("+-------------------+\n");
    printf("| [2] Sign In       |\n");
    printf("+-------------------+\n");
    printf("| [3] Return to Main|\n");
    printf("+-------------------+\n");
    printf("| >>");
    int ch;
    fflush(stdin);
    scanf(" %d", &ch);
    fflush(stdin);
    switch (ch)
    {
    case 1:
        customer_sign_up();
        break;
    case 2:
        customer_sign_in();
        break;
    case 3:
        front_display();
        break;
    default:
        front_display();
        break;
    }
}
void customer_sign_up()
{
    clear();
    customer *temp = head;

    // Traverse to the end of the linked list
    while (temp->next != NULL)
    {
        temp = temp->next;
    }

    // Allocate memory for the new customer
    temp->next = (customer *)malloc(sizeof(customer));
    temp = temp->next;
    temp->next = NULL;

    // Prompt the user for the username
    printf("+-------------------+\n");
    printf("|   Username:       |\n");
    printf("+-------------------+\n>>");
    scanf(" %[^\n]s", temp->name); // Assuming temp->name is a character array for storing the username
    if (check_customer_username(temp->name))
    {
        printf("+---------------------+\n");
        printf("| User Already Exists |\n");
        printf("+---------------------+\n");
        pause();
        customer_portal_display();
    }
    printf("+-------------------+\n");
    printf("|   Password:       |\n");
    printf("+-------------------+\n>>");
    scanf(" %s", temp->password); // Assuming temp->password is a character array for storing the password

    // Generate a unique customer ID
    temp->customer_id = id_generator();
    temp->balance = 1000;
    temp->index = 0;
    save_customer_data();
    printf("+----------------------------+\n");
    printf("| Successfully registered    |\n");
    printf("+----------------------------+\n");

    pause();
    customer_portal_display();
}
int check_customer_username(char *str)
{
    customer *temp = head->next; // Assuming head points to the first node
    while (temp->next != NULL)
    {
        if (strcmp(temp->name, str) == 0)
        {
            return 1; // Username exists
        }
        temp = temp->next;
    }
    return 0; // Username doesn't exist
}

int check_seller_username(char *str)
{
    seller *temp = pointer;
    temp = temp->next;
    while (temp->next != NULL)
    {
        if (strcmp(temp->name, str) == 0)
        {
            return 1;
        }
        temp = temp->next;
    }
    return 0;
}
void customer_sign_in()
{
    clear();
    char username[20];
    char pass[20];
    printf("+-------------------+\n");
    printf("| Enter Username:  |\n");
    printf("+-------------------+\n>>");
    scanf(" %[^\n]s", username);

    printf("+-------------------+\n");
    printf("| Enter Password:  |\n");
    printf("+-------------------+\n>>");
    scanf(" %[^\n]s", pass);

    customer *temp = head;
    int found = 0;
    while (temp != NULL)
    {
        if (strcmp(temp->name, username) == 0 && strcmp(temp->password, pass) == 0)
        {
            found = 1;
            break;
        }
        temp = temp->next;
    }
    if (found)
    {
        printf("+------------------------+\n");
        printf("| Logged In Successfully |\n");
        printf("+------------------------+\n");

        customer_ID = temp->customer_id;
        customer_logged_in = 1;
        pause();
        customer_front_display();
    }
    else
    {
        printf("Invalid Inputs\n");
    }
    pause();
    customer_portal_display();
}
void seller_login_portal()
{
    clear();
    printf("+-------------------+\n");
    printf("|   Seller Portal   |\n");
    printf("+-------------------+\n");
    printf("| [1] SignUp        |\n");
    printf("+-------------------+\n");
    printf("| [2] Sign In       |\n");
    printf("+-------------------+\n");
    printf("| [3] Back to Main  |\n");
    printf("+-------------------+\n>>");

    int ch;
    scanf("%d", &ch);
    switch (ch)
    {
    case 1:
        seller_sign_up();
        break;
    case 2:
        seller_signin();
        break;
    case 3:
        front_display();
        break;
    default:
        front_display();
        break;
    }
}
void seller_sign_up()
{
    clear();
    seller *temps = pointer;
    while (temps->next != NULL)
    {
        temps = temps->next;
    }
    temps->next = (seller *)malloc(sizeof(seller));
    temps = temps->next;
    temps->next = NULL;
    printf("+-------------------+\n");
    printf("|    UserName:      |\n");
    printf("+-------------------+\n");
    scanf(" %[^\n]s", temps->name); // Assuming temps->name is a character array for storing the username
    if (check_seller_username(temps->name) == 1)
    {
        printf("+---------------------+\n");
        printf("| User Already Exists |\n");
        printf("+---------------------+\n");
        pause();
        seller_login_portal();
    }
    printf("+-------------------+\n");
    printf("|    Password:      |\n");
    printf("+-------------------+\n");
    scanf(" %[^\n]s", temps->pass); // Assuming temps->pass is a character array for storing the password

    temps->seller_id = id_generator();
    temps->undelivered_index = 0;
    temps->index = 0;
    save_seller_data();
    printf("SuccessFully Registered\n");
    pause();
    seller_login_portal();
}
void seller_signin()
{
    clear();
    char username[20];
    char pass[20];
    printf("+-------------------+\n");
    printf("| Enter Username:  |\n");
    printf("+-------------------+\n>>");
    scanf(" %[^\n]s", username);

    printf("+-------------------+\n");
    printf("| Enter Password:  |\n");
    printf("+-------------------+\n>>");
    scanf(" %[^\n]s", pass);

    seller *temps = pointer;
    int found = 0;
    while (temps != NULL)
    {
        if (strcmp(temps->name, username) == 0 && strcmp(temps->pass, pass) == 0)
        {
            found = 1;
            seller_logged_in = 1;
            seller_ID = temps->seller_id;
            break;
        }
        temps = temps->next;
    }
    if (found)
    {
        printf("+------------------------+\n");
        printf("| Logged In Successfully |\n");
        printf("+------------------------+\n");

        pause();
        seller_front_display();
    }
    else
    {
        printf("+-------------------+\n");
        printf("| Invalid Inputs    |\n");
        printf("+-------------------+\n");
    }
    pause();
    seller_login_portal();
}
void customer_front_display()
{
    clear();
    printf("+--------------------------+\n");
    printf("| [1] Popular Items To Buy |\n");
    printf("+--------------------------+\n");
    printf("| [2] Search Items         |\n");
    printf("+--------------------------+\n");
    printf("| [3] Categories           |\n");
    printf("+--------------------------+\n");
    printf("| [4] My Cart              |\n");
    printf("+--------------------------+\n");
    printf("| [5] Give Reviews         |\n");
    printf("+--------------------------+\n");
    printf("| [6] My Balance           |\n");
    printf("+--------------------------+\n");
    printf("| [7] Logout               |\n");
    printf("+--------------------------+\n>>");
    int ch;
    scanf(" %d", &ch);
    switch (ch)
    {
    case 1:
        popular_item();
        break;
    case 2:
        search_items();
        break;
    case 3:
        search_by_categories();
        break;
    case 4:
        my_cart();
        break;
    case 5:
        give_reviews();
        break;
    case 6:
        balance();
        break;
    case 7:
        customer_logged_in = 0;
        customer_ID = 0;
        front_display();
        break;
    default:
        customer_front_display();
        break;
    }
}
void balance()
{
    clear();

    customer *temp = head;
    while (temp != NULL)
    {
        if (customer_ID == temp->customer_id)
        {
            printf("+-------------------+\n");
            printf("| Your Balance is: %.2f BDT\n", temp->balance);
            printf("+-------------------+\n");
            break;
        }
        temp = temp->next;
    }
    printf("+-----------------------+\n");
    printf("| [1] Add Balance       |\n");
    printf("+-----------------------+\n");
    printf("| [2] Return            |\n");
    printf("+-----------------------+\n>>");

    int ch;
    scanf(" %d", &ch);
    if (ch != 1)
    {
        pause();
        customer_front_display();
    }
    printf("+------------+\n");
    printf("| Add :      |\n");
    printf("+------------+\n>>");

    float add;
    scanf(" %f", &add);
    temp->balance += add;
    save_customer_data();
    printf("+--------------------------+\n");
    printf("| New Balance: %.2f         |\n", temp->balance);
    printf("+--------------------------+\n");
    pause();
    customer_front_display();
}
void give_reviews()
{
    clear();
    printf("+------------------+\n");
    printf("| Delivered Products |\n");
    printf("+------------------+\n");

    product *temp = ptr;
    customer *tempc = head;
    while (tempc != NULL)
    {
        if (tempc->customer_id == customer_ID)
        {
            break;
        }
        tempc = tempc->next;
    }
    int found = 0;
    while (temp != NULL && tempc != NULL)
    {
        for (int i = 0; i < tempc->index; i++)
        {
            if (deliver_status(tempc->check_out_items[i].product_id) && tempc->check_out_items[i].product_id == temp->product_id)
            {
                found = 1;
                printf("+-----------------------+\n");
                printf("| Item Name: %s|\n", temp->name);
                printf("+-----------------------+\n");
                printf("| [1] Give Review       |\n");
                printf("+-----------------------+\n");
                printf("| [2] Return            |\n");
                printf("+-----------------------+\n>>");

                int ch;
                scanf(" %d", &ch);
                if (ch != 1)
                {
                    pause();
                    customer_front_display();
                }
                printf("+---------------------------+\n");
                printf("| Enter A rating from 1 to 5 |\n");
                printf("+---------------------------+\n");
                float review;;
                scanf(" %f", &review);
                temp->reviews+=review;
                temp->number_of_reviews += 1;
                save_product_data();
            }
        }
        temp = temp->next;
    }
    if (!found)
    {
        printf("+-------------------+\n");
        printf("| No items to review|\n");
        printf("+-------------------+\n");
    }
    pause();
    customer_front_display();
}
void my_cart()
{
    clear();
    customer *temp = head;
    while (temp != NULL)
    {
        if (temp->customer_id == customer_ID)
        {
            break;
        }
        temp = temp->next;
    }
    if (temp->index != 0)
    {
        printf("Ordered Items:\n");
        for (int i = 0; i < temp->index; i++)
        {
            printf("+-------------------+\n");
            printf("| Product Name:");
            product_name(temp->check_out_items[i].product_id);
            printf("+-------------------+\n");

            printf("+-------------------+\n");
            printf("| Item Price: %.2f  |\n", temp->check_out_items[i].price);

            printf("+-------------------+\n");
            printf("| Amount: %d       |\n", temp->check_out_items[i].amount);
            printf("+-------------------+\n");
            printf("| Delivery Status: ");

            if (deliver_status(temp->check_out_items[i].product_id))
            {
                printf("Delivered\n");
            }
            else
            {
                printf("Undelivered\n");
            }
            printf("+-------------------+\n");
        }
    }
    else
    {
        printf("+---------------+\n");
        printf("| CART EMPTY    |\n");
        printf("+---------------+\n");
    }
    pause();
    customer_front_display();
}
int deliver_status(int id)
{
    product *temp = ptr;
    while (temp != NULL)
    {
        if (id == temp->product_id && temp->delivery_status == 1)
        {
            return 1;
        }
        temp = temp->next;
    }
    return 0;
}
void product_name(int id)
{
    product *temp = ptr;
    while (temp != NULL)
    {
        if (id == temp->product_id)
        {
            printf("%s\n", temp->name);
            break;
        }
        temp = temp->next;
    }
    return;
}
void seller_front_display()
{
    clear();
    printf("+---------------------------+\n");
    printf("| [1] Add Items For Sell    |\n");
    printf("+---------------------------+\n");
    printf("| [2] Search Items           |\n");
    printf("+---------------------------+\n");
    printf("| [3] My Items               |\n");
    printf("+---------------------------+\n");
    printf("| [4] Undelivered Products  |\n");
    printf("+---------------------------+\n");
    printf("| [5] Logout                 |\n");
    printf("+---------------------------+\n>>");

    int ch;
    scanf(" %d", &ch);
    switch (ch)
    {
    case 1:
        add_products();
        break;
    case 2:
        search_items();
        break;
    case 3:
        my_items();
        break;
    case 4:
        delivery_products();
        break;
    case 5:
        seller_ID = 0;
        seller_logged_in = 0;
        front_display();
        break;
    default:
        seller_front_display();
        break;
    }
}
void delivery_products()
{
    clear();
    product *temp = ptr;
    product *temp2 = ptr;
    printf("+---------------------------+\n");
    printf("| My Undelivered Products: |\n");
    printf("+---------------------------+\n");

    int i = 1;
    while (temp != NULL)
    {
        if (temp->seller_id == seller_ID && temp->delivery_status == 0 && temp->total_sold > 0)
        {
            printf("[%d] Item Name: %s\n", i++, temp->name);
        }
        temp = temp->next;
    }
    if (i == 1)
    {
        printf("+-----------------------------------+\n");
        printf("| There's No Undelivered Products  |\n");
        printf("+-----------------------------------+\n");

        pause();
        seller_front_display();
    }
    printf("+--------------------------+\n");
    printf("| [1] Delivery ALL         |\n");
    printf("+--------------------------+\n");
    printf("| [2] Return               |\n");
    printf("+--------------------------+\n");
    printf("| >>");

    int ch;
    scanf(" %d", &ch);
    if (ch != 1)
    {
        pause();
        seller_front_display();
    }
    while (temp2 != NULL)
    {
        if (temp2->seller_id == seller_ID && temp2->delivery_status == 0)
        {
            temp2->delivery_status = 1;
        }
        temp2 = temp2->next;
    }
    printf("+---------------------------+\n");
    printf("| Delivered Successfully   |\n");
    printf("+---------------------------+\n");

    save_product_data();
    pause();
    seller_front_display();
}
void add_products()
{
    clear();
    product *temp = ptr;
    while (temp->next != NULL)
    {
        temp = temp->next;
    }
    temp->next = (product *)malloc(sizeof(product));
    temp = temp->next;
    for (int i = 0; i < 20; i++)
    {
        printf("[%d] %s\n", i + 1, categories[i]);
    }
    printf("+-------------------------------+\n");
    printf("| Choose Category:\n");
    scanf(" %d", &temp->category);
    printf("+-------------------------------+\n");

    printf("+-------------------------------+\n");
    printf("| Name Of Product:");
    scanf(" %[^\n]s", temp->name);
    printf("+-------------------------------+\n");

    printf("+-------------------------------+\n");
    printf("| Unit Price:");
    scanf(" %f", &temp->price);
    printf("+-------------------------------+\n");

    printf("+-------------------------------+\n");
    printf("| Total Stock:");
    scanf(" %d", &temp->stock);
    printf("+-------------------------------+\n");

    printf("+-------------------------------+\n");
    printf("| Added Successfully           |\n");
    printf("+-------------------------------+\n");

    temp->product_id = id_generator();
    temp->seller_id = seller_ID;
    temp->next = NULL;
    temp->delivery_status = 0;
    temp->number_of_reviews = 0;
    temp->total_sold = 0;
    save_product_data();
    pause();
    seller_front_display();
}
void my_items()
{
    product *items = ptr;

    int i = 1;

    while (items != NULL)
    {
        if (items->seller_id == seller_ID)
        {
            printf("\n+----------------------+\n");
            printf("| [%d] Item             \n", i++);
            printf("+----------------------+\n");
            printf("| Name: %s             \n", items->name);
            printf("+----------------------+\n");
            printf("| Price: %.2f BDT\n", items->price);
            printf("+----------------------+\n");
            printf("| In Stock: %d          \n", items->stock);
            printf("+----------------------+\n");
            printf("| Total Sold: %d        \n", items->total_sold);
            printf("+----------------------+\n");
        }
        items = items->next;
    }
    if (i == 1)
    {
        printf("+----------------------+\n");
        printf("| NO ITEM FOUND        |\n");
        printf("+----------------------+\n");
    }
    pause();
    seller_front_display();
}
void search_items()
{
    clear();
    char name[20];
    printf("+--------------------------+\n");
    printf("| Enter Product Name:      |\n");
    printf("+--------------------------+\n>>");
    scanf(" %[^\n]s", name);
    product *tempp = ptr;
    int found = 0;
    while (tempp != NULL)
    {
        if (strcmp(tempp->name, name) == 0)
        {
            printf("+-------------------+\n");
            printf("| Found             |\n");
            printf("+-------------------+\n");
            printf("| Product Name: %s \n", tempp->name);
            printf("+-------------------+\n");
            printf("| Product Price: %.f BDT\n", tempp->price);
            printf("+-------------------+\n");
            printf("| Product Stock: %d  \n", tempp->stock);
            printf("+-------------------+\n");

            found = 1;
            break;
        }
        tempp = tempp->next;
    }

    if (!found)
    {
        printf("+----------------------+\n");
        printf("| Product Not Found    |\n");
        printf("+----------------------+\n");
    }
    if (!customer_logged_in && seller_logged_in)
    {
        pause();
        seller_front_display();
    }
    else if (!customer_logged_in && !seller_logged_in)
    {
        pause();
        front_display();
    }
    printf("+----------------------+\n");
    printf("| [1] Buy Item         |\n");
    printf("+----------------------+\n");
    printf("| [2] Return           |\n");
    printf("+----------------------+\n>>");

    int ch;
    scanf(" %d", &ch);
    if (ch == 1)
    {
        buy_item(tempp->product_id);
    }
    pause();
    customer_front_display();
}
void buy_item(int product_id)
{
    clear();
    product *temp = ptr;

    while (temp != NULL)
    {
        if (product_id == temp->product_id)
        {
            printf("+----------------------+\n");
            printf("| Selected Product:    |\n");
            printf("+----------------------+\n");
            printf("| Product name: %s     \n", temp->name);
            printf("+----------------------+\n");
            printf("| Product Price: %.2f BDT \n", temp->price);
            printf("+----------------------+\n");

            break;
        }
        temp = temp->next;
    }
    printf("+-------------------------------+\n");
    printf("| How Many do you want to buy: |\n");
    printf("+-------------------------------+\n>>");

    int amount;
    scanf(" %d", &amount);
    printf("+-------------------------+\n");
    printf("| Total Amount: %.2f BDT \n", temp->price * amount);
    printf("+-------------------------+\n");
    printf("| [1] Confirm             |\n");
    printf("+-------------------------+\n");
    printf("| [2] GO back             |\n");
    printf("+-------------------------+\n>>");

    int ch;
    scanf(" %d", &ch);
    if (ch != 1)
    {
        pause();
        customer_front_display();
    }
    temp->stock -= amount;
    if(temp->stock<0)
    {
        temp->stock+=amount;
        printf("Not Emough Stock\n");
        pause();
        customer_front_display();
    }
    temp->total_sold += amount;
    temp->delivery_status = 0;

    customer *tempc = head;
    while (tempc != NULL)
    {
        if (customer_ID == tempc->customer_id)
        {
            tempc->check_out_items[tempc->index].product_id = temp->product_id;
            tempc->check_out_items[tempc->index].amount = amount;
            tempc->check_out_items[tempc->index].price = temp->price;
            tempc->balance -= amount * temp->price;
            if (tempc->balance < 0)
            {
                tempc->balance+=amount*temp->price;
                printf("+-------------------+\n");
                printf("| Not Enough Balance|\n");
                printf("+-------------------+\n");

                pause();
                customer_front_display();
            }
            
            tempc->index += 1;
            break;
        }
        tempc = tempc->next;
    }
    save_product_data();
    save_customer_data();
    pause();
    customer_front_display();
}
