typedef struct Node_List
{
        void *info;
        int count;
        struct Node_List *Next;
}NodeList;

typedef struct 
{
       NodeList *FirstNode;
}HeadNode;

typedef HeadNode List;



