/*
 * Entry: 00461d9c
 * Name: std::pair<std::_Tree<std::_Tset_traits<ShortPath::OpenList::OpenNode,ShortPath::OpenList::OpenNodeLT,std::allocator<ShortPath::OpenList::OpenNode>,1>_>::iterator,bool>::pair<std::_Tree<std::_Tset_traits<ShortPath::OpenList::OpenNode,ShortPath::OpenList::OpenNodeLT,std::allocator<ShortPath::OpenList::OpenNode>,1>_>::iterator,bool>
 * Namespace: std::pair<std::_Tree<std::_Tset_traits<ShortPath::OpenList::OpenNode,ShortPath::OpenList::OpenNodeLT,std::allocator<ShortPath::OpenList::OpenNode>,1>_>::iterator,bool>
 * Signature: pair<std::_Tree<std::_Tset_traits<ShortPath::OpenList::OpenNode,ShortPath::OpenList::OpenNodeLT,std::allocator<ShortPath::OpenList::OpenNode>,1>_>::iterator,bool> * pair<std::_Tree<std::_Tset_traits<ShortPath::OpenList::OpenNode,ShortPath::OpenList::OpenNodeLT,std::allocator<ShortPath::OpenList::OpenNode>,1>_>::iterator,bool>(pair<std::_Tree<std::_Tset_traits<ShortPath::OpenList::OpenNode,ShortPath::OpenList::OpenNodeLT,std::allocator<ShortPath::OpenList::OpenNode>,1>_>::iterator,bool> * this, iterator * param_1, bool * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

pair<std::_Tree<std::_Tset_traits<ShortPath::OpenList::OpenNode,ShortPath::OpenList::OpenNodeLT,std::allocator<ShortPath::OpenList::OpenNode>,1>_>::iterator,bool>
* __thiscall
std::
pair<std::_Tree<std::_Tset_traits<ShortPath::OpenList::OpenNode,ShortPath::OpenList::OpenNodeLT,std::allocator<ShortPath::OpenList::OpenNode>,1>_>::iterator,bool>
::
pair<std::_Tree<std::_Tset_traits<ShortPath::OpenList::OpenNode,ShortPath::OpenList::OpenNodeLT,std::allocator<ShortPath::OpenList::OpenNode>,1>_>::iterator,bool>
          (pair<std::_Tree<std::_Tset_traits<ShortPath::OpenList::OpenNode,ShortPath::OpenList::OpenNodeLT,std::allocator<ShortPath::OpenList::OpenNode>,1>_>::iterator,bool>
           *this,iterator *param_1,bool *param_2)

{
  *(undefined4 *)&this->first = *(undefined4 *)param_1;
  *(undefined4 *)&(this->first).field_0x4 = *(undefined4 *)&param_1->field_0x4;
  this->second = *param_2;
  return this;
}
