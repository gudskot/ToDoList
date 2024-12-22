#include <stdio.h>

int main()
{
    FILE *fw;
    char task[50], sign, quit, buffer[50];
    if((fw = fopen("ToDoList.txt", "w+")) == NULL) return 1;

    printf("Hi, I'm ToDoList\n");
    while(sign != 'Q')
    {
        printf("Add your task: ");
        fgets(task, sizeof(task), stdin);
        fputs(task, fw);

        printf("Tasks -> T\nContinue -> Enter\nLeave -> Q\n");
        scanf("%c", &sign);
        getchar();

        if(sign == 'T')
        {
            rewind(fw);
            printf("/////\n");
            while(fgets(buffer, sizeof(buffer), fw) != NULL)
            {
                printf("%s", buffer);
            }
            printf("/////\n");
            printf("Continue -> Enter\nLeave -> Q\n");
            scanf("%c", &sign);
            getchar();
        }
    }
    printf("Goodbye!");

    return 0;
}