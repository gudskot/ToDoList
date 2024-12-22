#include <stdio.h>

int main()
{
    FILE *fw;
    char task[50], sign, quit, buffer[50];
    if((fw = fopen("ToDoList.txt", "w+")) == NULL) return 1;        //check readability

    printf("Hi, I'm ToDoList\n");
    while(sign != 'Q')      //working until user enter 'Q'
    {
        printf("Add your task: ");
        fgets(task, sizeof(task), stdin);       //reading from standart input
        fputs(task, fw);        //noting input into file

        printf("Tasks -> T\nContinue -> Enter\nLeave -> Q\n");
        scanf("%c", &sign);
        getchar();      //Clear input from '\n'

        if(sign == 'T')     
        {
            rewind(fw);     //back to the beginning of file
            printf("/////\n");
            while(fgets(buffer, sizeof(buffer), fw) != NULL)
            {
                printf("%s", buffer);
            }
            printf("/////\n");
            printf("Continue -> Enter\nLeave -> Q\n");
            scanf("%c", &sign);
            getchar();      //Clear input from '\n'
        }
    }
    printf("Goodbye!");
    fclose(fw);

    return 0;
}