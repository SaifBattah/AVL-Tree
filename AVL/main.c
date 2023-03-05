#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<conio.h>

/*
Done By: Saif Al-Deen Shakoor Battah.
*/

struct node
{
    char CourseName[50];
    int CreditHours;
    char CourseCode[50];
    int key;
    char Department[50];
    char Topics[200];
    struct node *right, *left;
    int Height;
};
struct node* Root = NULL;
struct node* Create_Tree(struct node* root);
int getHeight (struct node* node);
int MAX (int x, int y);
struct node* singleRotateLeft(struct node* x);
struct node* singleRotateRight(struct node* y);
struct node* doubleRotateLeft(struct node* K3);
struct node* doubleRotateRight(struct node* K3);
struct node* Insert(struct node* node, char* CourseName, int CreditHours,char* CourseCode,int key ,char* Department,char* Topics);
void printInOrder(struct node* t);
void printPreOrder(struct node* t);
struct node* newNode(char* CourseName, int CreditHours,char* CourseCode,int key,char* Department,char* Topics);
struct node* Deleteing(struct node* root, int key);
struct node* minValueNode(struct node* temp);
struct node* Delete_CSWSL(struct node* temp, char Letter);
struct node* Delete_CBTGD(struct node* temp, char* Department);

int main()
{
    Clear_Out_File();
    struct node* root = NULL;
    int Select;
    char CourseName[50];
    int CreditHours;
    char CourseCode[50];
    char Department[50];
    int key;
    char Topics[200];
    char Stop1;
    char Stop2;
    char newline;
    char Letter;
    ///root = Create_Tree(root);
    while(1)
        {
            printf("1. Create The Tree.\n2. Insert a New Course.\n3. Find a Course (Optional: Updating of its information). \n4. List Courses in lexicographic order. \n5. List all topics associated with a given Course. \n6. List all Courses in lexicographic order that belong to the same department.\n7. Delete a Course.\n8. Delete all Courses that start with a specific letter. \n9. Delete all Courses belong to a given department.\n10. Save all words in file offered_courses.txt\n");
            printf("Select Option: ");
            scanf("%d",&Select);
            switch(Select)
            {
                case 1:
                    printf("\n");
                            root = Create_Tree(root);
                            /*
                            printf("---------------- print Tree elements in Pre-order-------------\n\n");
                            printPreOrder(root);
                            printf("\n\n================================================\n\n");
                            printf("---------------- print Tree elements in IN-order-------------\n\n");
                            printInOrder(root);
                            printf("\n\n================================================\n\n");
                            */
                            printf("Tree Created!");
                    printf("\n\n");
                    break;
                case 2:
                    printf("\n");
                    scanf("%c",&newline);
                    printf("Course Name: ");
                    scanf("%[^\t\n]", CourseName);
                    scanf("%c",&Stop1);

                    printf("Credit Hours: ");
                    scanf("%d",&CreditHours);

                    printf("Course Code: ");
                    scanf("%s",CourseCode);

                    scanf("%c",&newline);
                    printf("Department: ");
                    scanf("%[^\t\n]",Department);

                    scanf("%c",&newline);
                    printf("Topics: ");
                    scanf("%[^\t\n]",Topics);
                    scanf("%c",&Stop2);

                    char *ToInt = CourseCode;// initialization

                    while (*ToInt)//read char after char until the end of the word
                        {
                            if (isdigit(*ToInt)) // if char is digit
                                {
                                    key = strtol(ToInt, &ToInt, 10); // set key as the read digit using strtol
                                }

                            else // if not go to the next char
                                {
                                    ToInt++;
                                }
                        }

                    root = Insert(root,CourseName,CreditHours,CourseCode,key,Department,Topics);
                    printf("Node Added!");
                    printf("\n\n");
                    break;
                case 3:
                    printf("\n");
                    scanf("%c",&newline);
                    printf("Enter Course Code(for ex: comp2421): ");
                    scanf("%[^\t\n]", CourseCode);
                    scanf("%c",&Stop1);
                    Searching(root,CourseCode,0);
                    printf("\n\n");
                    break;
                case 4:
                    printf("\n");
                    Print_AVL_Alpha(root);///create file and save the open and print alphab
                    Print_Alphabatically();
                    Clear_File();
                    printf("\n\n");
                    break;
                case 5:
                    printf("\n");
                    scanf("%c",&newline);
                    printf("Enter Course Code: ");
                    scanf("%[^\t\n]", CourseCode);
                    scanf("%c",&Stop1);
                    Print_Topics(root,CourseCode,0);
                    printf("\n\n");
                    break;
                case 6:
                    printf("\n");
                    scanf("%c",&newline);
                    printf("Enter Department Name: ");
                    scanf("%[^\t\n]", Department);
                    scanf("%c",&Stop1);
                    Departments_Search(root,Department);
                    Print_Alphabatically();
                    Clear_File();
                    printf("\n\n");
                    break;
                case 7:
                    printf("\n");
                    scanf("%c",&newline);
                    printf("Enter Course Code: ");
                    scanf("%[^\t\n]", CourseCode);
                    scanf("%c",&Stop1);
                    //////////////////
                    char *ToIn = CourseCode;// initialization

                    while (*ToIn)//read char after char until the end of the word
                        {
                            if (isdigit(*ToIn)) // if char is digit
                                {
                                    key = strtol(ToIn, &ToIn, 10); // set key as the read digit using strtol
                                }

                            else // if not go to the next char
                                {
                                    ToIn++;
                                }
                        }
                    //////////////////
                    root = Deleteing(root,key);
                    printf("\n\n");
                    break;
                case 8:
                    printf("\n");
                    scanf("%c",&newline);
                    printf("Enter Letter: ");
                    scanf("%[^\t\n]",&Letter);
                    scanf("%c",&Stop1);
                    for(int i=0; i<10;i++){
                    root = Delete_CSWSL(root,Letter);
                    }
                    printf("\n\n");
                    break;
                case 9:
                    printf("\n");
                    scanf("%c",&newline);
                    printf("Enter Department Name: ");
                    scanf("%[^\t\n]", Department);
                    scanf("%c",&Stop1);
                    for(int i=0;i<15;i++){
                    root = Delete_CBTGD(root,Department);
                    }
                    printf("\n\n");
                    break;
                case 10:
                    Save_Tree(root);
                    printf("\nTree Saved on file!\n");
                    printf("\nBye!\n");
                    exit(0);
                    break;

                default:
                    printf("\nWrong input! Try Again Please!\n\n");
                    break;
            }
        }
    return 0;
}

