/*
 * Entry: 005ca4eb
 * Name: ShortPath::OpenList::`dynamic_initializer_for_'g_OpenNodes''
 * Namespace: ShortPath::OpenList
 * Signature: void `dynamic_initializer_for_'g_OpenNodes''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl ShortPath::OpenList::_dynamic_initializer_for__g_OpenNodes__(void)

{
  std::
  multiset<ShortPath::OpenList::OpenNode,ShortPath::OpenList::OpenNodeLT,std::allocator<ShortPath::OpenList::OpenNode>_>
  ::
  multiset<ShortPath::OpenList::OpenNode,ShortPath::OpenList::OpenNodeLT,std::allocator<ShortPath::OpenList::OpenNode>_>
            (&g_OpenNodes);
  atexit(_dynamic_atexit_destructor_for__g_OpenNodes__);
  return;
}
