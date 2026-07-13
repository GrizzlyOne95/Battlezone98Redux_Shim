/*
 * Entry: 004629c7
 * Name: std::multiset<ShortPath::OpenList::OpenNode,ShortPath::OpenList::OpenNodeLT,std::allocator<ShortPath::OpenList::OpenNode>_>::insert
 * Namespace: std::multiset<ShortPath::OpenList::OpenNode,ShortPath::OpenList::OpenNodeLT,std::allocator<ShortPath::OpenList::OpenNode>_>
 * Signature: iterator insert(multiset<ShortPath::OpenList::OpenNode,ShortPath::OpenList::OpenNodeLT,std::allocator<ShortPath::OpenList::OpenNode>_> * this, OpenNode * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

iterator __thiscall
std::
multiset<ShortPath::OpenList::OpenNode,ShortPath::OpenList::OpenNodeLT,std::allocator<ShortPath::OpenList::OpenNode>_>
::insert(multiset<ShortPath::OpenList::OpenNode,ShortPath::OpenList::OpenNodeLT,std::allocator<ShortPath::OpenList::OpenNode>_>
         *this,OpenNode *param_1)

{
  Node *pNVar1;
  pair<std::_Tree<std::_Tset_traits<ShortPath::OpenList::OpenNode,ShortPath::OpenList::OpenNodeLT,std::allocator<ShortPath::OpenList::OpenNode>,1>_>::iterator,bool>
  *ppVar2;
  iterator iVar3;
  OpenNode *in_stack_00000008;
  pair<std::_Tree<std::_Tset_traits<ShortPath::OpenList::OpenNode,ShortPath::OpenList::OpenNodeLT,std::allocator<ShortPath::OpenList::OpenNode>,1>_>::iterator,bool>
  local_10;
  
  ppVar2 = _Tree<std::_Tset_traits<ShortPath::OpenList::OpenNode,ShortPath::OpenList::OpenNodeLT,std::allocator<ShortPath::OpenList::OpenNode>,1>_>
           ::insert((_Tree<std::_Tset_traits<ShortPath::OpenList::OpenNode,ShortPath::OpenList::OpenNodeLT,std::allocator<ShortPath::OpenList::OpenNode>,1>_>
                     *)this,&local_10,in_stack_00000008);
  pNVar1 = *(Node **)&ppVar2->first;
  param_1->g = *(float *)&(ppVar2->first).field_0x4;
  param_1->m_Node = pNVar1;
  iVar3._4_4_ = pNVar1;
  iVar3._0_4_ = param_1;
  return iVar3;
}