struct node* Create_Tree(struct node* root)
{
    char line[300];
    char CourseName[50];
    int CreditHours;
    char CourseCode[50];
    int key;
    char Department[50];
    char Topics[200];
    FILE *f = fopen("courses.txt","r");

    while(fgets(line,300,f))
        {
            if(strlen(line) > 1)
                {
                    char *token = strtok(line,":");
                    strcpy(CourseName,token);
                    ///printf("%s\n",CourseName);
                    token = strtok(NULL, "#");
                    CreditHours = atoi(token);
                    ///printf("Credit Hours: %d\n",CreditHours);
                    token = strtok(NULL, "#");
                    strcpy(CourseCode,token);
                    ///printf("Course Code: %s\n",CourseCode);
                    token = strtok(NULL, "#/");
                    strcpy(Department,token);
                    ///printf("Department: %s\n",Department);
                    token = strtok(NULL,"/");
                    strcpy(Topics,token);
                    ///printf("Topics: %s\n",Topics);

                    char *ToInt = CourseCode;// initialization
                    while (*ToInt)//read char after char until the end of the word
                        {
                            if (isdigit(*ToInt)) // if char is digit
                                {
                                    key = strtol(ToInt, &ToInt, 10); // set key as the read digit using strtol
                                }

                            else // if not go to the next char
                                {
                                    ToInt++;
                                }
                        }

                    root = Insert(root,CourseName,CreditHours,CourseCode,key,Department,Topics);
                }
                ///printf("====================================================\n");
        }
    fclose(f);

    return root;
}

int getHeight (struct node* node){
    if(node==NULL)
        return -1;
    else
        return node->Height;
}

int MAX (int x, int y){
    if(x>y)
        return x;
    else
        return y;
}

