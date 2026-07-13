/*
 * Entry: 00462a4f
 * Name: ShortPath::OpenList::Insert
 * Namespace: ShortPath::OpenList
 * Signature: void Insert(Node * param_1, float param_2, float param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl ShortPath::OpenList::Insert(Node *param_1,float param_2,float param_3)

{
  std::
  multiset<ShortPath::OpenList::OpenNode,ShortPath::OpenList::OpenNodeLT,std::allocator<ShortPath::OpenList::OpenNode>_>
  ::insert(&g_OpenNodes,(OpenNode *)&stack0xfffffff4);
  param_1->open = true;
  return;
}
