/*
 * Entry: 005cc76d
 * Name: ShortPath::OpenList::`dynamic_atexit_destructor_for_'g_OpenNodes''
 * Namespace: ShortPath::OpenList
 * Signature: void `dynamic_atexit_destructor_for_'g_OpenNodes''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl ShortPath::OpenList::_dynamic_atexit_destructor_for__g_OpenNodes__(void)

{
  std::
  _Tree<std::_Tset_traits<ShortPath::OpenList::OpenNode,ShortPath::OpenList::OpenNodeLT,std::allocator<ShortPath::OpenList::OpenNode>,1>_>
  ::_Tidy((_Tree<std::_Tset_traits<ShortPath::OpenList::OpenNode,ShortPath::OpenList::OpenNodeLT,std::allocator<ShortPath::OpenList::OpenNode>,1>_>
           *)&g_OpenNodes);
  operator_delete((void *)g_OpenNodes._0_4_);
  return;
}