struct node* singleRotateLeft(struct node* x) {
    struct node*  y;
    y         = x->right;
    x->right  = y->left;
    y->left = x;

    x->Height = 1 + MAX(getHeight(x->left) , getHeight(x->right));
    y->Height = 1 + MAX(getHeight(x) , getHeight(y->right));

    return y;
}

struct node* singleRotateRight(struct node* y) {
    struct node* x;
    x        = y->left;
    y->left  = x->right;
    x->right = y;

    y->Height = 1 + MAX(getHeight(y->right) , getHeight(y->left));
    x->Height = 1 + MAX(getHeight(y) , getHeight(x->left));

    return x;
}

struct node* doubleRotateLeft(struct node* K3) {
    K3->left  = singleRotateLeft(K3->left);
    return singleRotateRight(K3);
}

struct node* doubleRotateRight(struct node* K3) {
    K3->right  = singleRotateRight(K3->right);
    return singleRotateLeft(K3);
}

struct node* Insert(struct node* node, char* CourseName, int CreditHours,char* CourseCode,int key,char* Department,char* Topics)
{
    if(node == NULL)//First Node
        {
            return newNode(CourseName, CreditHours, CourseCode, key, Department, Topics);
        }

    else if(key < node->key)
        {
            ///printf("%d Inserted at left of %d\n",key,node->key);
            node->left = Insert(node->left,CourseName,CreditHours,CourseCode,key,Department,Topics);
            if(getHeight(node->left) - getHeight(node->right) >= 2)
                {

                    if(key < node->left->key)
                        {
                            node = singleRotateRight(node);
                        }
                    else
                        {
                            node = doubleRotateLeft(node);
                        }
                }
        }

    else if(key > node->key)
        {
            ///printf("%d Inserted at right of %d\n",key,node->key);
            node->right = Insert(node->right,CourseName,CreditHours,CourseCode,key,Department,Topics);
            if(getHeight(node->right) - getHeight(node->left) >=2)
                {
                    if(key > node->right->key)
                        {
                            node = singleRotateLeft(node);
                        }
                    else
                        {
                            node = doubleRotateRight(node);
                        }
                }
        }
    node->Height = 1 + MAX(getHeight(node->right) , getHeight(node->left));
    return node;
}

struct node* newNode(char* CourseName, int CreditHours,char* CourseCode,int key,char* Department,char* Topics)
{
    struct node* Temp = (struct node*)malloc(sizeof(struct node));
    strcpy(Temp->CourseName,CourseName);
    Temp->CreditHours = CreditHours;
    strcpy(Temp->CourseCode,CourseCode);
    Temp->key = key;
    strcpy(Temp->Department,Department);
    strcpy(Temp->Topics,Topics);
    Temp->left = Temp->right = NULL;
    Temp->Height = 0;
    return Temp;
}

void Searching(struct node* t, char* CourseCode,int counter)
{
    int choice;
    char *ToInt = CourseCode;// initialization
    int key;

    while (*ToInt)//read char after char until the end of the word
        {
            if (isdigit(*ToInt)) // if char is digit
                {
                    key = strtol(ToInt, &ToInt, 10); // set key as the read digit using strtol
                }

            else // if not go to the next char
                    {
                        ToInt++;
                    }
        }

    if(t == NULL)
        {
            if(counter == 0)
                {
                    printf("\nTree is empty\n");
                }

            else
                {
                    printf("\nCourse Not Founded\n");
                }
        }

    else
        {
            if(t->key == key)
                {
                    if(strcmp(t->CourseCode,CourseCode) == 0)
                        {
                            printf("\nCourse Founded!\n");
                            printf("\nTo Update Information(Enter 1)\n");
                            scanf("%d",&choice);

                            if(choice == 1)
                                {
                                    Updating(t);
                                }

                            else if(choice = 2)
                                {
                                    printf("");
                                }

                            else
                                {
                                    printf("");
                                }

                        }

                    else
                        {
                            printf("\nThe founded course doesn't match your input!\n");
                        }
                        ///function asking of update
                }

            else if(t->key > key)
                {
                    Searching(t->left,CourseCode,1);
                }

            else if(t->key < key)
                {
                    Searching(t->right,CourseCode,1);
                }

        }
}

