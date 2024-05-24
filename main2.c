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
    printf("\nPress Enter To continue.....\n");
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

    while (fread(ptr, sizeof(product), 1, file))
    {
        product *new_product = (product *)malloc(sizeof(product));
        memcpy(new_product, ptr, sizeof(product));
        new_product->next = ptr->next;
        ptr->next = new_product;
        ptr = new_product;
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

    while (fread(pointer, sizeof(seller), 1, file))
    {
        seller *new_seller = (seller *)malloc(sizeof(seller));
        memcpy(new_seller, pointer, sizeof(seller));
        new_seller->next = pointer->next;
        pointer->next = new_seller;
        pointer = new_seller;
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

    while (fread(head, sizeof(customer), 1, file))
    {
        customer *new_customer = (customer *)malloc(sizeof(customer));
        memcpy(new_customer, head, sizeof(customer));
        new_customer->next = head->next;
        head->next = new_customer;
        head = new_customer;
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
        if (temp->number_of_reviews != 0)
        {
            if (temp->reviews / temp->number_of_reviews >= 4)
            {
                printf("[%d] Item Name: %s\n", i + 1, temp->name);
                printf("Review: %.1f\n", temp->reviews / temp->number_of_reviews);
                arr[i++] = temp->product_id;
            }
        }
        temp = temp->next;
    }
    if (customer_logged_in)
    {
        printf("Choose to buy: ");
        int chh;
        scanf(" %d", &chh);
        buy_item(arr[chh - 1]);
    }
    if (i == 0)
    {
        printf("No Items Found\n");
    }
    pause();
    front_display();
}
void front_display()
{
    clear();
    printf("1. See Popular Items\n");
    printf("2. Search Items\n");
    printf("3. Categories\n");
    printf("4. Customer Portal\n");
    printf("5. Seller Portal\n");
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
    printf("\nChoose a category:");
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
        printf("Choose to buy: ");
        int chh;
        scanf(" %d", &chh);
        buy_item(arr[chh - 1]);
    }
    pause();
    front_display();
}
void customer_portal_display()
{
    clear();
    printf("Customer Portal\n");
    printf("[1] Sign_up\n");
    printf("[2] Sign In\n");
    printf("[3] Return TO main\n");
    int ch;
    scanf(" %d", &ch);
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

    // Prompt the user for the username
    printf("Username: ");
    scanf(" %[^\n]s", temp->name);
    printf("Password: ");
    scanf(" %s[^\n]", temp->password);

    // Generate a unique customer ID
    temp->customer_id = id_generator();

    temp->next = NULL;
    temp->balance = 1000;
    temp->index = 0;
    save_customer_data();
    printf("Successfully registered\n");
    pause();
    customer_portal_display();
}
void customer_sign_in()
{
    clear();
    char username[20];
    char pass[20];
    printf("Enter Username:");
    scanf(" %[^\n]s", username);
    printf("Enter Password: ");
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
        printf("Logged In Succesfully\n");
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
    printf("Seller Portal\n");
    printf("[1]SignUp\n");
    printf("[2] Sign In\n");
    printf("[3] Back TO Main\n");
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
    printf("UserName: ");
    scanf(" %[^\n]s", temps->name);
    printf("Password: ");
    scanf(" %s[^\n]", temps->pass);
    temps->next = NULL;
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
    printf("Enter Username:");
    scanf(" %[^\n]s", username);
    printf("Enter Password: ");
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
        printf("Logged In Succesfully\n");
        pause();
        seller_front_display();
    }
    else
    {
        printf("Invalid Inputs\n");
    }
    pause();
    seller_login_portal();
}
void customer_front_display()
{
    clear();
    printf("[1] Populer Items To Buy\n");
    printf("[2] Search Items\n");
    printf("[3] Categories\n");
    printf("[4] My Cart\n");
    printf("[5] Give Reviews\n");
    printf("[6] My Balance\n");
    printf("[7] Logout\n");
    int ch;
    scanf(" %d", &ch);
    switch (ch)
    {
    case 1:
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
        break;
    }
}
void balance()
{
    clear();
    printf("Your Balance is:");
    customer *temp = head;
    while (temp != NULL)
    {
        if (customer_ID == temp->customer_id)
        {
            printf("%.2f\n", temp->balance);
            break;
        }
        temp = temp->next;
    }
    printf("[1]Add Balance [2]Return\n");
    int ch;
    scanf(" %d", &ch);
    if (ch != 1)
    {
        pause();
        customer_front_display();
    }
    printf("Add : ");
    float add;
    scanf(" %f", &add);
    temp->balance += add;
    save_customer_data();
    printf("New Balance: %.2f\n", temp->balance);
    pause();
    customer_front_display();
}
void give_reviews()
{
    clear();
    printf("Delivered Products:\n");
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
    while (temp != NULL&&tempc!=NULL)
    {
        for (int i = 0; i < tempc->index; i++)
        {
            if (deliver_status(tempc->check_out_items[i].product_id) && tempc->check_out_items[i].product_id == temp->product_id)
            {
                found = 1;
                printf("[1] Give Review  [2] Return\n");
                int ch;
                scanf(" %d", &ch);
                if (ch != 1)
                {
                    pause();
                    customer_front_display();
                }
                printf("Enter A rating from 1 to 5 :");
                scanf(" %f", &temp->reviews);
                temp->number_of_reviews += 1;
                save_product_data();
            }
        }
        temp=temp->next;
    }
    if (!found)
    {
        printf("No items to review\n");
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
            product_name(temp->check_out_items[i].product_id);
            printf("Item Price: %.2f\n", temp->check_out_items[i].price);
            printf("Amount: %d\n", temp->check_out_items[i].amount);
            printf("Delivery Status: ");
            if (deliver_status(temp->check_out_items[i].product_id))
            {
                printf("Delivered\n");
            }
            else
            {
                printf("Undelivered\n");
            }
        }
    }
    else
    {
        printf("CART EMPTY");
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
    printf("[1] Add Items For Sell\n");
    printf("[2] Search Items\n");
    printf("[3] My Items\n");
    printf("[4] Undelivered Products\n");
    printf("[5] Logout\n");
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
    printf("My Undelivered Products:\n");
    int i = 1;
    while (temp != NULL)
    {
        if (temp->seller_id == seller_ID && temp->delivery_status == 0)
        {
            printf("[%d] Item Name: %s\n", i++, temp->name);
        }
        temp = temp->next;
    }
    if (i == 1)
    {
        printf("There's No Undelivered Products\n");
        pause();
        seller_front_display();
    }
    printf("\n[1]Delivery ALL [2] Return\n>>");
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
    printf("Delivered Successfully\n");
    save_product_data();
    pause();
    seller_front_display();
}
void add_products()
{
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
    printf("\nChoose Category: \n");
    scanf(" %d", &temp->category);
    printf("Name Of Poduct: ");
    scanf(" %[^\n]s", temp->name);
    printf("Unit Price: ");
    scanf(" %f", &temp->price);
    printf("Total Stock: ");
    scanf(" %d", &temp->stock);
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
            printf("\n[%d] Item\n", i++);
            printf("Name: %s\n", items->name);
            printf("Price: %.2f\n", items->price);
            printf("In Stock: %d\n", items->stock);
            printf("Total Sold: %d\n", items->total_sold);
        }
        items = items->next;
    }
    if (i == 1)
    {
        printf("NO ITEM FOUND\n");
    }
    pause();
    seller_front_display();
}
void search_items()
{
    char name[20];
    printf("Enter Product Name:");
    scanf(" %[^\n]s", name);
    product *tempp = ptr;
    int found = 0;
    while (tempp != NULL)
    {
        if (strcmp(tempp->name, name) == 0)
        {
            printf("Found\n");
            printf("Product Name: %s\n", tempp->name);
            printf("Product Price: %.f\n", tempp->price);
            printf("Product Stock: %d\n", tempp->stock);
            found = 1;
            break;
        }
        tempp = tempp->next;
    }

    if (!found)
    {
        printf("Product Not Found\n");
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
    printf("\n[1]Buy Item [2]Return\n");
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
    printf("\nSelected Product: \n");
    while (temp != NULL)
    {
        if (product_id == temp->product_id)
        {
            printf("Product name: %s\n", temp->name);
            printf("Product Price: %.2f\n", temp->price);
            break;
        }
        temp = temp->next;
    }
    printf("\nHow Many do you want to buy: ");
    int amount;
    scanf(" %d", &amount);
    printf("Total Amount: %.2f BDT\n", temp->price * amount);
    printf("[1]Confirm  [2]GO back\n");
    int ch;
    scanf(" %d", &ch);
    if (ch != 1)
    {
        pause();
        customer_front_display();
    }
    temp->stock -= amount;
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
                printf("Not Enough Balance\n");
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
