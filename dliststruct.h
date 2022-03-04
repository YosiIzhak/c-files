static void PushNode(Node *_node, Node *_next);
static void PopNode(Node *_node);

struct Node
{
void*     m_data;
Node*     m_next;
Node*     m_prev;
};
struct List
{
Node m_head;
Node m_tail;

};