void Updating(struct node* temp)
{
    printf("%s:%d#%s#%s:%s",temp->CourseName,temp->CreditHours,temp->CourseCode,temp->Department,temp->Topics);
    int choice;
    //int TopicChoice;
    char CourseName[50];
    int CreditHours;
    char Department[50];
    char Topics[200];
    char temptopic[32];
    char newline;
    char Stop;
    char str[] = ",";
    printf("\nWhat to edit?\n1- Course name\n2- Credit Hours\n3- Department.\n4- Topics.\nChoice:");
    scanf("%d",&choice);

    switch(choice)
        {
            case 1:
                printf("\nOld: %s\n",temp->CourseName);
                scanf("%c",&newline);
                printf("New: ");
                scanf("%[^\t\n]", CourseName);
                strcpy(temp->CourseName,CourseName);
                printf("\nUpdated Successfully!\n");
                break;

            case 2:
                printf("\nOld: %d\n",temp->CreditHours);
                printf("New: ");
                scanf("%d",&CreditHours);
                temp->CreditHours = CreditHours;
                printf("\nUpdated Successfully!\n");
                break;

            case 3:
                printf("\nOld: %s\n",temp->Department);
                scanf("%c",&newline);
                printf("New: ");
                scanf("%[^\t\n]", Department);
                strcpy(temp->Department,Department);
                printf("\nUpdated Successfully!\n");
                break;

            case 4:
                printf("\nTopics: %s\n",temp->Topics);
                ///printf("\nSelect:\n1- Add new topic.\n2-Delete existing Topic.\nChoice:");
                ///scanf("%d",&TopicChoice);

                ///if(TopicChoice == 1)
                   /// {
                        scanf("%c",&newline);
                        printf("New Topic: ");
                        scanf("%[^\t\n]", temptopic);
                        scanf("%c",&Stop);
                        strcat(str,temptopic);
                        strtok(str,"\n");
                        strcpy(Topics,temp->Topics);
                        strcat(Topics,str);
                        Topics[strlen(Topics) + 1] = "";
                        strcpy(temp->Topics,Topics);
                        printf("\nTopics: %s\n",Topics);
                        printf("\nUpdated Successfully!\n");
                   /// }

                break;

            default :
                break;
        }
}

void Print_AVL_Alpha(struct node* root)
{
    if (root != NULL)
    {
        Print_AVL_Alpha(root->left);
        Put_In_File(root->CourseName);
        Print_AVL_Alpha(root->right);
    }

}

void Put_In_File(char* Name)
{
    FILE *fo = fopen("Alpha.txt","a");
    fprintf(fo,"%s\n",Name);
    fclose(fo);
}

void Print_Alphabatically()
{
    char line[50];
    char temp[50];
    char ordering[50][50];
    int index = 0;
    FILE *fopens = fopen("Alpha.txt","r");

    while(fgets(line,100,fopens) != NULL)
        {
            strcpy(ordering[index],line);
            index++;
        }

        fclose(fopens);

    for(int j = 0; j<=index;j++)
        {
            for(int k = j+1; k<=index;k++)
                {
                    if(strcmp(ordering[j],ordering[k])>0)
                        {
                            strcpy(temp,ordering[j]);
                            strcpy(ordering[j],ordering[k]);
                            strcpy(ordering[k],temp);
                        }
                }
        }

    for(int i = 0; i<=index;i++)
        {
            printf("%s",ordering[i]);
        }

}

void Clear_File()
{
    FILE *fopens;
    fopens = fopen("Alpha.txt","w");
    fprintf(fopens,"%s","");
    fclose(fopens);
}


void Print_Topics(struct node* temp, char* Course,int founded)
{
    char *ToInt = Course;// initialization
    int key;
    while (*ToInt)//read char after char until the end of the word
        {
            if (isdigit(*ToInt)) // if char is digit
                {
                    key = strtol(ToInt, &ToInt, 10); // set key as the read digit using strtol
                }

            else // if not go to the next char
                    {
                        ToInt++;
                    }
        }
    if(temp!= NULL)
        {
            if(key == temp->key)
                {
                    printf("node: %s\nCourse: %s\n",temp->CourseCode,Course);
                    printf("%s",temp->Topics);
                    founded = 1;
                }

            if(founded != 1)
                {
                    Print_Topics(temp->left,Course,0);
                    Print_Topics(temp->right,Course,0);
                }
        }
}

