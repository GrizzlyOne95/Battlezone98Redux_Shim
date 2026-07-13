/*
 * Entry: 00462397
 * Name: ShortPath::OpenList::Clean
 * Namespace: ShortPath::OpenList
 * Signature: void Clean(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl ShortPath::OpenList::Clean(void)

{
  std::
  _Tree<std::_Tset_traits<ShortPath::OpenList::OpenNode,ShortPath::OpenList::OpenNodeLT,std::allocator<ShortPath::OpenList::OpenNode>,1>_>
  ::clear((_Tree<std::_Tset_traits<ShortPath::OpenList::OpenNode,ShortPath::OpenList::OpenNodeLT,std::allocator<ShortPath::OpenList::OpenNode>,1>_>
           *)&g_OpenNodes);
  return;
}
