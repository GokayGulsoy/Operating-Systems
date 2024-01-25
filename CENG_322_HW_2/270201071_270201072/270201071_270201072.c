/*
  270201071 Merve Nur Ozan
  270201072 Gökay Gülsoy
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct normal_menu
{
    char *date;
    char *soup;
    char *main_dish;
    char *side_dish;
    char *extra;
    int *sale_count_array;
};

struct vegan_menu
{
    char *date;
    char *soup;
    char *main_dish;
    char *side_dish;
    char *extra;
    int *sale_count_array;
};

struct vegetarian_menu
{
    char *date;
    char *soup;
    char *main_dish;
    char *side_dish;
    char *extra;
    int *sale_count_array;
};

typedef struct cafeteria
{
    char *month_name;
    struct normal_menu *normal_menu_array;
    struct vegan_menu *vegan_menu_array;
    struct vegetarian_menu *vegetarian_menu_array;
} Cafeteria;

// function prototypes
void initialize_menus(Cafeteria *, char *);
void record_customer_counts(Cafeteria *);
void calc_and_show_income(Cafeteria *);

int main()
{

    Cafeteria *our_cafeteria = (Cafeteria *)malloc(sizeof(Cafeteria));
    our_cafeteria->month_name = NULL;
    our_cafeteria->normal_menu_array = NULL;
    our_cafeteria->vegan_menu_array = NULL;
    our_cafeteria->vegetarian_menu_array = NULL;
    char *csv_file_name = "cafeteria_march_menu.csv";
    initialize_menus(our_cafeteria, csv_file_name);
    record_customer_counts(our_cafeteria);
    calc_and_show_income(our_cafeteria);

    return 0;
}

// function initialzie_menus
void initialize_menus(Cafeteria *cafeteria, char *csv_file_name)
{
    // allocating normal,vegan, and vegeterian menu arrays
    cafeteria->normal_menu_array = (struct normal_menu *)malloc(sizeof(struct normal_menu) * 23);
    cafeteria->vegan_menu_array = (struct vegan_menu *)malloc(sizeof(struct vegan_menu) * 23);
    cafeteria->vegetarian_menu_array = (struct vegetarian_menu *)malloc(sizeof(struct vegetarian_menu) * 23);

    for (int i = 0; i < 23; i++)
    {
        struct normal_menu n_menu;
        struct vegan_menu veg_menu;
        struct vegetarian_menu vegetar_menu;
        cafeteria->normal_menu_array[i] = n_menu;
        cafeteria->vegan_menu_array[i] = veg_menu;
        cafeteria->vegetarian_menu_array[i] = vegetar_menu;
    }

    FILE *file_ptr = fopen(csv_file_name, "r");
    if (file_ptr == NULL)
    {
        printf("could not open the file %s\n", csv_file_name);
        exit(0);
    }

    // assigning month name from file name
    int month_name_index = 0;
    char *month_name = (char *)malloc(sizeof(char) * 30);
    int org_index = 0;
    while (csv_file_name[month_name_index] != '_')
    {
        month_name_index++;
    }

    month_name_index++;

    while (csv_file_name[month_name_index] != '_')
    {
        month_name[org_index] = csv_file_name[month_name_index];
        month_name_index++;
        org_index++;
    }

    month_name[org_index] = '\0';
    cafeteria->month_name = (char *)malloc((strlen(month_name) + 1) * sizeof(char));
    strcpy(cafeteria->month_name, month_name);

    char *token;
    char line[256];
    int line_no = 0;
    while (fgets(line, sizeof(line), file_ptr) != NULL)
    {

        token = strtok(line, ",");
        int token_no = 0;
        while (token != NULL)
        {

            // skipping the first token as not used
            if (token_no == 0)
            {
                token = strtok(NULL, ",");
                token_no++;
            }

            if (line_no >= 0 && line_no < 23)
            {

                switch (token_no)
                {
                case 1:
                    cafeteria->normal_menu_array[line_no].date = (char *)malloc(sizeof(char) * strlen(token) + 1);
                    strcpy(cafeteria->normal_menu_array[line_no].date, token);
                    break;
                case 2:
                    cafeteria->normal_menu_array[line_no].soup = (char *)malloc(sizeof(char) * strlen(token) + 1);
                    strcpy(cafeteria->normal_menu_array[line_no].soup, token);
                    break;
                case 3:
                    cafeteria->normal_menu_array[line_no].main_dish = (char *)malloc(sizeof(char) * strlen(token) + 1);
                    strcpy(cafeteria->normal_menu_array[line_no].main_dish, token);
                    break;
                case 4:
                    cafeteria->normal_menu_array[line_no].side_dish = (char *)malloc(sizeof(char) * strlen(token) + 1);
                    strcpy(cafeteria->normal_menu_array[line_no].side_dish, token);
                    break;
                case 5:
                    cafeteria->normal_menu_array[line_no].extra = (char *)malloc(sizeof(char) * strlen(token) + 1);
                    strcpy(cafeteria->normal_menu_array[line_no].extra, token);
                }
            }

            else if (line_no >= 23 && line_no < 46)
            {
                switch (token_no)
                {
                case 1:
                    cafeteria->vegan_menu_array[line_no % 23].date = (char *)malloc(sizeof(char) * strlen(token) + 1);
                    strcpy(cafeteria->vegan_menu_array[line_no % 23].date, token);
                    break;
                case 2:
                    cafeteria->vegan_menu_array[line_no % 23].soup = (char *)malloc(sizeof(char) * strlen(token) + 1);
                    strcpy(cafeteria->vegan_menu_array[line_no % 23].soup, token);
                    break;
                case 3:
                    cafeteria->vegan_menu_array[line_no % 23].main_dish = (char *)malloc(sizeof(char) * strlen(token) + 1);
                    strcpy(cafeteria->vegan_menu_array[line_no % 23].main_dish, token);
                    break;
                case 4:
                    cafeteria->vegan_menu_array[line_no % 23].side_dish = (char *)malloc(sizeof(char) * strlen(token) + 1);
                    strcpy(cafeteria->vegan_menu_array[line_no % 23].side_dish, token);
                    break;
                case 5:
                    cafeteria->vegan_menu_array[line_no % 23].extra = (char *)malloc(sizeof(char) * strlen(token) + 1);
                    strcpy(cafeteria->vegan_menu_array[line_no % 23].extra, token);
                }
            }

            else if (line_no >= 46)
            {
                switch (token_no)
                {
                case 1:
                    cafeteria->vegetarian_menu_array[line_no % 23].date = (char *)malloc(sizeof(char) * strlen(token) + 1);
                    strcpy(cafeteria->vegetarian_menu_array[line_no % 23].date, token);
                    break;
                case 2:
                    cafeteria->vegetarian_menu_array[line_no % 23].soup = (char *)malloc(sizeof(char) * strlen(token) + 1);
                    strcpy(cafeteria->vegetarian_menu_array[line_no % 23].soup, token);
                    break;
                case 3:
                    cafeteria->vegetarian_menu_array[line_no % 23].main_dish = (char *)malloc(sizeof(char) * strlen(token) + 1);
                    strcpy(cafeteria->vegetarian_menu_array[line_no % 23].main_dish, token);
                    break;
                case 4:
                    cafeteria->vegetarian_menu_array[line_no % 23].side_dish = (char *)malloc(sizeof(char) * strlen(token) + 1);
                    strcpy(cafeteria->vegetarian_menu_array[line_no % 23].side_dish, token);
                    break;
                case 5:
                    cafeteria->vegetarian_menu_array[line_no % 23].extra = (char *)malloc(sizeof(char) * strlen(token) + 1);
                    strcpy(cafeteria->vegetarian_menu_array[line_no % 23].extra, token);
                }
            }

            // tokenizing the next string
            token = strtok(NULL, ",");
            token_no++;
        }

        line_no++;
    }

    
     fclose(file_ptr);
}

// function record_customer_counts
void record_customer_counts(Cafeteria *cafeteria)
{ 

    // setting seed for random number generator
    srand(time(0));
    for (int i = 0; i < 23; i++)
    {
        cafeteria->normal_menu_array[i].sale_count_array = (int *)malloc(sizeof(int) * 3);
        cafeteria->vegan_menu_array[i].sale_count_array = (int *)malloc(sizeof(int) * 3);
        cafeteria->vegetarian_menu_array[i].sale_count_array = (int *)malloc(sizeof(int) * 3);

        cafeteria->normal_menu_array[i].sale_count_array[0] = rand() % 51;
        cafeteria->normal_menu_array[i].sale_count_array[1] = rand() % 51;
        cafeteria->normal_menu_array[i].sale_count_array[2] = rand() % 51;

        cafeteria->vegan_menu_array[i].sale_count_array[0] = rand() % 51;
        cafeteria->vegan_menu_array[i].sale_count_array[1] = rand() % 51;
        cafeteria->vegan_menu_array[i].sale_count_array[2] = rand() % 51;

        cafeteria->vegetarian_menu_array[i].sale_count_array[0] = rand() % 51;
        cafeteria->vegetarian_menu_array[i].sale_count_array[1] = rand() % 51;
        cafeteria->vegetarian_menu_array[i].sale_count_array[2] = rand() % 51;
    }

}

// function calc_and_show_income
void calc_and_show_income(Cafeteria *cafeteria)
{

    int normal_menu_sales = 0, vegan_menu_sales = 0, vegetarian_menu_sales = 0;
    int student_sales = 0, academic_sales = 0, administrative_sales = 0;
    int total_sales = 0;

    for (int i = 0; i < 23; i++)
    {
  
        normal_menu_sales += cafeteria->normal_menu_array[i].sale_count_array[0] * 6;
        normal_menu_sales += cafeteria->normal_menu_array[i].sale_count_array[1] * 16;
        normal_menu_sales += cafeteria->normal_menu_array[i].sale_count_array[2] * 12;

        vegan_menu_sales += cafeteria->vegan_menu_array[i].sale_count_array[0] * 6;
        vegan_menu_sales += cafeteria->vegan_menu_array[i].sale_count_array[1] * 16;
        vegan_menu_sales += cafeteria->vegan_menu_array[i].sale_count_array[2] * 12;

        vegetarian_menu_sales += cafeteria->vegetarian_menu_array[i].sale_count_array[0] * 6;
        vegetarian_menu_sales += cafeteria->vegetarian_menu_array[i].sale_count_array[1] * 16;
        vegetarian_menu_sales += cafeteria->vegetarian_menu_array[i].sale_count_array[2] * 12;

        student_sales += cafeteria->normal_menu_array[i].sale_count_array[0] * 6;
        student_sales += cafeteria->vegan_menu_array[i].sale_count_array[0] * 6;
        student_sales += cafeteria->vegetarian_menu_array[i].sale_count_array[0] * 6;

        academic_sales += cafeteria->normal_menu_array[i].sale_count_array[1] * 16;
        academic_sales += cafeteria->vegan_menu_array[i].sale_count_array[1] * 16;
        academic_sales += cafeteria->vegetarian_menu_array[i].sale_count_array[1] * 16;

        administrative_sales += cafeteria->normal_menu_array[i].sale_count_array[2] * 12;
        administrative_sales += cafeteria->vegan_menu_array[i].sale_count_array[2] * 12;
        administrative_sales += cafeteria->vegetarian_menu_array[i].sale_count_array[2] * 12;
    }

    total_sales = student_sales + academic_sales + administrative_sales;
    printf("~~~Normal menu for the first day of month\n");
    printf("date--> %s\n", cafeteria->normal_menu_array[0].date);
    printf("soup--> %s\n", cafeteria->normal_menu_array[0].soup);
    printf("main_dish--> %s\n", cafeteria->normal_menu_array[0].main_dish);
    printf("side_dish--> %s\n", cafeteria->normal_menu_array[0].side_dish);
    printf("extra--> %s\n", cafeteria->normal_menu_array[0].extra);

    printf("~~~Normal menu for the last day of month\n");
    printf("date--> %s\n", cafeteria->normal_menu_array[22].date);
    printf("soup--> %s\n", cafeteria->normal_menu_array[22].soup);
    printf("main_dish--> %s\n", cafeteria->normal_menu_array[22].main_dish);
    printf("side_dish--> %s\n", cafeteria->normal_menu_array[22].side_dish);
    printf("extra--> %s\n", cafeteria->normal_menu_array[22].extra);

    printf("~~~Vegan menu for the first day of month\n");
    printf("date--> %s\n", cafeteria->vegan_menu_array[0].date);
    printf("soup--> %s\n", cafeteria->vegan_menu_array[0].soup);
    printf("main_dish--> %s\n", cafeteria->vegan_menu_array[0].main_dish);
    printf("side_dish--> %s\n", cafeteria->vegan_menu_array[0].side_dish);
    printf("extra--> %s\n", cafeteria->vegan_menu_array[0].extra);

    printf("~~~Vegan menu for the last day of month\n");
    printf("date--> %s\n", cafeteria->vegan_menu_array[22].date);
    printf("soup--> %s\n", cafeteria->vegan_menu_array[22].soup);
    printf("main_dish--> %s\n", cafeteria->vegan_menu_array[22].main_dish);
    printf("side_dish--> %s\n", cafeteria->vegan_menu_array[22].side_dish);
    printf("extra--> %s\n", cafeteria->vegan_menu_array[22].extra);

    printf("~~~Vegetarian menu for the first day of month\n");
    printf("date--> %s\n", cafeteria->vegetarian_menu_array[0].date);
    printf("soup--> %s\n", cafeteria->vegetarian_menu_array[0].soup);
    printf("main_dish--> %s\n", cafeteria->vegetarian_menu_array[0].main_dish);
    printf("side_dish--> %s\n", cafeteria->vegetarian_menu_array[0].side_dish);
    printf("extra--> %s\n", cafeteria->vegetarian_menu_array[0].extra);

    printf("~~~Vegetarian menu for the last day of month\n");
    printf("date--> %s\n", cafeteria->vegetarian_menu_array[22].date);
    printf("soup--> %s\n", cafeteria->vegetarian_menu_array[22].soup);
    printf("main_dish--> %s\n", cafeteria->vegetarian_menu_array[22].main_dish);
    printf("side_dish--> %s\n", cafeteria->vegetarian_menu_array[22].side_dish);
    printf("extra--> %s\n", cafeteria->vegetarian_menu_array[22].extra);

    printf("Example output for normal menu ====> %s |%s|%s|%s|%s\n",
           cafeteria->normal_menu_array[2].date, cafeteria->normal_menu_array[2].soup,
           cafeteria->normal_menu_array[2].main_dish,
           cafeteria->normal_menu_array[2].side_dish, cafeteria->normal_menu_array[2].extra);

    printf("Example output for vegan menu ====> %s |%s|%s|%s|%s\n",
           cafeteria->vegan_menu_array[7].date, cafeteria->vegan_menu_array[7].soup,
           cafeteria->vegan_menu_array[7].main_dish, cafeteria->vegan_menu_array[7].side_dish,
           cafeteria->vegan_menu_array[7].extra);
           
    printf("Example output for vegeterian menu ====> %s |%s|%s|%s|%s\n",
           cafeteria->vegetarian_menu_array[13].date,
           cafeteria->vegetarian_menu_array[13].soup,
           cafeteria->vegetarian_menu_array[13].main_dish,
           cafeteria->vegetarian_menu_array[13].side_dish,
           cafeteria->vegetarian_menu_array[13].extra);

    printf("\nCounts for the normal menu of March 3rd ===> Student:%d,Academic:%d,Administrative:%d\n",
           cafeteria->normal_menu_array[2].sale_count_array[0], cafeteria->normal_menu_array[2].sale_count_array[1],
           cafeteria->normal_menu_array[2].sale_count_array[2]);

    printf("\nCounts for the vegan menu of March 10th ===> Student:%d,Academic:%d,Administrative:%d\n",
           cafeteria->vegan_menu_array[7].sale_count_array[0], cafeteria->vegan_menu_array[7].sale_count_array[1],
           cafeteria->vegan_menu_array[7].sale_count_array[2]);

    printf("\nCounts for the vegetarian menu of March 20th ===> Student:%d,Academic:%d,Administrative:%d\n",
           cafeteria->vegetarian_menu_array[13].sale_count_array[0], cafeteria->vegetarian_menu_array[13].sale_count_array[1],
           cafeteria->vegetarian_menu_array[13].sale_count_array[2]);

    printf("\n************SALES RESULT************\n\n");
    printf("Normal menu sales: %d TL, Vegan menu sales: %d TL, Vegetarian menu sales: %d TL\n",
           normal_menu_sales, vegan_menu_sales, vegetarian_menu_sales);
    printf("Student sales: %d TL, Academic personal sales: %d TL, Administrative personal sales: %d TL\n",
           student_sales, academic_sales, administrative_sales);
    printf("Total sale income: %d TL\n", total_sales);
    
    
    // freeing dynamically allocated memory
    for (int i = 0; i < 23; i++) {
        free(cafeteria->normal_menu_array[i].sale_count_array);
        free(cafeteria->vegan_menu_array[i].sale_count_array);
        free(cafeteria->vegetarian_menu_array[i].sale_count_array);
        
        free(cafeteria->normal_menu_array[i].date);
        free(cafeteria->normal_menu_array[i].soup);
        free(cafeteria->normal_menu_array[i].main_dish);
        free(cafeteria->normal_menu_array[i].side_dish);
        free(cafeteria->normal_menu_array[i].extra);
       
        
        free(cafeteria->vegan_menu_array[i].date);
        free(cafeteria->vegan_menu_array[i].soup);
        free(cafeteria->vegan_menu_array[i].main_dish);
        free(cafeteria->vegan_menu_array[i].side_dish);
        free(cafeteria->vegan_menu_array[i].extra);
        
        free(cafeteria->vegetarian_menu_array[i].date);
        free(cafeteria->vegetarian_menu_array[i].soup);
        free(cafeteria->vegetarian_menu_array[i].main_dish);
        free(cafeteria->vegetarian_menu_array[i].side_dish);
        free(cafeteria->vegetarian_menu_array[i].extra);
    }

    free(cafeteria->month_name);
    free(cafeteria->normal_menu_array);
    free(cafeteria->vegan_menu_array);
    free(cafeteria->vegetarian_menu_array);
    free(cafeteria);
}
