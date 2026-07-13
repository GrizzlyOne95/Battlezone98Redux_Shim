/*
 * Entry: 005344bf
 * Name: std::_Tree<std::_Tmap_traits<std::pair<unsigned_short,unsigned_short>,Ordnance_*,std::less<std::pair<unsigned_short,unsigned_short>_>,std::allocator<std::pair<std::pair<unsigned_short,unsigned_short>_const_,Ordnance_*>_>,0>_>::insert
 * Namespace: std::_Tree<std::_Tmap_traits<std::pair<unsigned_short,unsigned_short>,Ordnance_*,std::less<std::pair<unsigned_short,unsigned_short>_>,std::allocator<std::pair<std::pair<unsigned_short,unsigned_short>_const_,Ordnance_*>_>,0>_>
 * Signature: pair<std::_Tree<std::_Tmap_traits<std::pair<unsigned_short,unsigned_short>,Ordnance_*,std::less<std::pair<unsigned_short,unsigned_short>_>,std::allocator<std::pair<std::pair<unsigned_short,unsigned_short>_const_,Ordnance_*>_>,0>_>::iterator,bool> * insert(_Tree<std::_Tmap_traits<std::pair<unsigned_short,unsigned_short>,Ordnance_*,std::less<std::pair<unsigned_short,unsigned_short>_>,std::allocator<std::pair<std::pair<unsigned_short,unsigned_short>_const_,Ordnance_*>_>,0>_> * this, pair<std::_Tree<std::_Tmap_traits<std::pair<unsigned_short,unsigned_short>,Ordnance_*,std::less<std::pair<unsigned_short,unsigned_short>_>,std::allocator<std::pair<std::pair<unsigned_short,unsigned_short>_const_,Ordnance_*>_>,0>_>::iterator,bool> * __return_storage_ptr__, pair<std::pair<unsigned_short,unsigned_short>_const_,Ordnance_*> * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Variable defined which should be unmapped: __return_storage_ptr__ */

pair<std::_Tree<std::_Tmap_traits<std::pair<unsigned_short,unsigned_short>,Ordnance_*,std::less<std::pair<unsigned_short,unsigned_short>_>,std::allocator<std::pair<std::pair<unsigned_short,unsigned_short>_const_,Ordnance_*>_>,0>_>::iterator,bool>
* __thiscall
std::
_Tree<std::_Tmap_traits<std::pair<unsigned_short,unsigned_short>,Ordnance_*,std::less<std::pair<unsigned_short,unsigned_short>_>,std::allocator<std::pair<std::pair<unsigned_short,unsigned_short>_const_,Ordnance_*>_>,0>_>
::insert(_Tree<std::_Tmap_traits<std::pair<unsigned_short,unsigned_short>,Ordnance_*,std::less<std::pair<unsigned_short,unsigned_short>_>,std::allocator<std::pair<std::pair<unsigned_short,unsigned_short>_const_,Ordnance_*>_>,0>_>
         *this,pair<std::_Tree<std::_Tmap_traits<std::pair<unsigned_short,unsigned_short>,Ordnance_*,std::less<std::pair<unsigned_short,unsigned_short>_>,std::allocator<std::pair<std::pair<unsigned_short,unsigned_short>_const_,Ordnance_*>_>,0>_>::iterator,bool>
               *__return_storage_ptr__,
        pair<std::pair<unsigned_short,unsigned_short>_const_,Ordnance_*> *param_1)

{
  undefined4 uVar1;
  bool bVar2;
  _Node *p_Var3;
  _Node *p_Var4;
  iterator iVar5;
  const_iterator local_18;
  const_iterator local_10;
  _Node *local_8;
  
  local_8 = (_Node *)CONCAT31(local_8._1_3_,1);
  p_Var3 = this->_Myhead;
  p_Var4 = this->_Myhead->_Parent;
  while (p_Var4->_Isnil == '\0') {
    bVar2 = operator<<unsigned_short,unsigned_short>(&param_1->first,&(p_Var4->_Myval).first);
    local_8 = (_Node *)CONCAT31(local_8._1_3_,bVar2);
    p_Var3 = p_Var4;
    if (bVar2) {
      p_Var4 = p_Var4->_Left;
    }
    else {
      p_Var4 = p_Var4->_Right;
    }
  }
  const_iterator::const_iterator(&local_10,p_Var3,this);
  if ((char)local_8 != '\0') {
    const_iterator::const_iterator(&local_18,this->_Myhead->_Left,this);
    bVar2 = const_iterator::operator==(&local_10,&local_18);
    if (bVar2) {
      p_Var4 = (_Node *)0x1;
      goto LAB_00534530;
    }
    const_iterator::_Dec(&local_10);
  }
  bVar2 = operator<<unsigned_short,unsigned_short>(&((local_10._Ptr)->_Myval).first,&param_1->first)
  ;
  p_Var4 = local_8;
  if (!bVar2) {
    *(int *)&__return_storage_ptr__->first = local_10._padding_;
    *(_Node **)&(__return_storage_ptr__->first).field_0x4 = local_10._Ptr;
    __return_storage_ptr__->second = false;
    return __return_storage_ptr__;
  }
LAB_00534530:
  iVar5 = _Insert(this,SUB41(&local_18,0),p_Var4,
                  (pair<std::pair<unsigned_short,unsigned_short>_const_,Ordnance_*> *)p_Var3);
  uVar1 = iVar5._0_4_[1];
  *(undefined4 *)&__return_storage_ptr__->first = *iVar5._0_4_;
  *(undefined4 *)&(__return_storage_ptr__->first).field_0x4 = uVar1;
  __return_storage_ptr__->second = true;
  return __return_storage_ptr__;
}
