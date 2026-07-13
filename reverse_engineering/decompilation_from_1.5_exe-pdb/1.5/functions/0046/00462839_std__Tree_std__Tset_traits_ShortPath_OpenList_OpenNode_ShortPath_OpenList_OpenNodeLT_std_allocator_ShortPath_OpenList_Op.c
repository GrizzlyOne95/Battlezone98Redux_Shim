/*
 * Entry: 00462839
 * Name: std::_Tree<std::_Tset_traits<ShortPath::OpenList::OpenNode,ShortPath::OpenList::OpenNodeLT,std::allocator<ShortPath::OpenList::OpenNode>,1>_>::insert
 * Namespace: std::_Tree<std::_Tset_traits<ShortPath::OpenList::OpenNode,ShortPath::OpenList::OpenNodeLT,std::allocator<ShortPath::OpenList::OpenNode>,1>_>
 * Signature: pair<std::_Tree<std::_Tset_traits<ShortPath::OpenList::OpenNode,ShortPath::OpenList::OpenNodeLT,std::allocator<ShortPath::OpenList::OpenNode>,1>_>::iterator,bool> * insert(_Tree<std::_Tset_traits<ShortPath::OpenList::OpenNode,ShortPath::OpenList::OpenNodeLT,std::allocator<ShortPath::OpenList::OpenNode>,1>_> * this, pair<std::_Tree<std::_Tset_traits<ShortPath::OpenList::OpenNode,ShortPath::OpenList::OpenNodeLT,std::allocator<ShortPath::OpenList::OpenNode>,1>_>::iterator,bool> * __return_storage_ptr__, OpenNode * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

pair<std::_Tree<std::_Tset_traits<ShortPath::OpenList::OpenNode,ShortPath::OpenList::OpenNodeLT,std::allocator<ShortPath::OpenList::OpenNode>,1>_>::iterator,bool>
* __thiscall
std::
_Tree<std::_Tset_traits<ShortPath::OpenList::OpenNode,ShortPath::OpenList::OpenNodeLT,std::allocator<ShortPath::OpenList::OpenNode>,1>_>
::insert(_Tree<std::_Tset_traits<ShortPath::OpenList::OpenNode,ShortPath::OpenList::OpenNodeLT,std::allocator<ShortPath::OpenList::OpenNode>,1>_>
         *this,pair<std::_Tree<std::_Tset_traits<ShortPath::OpenList::OpenNode,ShortPath::OpenList::OpenNodeLT,std::allocator<ShortPath::OpenList::OpenNode>,1>_>::iterator,bool>
               *__return_storage_ptr__,OpenNode *param_1)

{
  undefined4 uVar1;
  bool bVar2;
  _Node *p_Var3;
  iterator iVar4;
  _Node *local_c;
  _Node *local_8;
  
  local_c = (_Node *)CONCAT31(local_c._1_3_,1);
  p_Var3 = this->_Myhead->_Parent;
  local_8 = this->_Myhead;
  while (p_Var3->_Isnil == '\0') {
    bVar2 = ShortPath::OpenList::OpenNodeLT::operator()
                      ((OpenNodeLT *)&this->_padding_,*param_1,p_Var3->_Myval);
    local_c = (_Node *)CONCAT31(local_c._1_3_,bVar2);
    local_8 = p_Var3;
    if (bVar2) {
      p_Var3 = p_Var3->_Left;
    }
    else {
      p_Var3 = p_Var3->_Right;
    }
  }
  iVar4 = _Insert(this,true,local_c,(OpenNode *)local_8);
  uVar1 = *iVar4._0_4_;
  *(undefined4 *)&(__return_storage_ptr__->first).field_0x4 = iVar4._0_4_[1];
  *(undefined4 *)&__return_storage_ptr__->first = uVar1;
  __return_storage_ptr__->second = true;
  return __return_storage_ptr__;
}
