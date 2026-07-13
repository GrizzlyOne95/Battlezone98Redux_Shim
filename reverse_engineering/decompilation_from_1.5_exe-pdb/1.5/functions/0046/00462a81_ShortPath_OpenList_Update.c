/*
 * Entry: 00462a81
 * Name: ShortPath::OpenList::Update
 * Namespace: ShortPath::OpenList
 * Signature: void Update(Node * param_1, float param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl ShortPath::OpenList::Update(Node *param_1,float param_2)

{
  const_iterator cVar1;
  bool bVar2;
  OpenNode *pOVar3;
  undefined1 local_14 [12];
  _Node *local_8;
  
  std::
  _Tree<std::_Tset_traits<ShortPath::OpenList::OpenNode,ShortPath::OpenList::OpenNodeLT,std::allocator<ShortPath::OpenList::OpenNode>,1>_>
  ::const_iterator::const_iterator
            ((const_iterator *)local_14,*(_Node **)g_OpenNodes._24_4_,
             (_Tree<std::_Tset_traits<ShortPath::OpenList::OpenNode,ShortPath::OpenList::OpenNodeLT,std::allocator<ShortPath::OpenList::OpenNode>,1>_>
              *)&g_OpenNodes);
  local_14._8_4_ = local_14._0_4_;
  local_8 = (_Node *)local_14._4_4_;
  while( true ) {
    std::
    _Tree<std::_Tset_traits<ShortPath::OpenList::OpenNode,ShortPath::OpenList::OpenNodeLT,std::allocator<ShortPath::OpenList::OpenNode>,1>_>
    ::const_iterator::const_iterator
              ((const_iterator *)local_14,(_Node *)g_OpenNodes._24_4_,
               (_Tree<std::_Tset_traits<ShortPath::OpenList::OpenNode,ShortPath::OpenList::OpenNodeLT,std::allocator<ShortPath::OpenList::OpenNode>,1>_>
                *)&g_OpenNodes);
    bVar2 = std::
            _Tree<std::_Tset_traits<ShortPath::OpenList::OpenNode,ShortPath::OpenList::OpenNodeLT,std::allocator<ShortPath::OpenList::OpenNode>,1>_>
            ::const_iterator::operator==
                      ((const_iterator *)(local_14 + 8),(const_iterator *)local_14);
    if (bVar2) {
      return;
    }
    pOVar3 = std::
             _Tree<std::_Tset_traits<ShortPath::OpenList::OpenNode,ShortPath::OpenList::OpenNodeLT,std::allocator<ShortPath::OpenList::OpenNode>,1>_>
             ::const_iterator::operator*((const_iterator *)(local_14 + 8));
    if (pOVar3->m_Node == param_1) break;
    std::
    _Tree<std::_Tset_traits<ShortPath::OpenList::OpenNode,ShortPath::OpenList::OpenNodeLT,std::allocator<ShortPath::OpenList::OpenNode>,1>_>
    ::const_iterator::_Inc((const_iterator *)(local_14 + 8));
  }
  std::
  _Tree<std::_Tset_traits<ShortPath::OpenList::OpenNode,ShortPath::OpenList::OpenNodeLT,std::allocator<ShortPath::OpenList::OpenNode>,1>_>
  ::const_iterator::operator*((const_iterator *)(local_14 + 8));
  cVar1._Ptr = (_Node *)local_14._8_4_;
  cVar1._padding_ = (int)local_14;
  std::
  _Tree<std::_Tset_traits<ShortPath::OpenList::OpenNode,ShortPath::OpenList::OpenNodeLT,std::allocator<ShortPath::OpenList::OpenNode>,1>_>
  ::erase((_Tree<std::_Tset_traits<ShortPath::OpenList::OpenNode,ShortPath::OpenList::OpenNodeLT,std::allocator<ShortPath::OpenList::OpenNode>,1>_>
           *)&g_OpenNodes,cVar1);
  std::
  multiset<ShortPath::OpenList::OpenNode,ShortPath::OpenList::OpenNodeLT,std::allocator<ShortPath::OpenList::OpenNode>_>
  ::insert(&g_OpenNodes,(OpenNode *)local_14);
  return;
}