void Departments_Search(struct node* temp, char* DepartmentName)
{
    int i;
    int Matching = 0;
    if(temp!= NULL)
        {
            for(i=0;temp->Department[i]!='\0';i++)
                {
                    if(DepartmentName[i]==temp->Department[i])
                        {
                            Matching++;
                        }
                }

            if(Matching==i)
            {
                //printf("%s\n",temp->CourseName);
                ///here
                Put_In_File(temp->CourseName);
            }
            Departments_Search(temp->left,DepartmentName);
            Departments_Search(temp->right,DepartmentName);
        }
}

struct node* Deleteing(struct node* root, int key)
{
    struct node* temp;
	if (root == NULL)
        {
            return root;
        }

	if ( key < root->key )
        {
            root->left = Deleteing(root->left, key);
        }

	else if( key > root->key )
        {
            root->right = Deleteing(root->right, key);
        }

	else
        {
            if( (root->left == NULL) || (root->right == NULL) )
                {
                    struct node *temp = root->left ? root->left : root->right;

                    if (temp == NULL)
                        {
                            temp = root;
                            root = NULL;
                        }

                    else
                        *root = *temp;

                    free(temp);
                }

            else
                {
                    struct node* temp = minValueNode(root->right);
                    root->key = temp->key;
                    root->right = Deleteing(root->right, temp->key);
                }
        }

	if (root == NULL)
        {
            return root;
        }

	root->Height = 1+ MAX(getHeight(root->left),getHeight(root->right));

	int balance = getBalanceFactor(root);

	if (balance > 1 && getBalanceFactor(root->left) >= 0)
        {
            return singleRotateRight(root);
        }

	if (balance > 1 && getBalanceFactor(root->left) < 0)
        {
            root->left = singleRotateLeft(root->left);
            return singleRotateRight(root);
        }

	if (balance < -1 && getBalanceFactor(root->right) <= 0)
        {
            return singleRotateLeft(root);
        }

	if (balance < -1 && getBalanceFactor(root->right) > 0)
        {
            root->right = singleRotateRight(root->right);
            return singleRotateLeft(root);
        }

	return root;

}

struct node* minValueNode(struct node* temp)
{
    struct node* current = temp;

    while(current->left != NULL)
        {
            current = current->left;
        }
    return current;
}


int getBalanceFactor(struct node* temp)
{
    if(temp == NULL)
        {
            return 0;
        }
    return getHeight(temp->left) - getHeight(temp->right);
}

struct node* Delete_CSWSL(struct node* temp, char Letter)
{
    if(temp!= NULL)
        {
            printf("%c",temp->CourseCode[0]);
            if(Letter == temp->CourseCode[0])
                {
                    return Deleteing(temp,temp->key);
                }
            temp->left = Delete_CSWSL(temp->left,Letter);
            temp->right = Delete_CSWSL(temp->right,Letter);
        }
    return temp;
}

struct node* Delete_CBTGD(struct node* temp, char* Department)
{
        if(temp!= NULL)
        {

            if(!strcmp(Department,temp->Department))
                {
                    return Deleteing(temp,temp->key);
                }
            temp->left = Delete_CBTGD(temp->left,Department);
            temp->right = Delete_CBTGD(temp->right,Department);

        }
    return temp;
}

void Save_Tree(struct node* root)
{

    if(root != NULL)
        {
            FILE *fopens;
            fopens = fopen("offered_courses.txt","a");
            fprintf(fopens,"%s:%d#%s#%s/%s\n",root->CourseName,root->CreditHours,root->CourseCode,root->Department,root->Topics);
            fclose(fopens);
            Save_Tree(root->left);
            Save_Tree(root->right);
        }
}

void Clear_Out_File()
{
    FILE *fopens;
    fopens = fopen("offered_courses.txt","w");
    fprintf(fopens,"%s","");
    fclose(fopens);
}
