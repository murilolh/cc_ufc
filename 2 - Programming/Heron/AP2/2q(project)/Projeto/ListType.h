typedef struct Node_List
{
        void *info;
        struct Node_List *Next;
        int count;
}NodeList;

typedef struct 
{
       NodeList *FirstNode;
}HeadNode;

typedef HeadNode List;


