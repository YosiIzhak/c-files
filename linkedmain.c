#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linked.h"


int main()
{

Person *Head;
Person *item;
Person *per;

Person *Pointer1;
Person *Pointer2;
Person *Pointer3;
Person *Pointer4;
Person *Pointer5;

Person Person1;
Person Person2;
Person Person3;
Person Person4;
Person Person5;

Person1.m_id = 1111;
Person1.m_age = 1;
Person1.m_next = NULL;
strcpy(Person1.m_name,"yosi"); 


Person2.m_id = 2222;
Person2.m_age = 2;
Person2.m_next = NULL;
strcpy(Person2.m_name,"jo");  


Person3.m_id = 3333;
Person3.m_age = 3;
Person3.m_next = NULL;
strcpy(Person3.m_name,"yakov"); 


Person4.m_id = 2;
Person4.m_age = 4;
Person4.m_next = NULL;
strcpy(Person4.m_name,"dana"); 


Person5.m_id = 5555;
Person5.m_age = 5;
Person5.m_next = NULL;
strcpy(Person5.m_name,"mosh");  
         
Pointer1 = &Person1;
Pointer2 = &Person2;
Pointer3 = &Person3;
Pointer4 = &Person4;
Pointer5 = &Person5;

Head = ListInsertHead(NULL ,Pointer1);
printf("Person1\n");
printf("id: %d\n", Head -> m_id);
printf("name: %s\n", Head -> m_name);
printf("age: %d\n", Head -> m_age);
printf("next: %p\n",(void*) Head -> m_next);
printf("\n\n");

Head = ListInsertHead(Head ,Pointer2);
printf("Person2\n");
printf("id: %d\n", Head -> m_id);
printf("name: %s\n", Head -> m_name);
printf("age: %d\n", Head -> m_age);
printf("next: %p\n",(void*) Head -> m_next);
printf("\n\n");

Head = ListInsertHead(Head ,Pointer3);
printf("Person3\n");
printf("id: %d\n", Head -> m_id);
printf("name: %s\n", Head -> m_name);
printf("age: %d\n", Head -> m_age);
printf("next: %p\n",(void*) Head -> m_next);
printf("\n\n");

/*Head = ListRemoveHead(Head, &item);
printf("After deletion Person3 \n");
printf("id: %d\n", Head -> m_id);
printf("name: %s\n", Head -> m_name);
printf("age: %d\n", Head -> m_age);
printf("next: %p\n",(void*) Head -> m_next);
printf("item: %p\n", (void*) item);*/
printf("\n\n");

Head = ListInsertByKey(Head, 2, Pointer4);
Head = ListInsertByKeyRec(Head, 5555, Pointer5);





PrintList(Head);


}
