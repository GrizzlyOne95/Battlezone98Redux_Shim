/*
 * Entry: 00462979
 * Name: ShortPath::OpenList::First
 * Namespace: ShortPath::OpenList
 * Signature: Node * First(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Node * __cdecl ShortPath::OpenList::First(void)

{
  Node *pNVar1;
  const_iterator cVar2;
  OpenNode *pOVar3;
  const_iterator local_c;
  
  if (g_OpenNodes._28_4_ == 0) {
    return (Node *)0x0;
  }
  std::
  _Tree<std::_Tset_traits<ShortPath::OpenList::OpenNode,ShortPath::OpenList::OpenNodeLT,std::allocator<ShortPath::OpenList::OpenNode>,1>_>
  ::const_iterator::const_iterator
            (&local_c,*(_Node **)g_OpenNodes._24_4_,
             (_Tree<std::_Tset_traits<ShortPath::OpenList::OpenNode,ShortPath::OpenList::OpenNodeLT,std::allocator<ShortPath::OpenList::OpenNode>,1>_>
              *)&g_OpenNodes);
  pOVar3 = std::
           _Tree<std::_Tset_traits<ShortPath::OpenList::OpenNode,ShortPath::OpenList::OpenNodeLT,std::allocator<ShortPath::OpenList::OpenNode>,1>_>
           ::const_iterator::operator*(&local_c);
  pNVar1 = pOVar3->m_Node;
  cVar2._Ptr = (_Node *)local_c._padding_;
  cVar2._padding_ = (int)&local_c;
  std::
  _Tree<std::_Tset_traits<ShortPath::OpenList::OpenNode,ShortPath::OpenList::OpenNodeLT,std::allocator<ShortPath::OpenList::OpenNode>,1>_>
  ::erase((_Tree<std::_Tset_traits<ShortPath::OpenList::OpenNode,ShortPath::OpenList::OpenNodeLT,std::allocator<ShortPath::OpenList::OpenNode>,1>_>
           *)&g_OpenNodes,cVar2);
  pNVar1->open = false;
  return pNVar1;
}
