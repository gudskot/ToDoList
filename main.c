#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int writeFile(FILE *fw)
{
    char task[50];
    printf("Add your task: ");
    fgets(task, sizeof(task), stdin);       //reading from standart input
    fputs(task, fw);        //noting input into file

    return 0;
}

int readFile(FILE *fw)
{
    char buffer[50];
    rewind(fw);     //back to the beginning of file
    printf("/////\n");
    while(fgets(buffer, sizeof(buffer), fw) != NULL)
    {
        printf("%s", buffer);
    }
    printf("/////\n");

    return 0;
}

int deleteLine(char file[13], FILE *fw)
{
    FILE *temp;
    if((temp = fopen("ToDoListTemp.txt", "w+")) == NULL) 
    {
        printf("Failed to open the file.\n");
        return 1; 
    }
    char buffer[50];
    int lineToDelete, currentLine = 0;
    
    printf("Line to delete: ");
    scanf("%d", &lineToDelete);
    getchar();      //Clear input from '\n'
    lineToDelete--;     //For a better understanding of which row will be deleted

    rewind(fw);     //back to the beginning of file
    while(fgets(buffer, sizeof(buffer), fw) != NULL)
    {
        if(currentLine != lineToDelete)
        {
            fputs(buffer, temp);
        }
        currentLine++;
    }
    fclose(fw);
    fclose(temp);

    remove(file);       // Delete original file
    rename("ToDoListTemp.txt", file);       // Rename temporary file
    if((fw = fopen(file, "r+")) == NULL)    // Reopen the updated file
    {
        printf("Failed to reopen the file.\n");
        return 1;
    }

    return 0;
}

int editFile(char file[13], FILE *fw)
{
    FILE *temp;
    if((temp = fopen("ToDoListTemp.txt", "w+")) == NULL) 
    {
        printf("Failed to open the file.\n");
        return 1; 
    }
    char buffer[50], editLine[50];
    int lineToEdit, currentLine = 0;

    printf("Line to edit: ");
    scanf("%d", &lineToEdit);
    getchar();      //Clear input from '\n'
    
    lineToEdit--;     //For a better understanding of which row will be edit

    printf("Edit: ");
    scanf("%s", &editLine);
    getchar();      //Clear input from '\n'

    int len = strlen(editLine);
    if(len + 1 < sizeof(editLine))      //Is there enough space for '\0'
    {
        editLine[len] = '\n';
        editLine[len + 1] = '\0';
    }

    rewind(fw);     //back to the beginning of file
    while(fgets(buffer, sizeof(buffer), fw) != NULL)
    {
        if(currentLine != lineToEdit)
        {
            fputs(buffer, temp);
        }
        else
        {
            fputs(editLine, temp);
        }
        currentLine++;
    }
    fclose(fw);
    fclose(temp);

    remove(file);       // Delete original file
    rename("ToDoListTemp.txt", file);       // Rename temporary file
    if((fw = fopen(file, "r+")) == NULL)    // Reopen the updated file
    {
        printf("Failed to reopen the file.\n");
        return 1;
    }

    return 0;
}

int main()
{
    FILE *fw;
    char sign;
    char file[] = "ToDoList.txt";
    if((fw = fopen(file, "w+")) == NULL)        //Openning file and clear input
    {
        printf("Failed to create the file.\n");
        return 1;     
    }

    printf("Hi, I'm ToDoList\n");
    while(1)      //working until user enter 'Q'
    {
        printf("Write -> W\nEdit -> E\nDelete -> D\nTasks -> T\nLeave -> Q\n");
        scanf("%c", &sign);
        getchar();      //Clear input from '\n'

        if(sign == 'W')
        {
            writeFile(fw);
        }
        else if(sign == 'E')
        {
            editFile(file, fw);
        }
        else if(sign == 'D')
        {
            deleteLine(file, fw);
        }
        else if(sign == 'T')     
        {
            readFile(fw);
        }
        else if(sign == 'Q')
        {
            break;
        }
        else
        {
            printf("Invalid option. Try again.\n");
        }
    }
    printf("Goodbye!");
    fclose(fw);

    return 0;
}