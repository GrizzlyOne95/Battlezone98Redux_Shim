/*
 * Entry: 0048ce49
 * Name: std::_Tree<std::_Tmap_traits<unsigned_long,DistributedObject_*,std::less<unsigned_long>,std::allocator<std::pair<unsigned_long_const_,DistributedObject_*>_>,0>_>::insert
 * Namespace: std::_Tree<std::_Tmap_traits<unsigned_long,DistributedObject_*,std::less<unsigned_long>,std::allocator<std::pair<unsigned_long_const_,DistributedObject_*>_>,0>_>
 * Signature: pair<std::_Tree<std::_Tmap_traits<unsigned_long,DistributedObject_*,std::less<unsigned_long>,std::allocator<std::pair<unsigned_long_const_,DistributedObject_*>_>,0>_>::iterator,bool> * insert(_Tree<std::_Tmap_traits<unsigned_long,DistributedObject_*,std::less<unsigned_long>,std::allocator<std::pair<unsigned_long_const_,DistributedObject_*>_>,0>_> * this, pair<std::_Tree<std::_Tmap_traits<unsigned_long,DistributedObject_*,std::less<unsigned_long>,std::allocator<std::pair<unsigned_long_const_,DistributedObject_*>_>,0>_>::iterator,bool> * __return_storage_ptr__, pair<unsigned_long_const_,DistributedObject_*> * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Variable defined which should be unmapped: __return_storage_ptr__ */

pair<std::_Tree<std::_Tmap_traits<unsigned_long,DistributedObject_*,std::less<unsigned_long>,std::allocator<std::pair<unsigned_long_const_,DistributedObject_*>_>,0>_>::iterator,bool>
* __thiscall
std::
_Tree<std::_Tmap_traits<unsigned_long,DistributedObject_*,std::less<unsigned_long>,std::allocator<std::pair<unsigned_long_const_,DistributedObject_*>_>,0>_>
::insert(_Tree<std::_Tmap_traits<unsigned_long,DistributedObject_*,std::less<unsigned_long>,std::allocator<std::pair<unsigned_long_const_,DistributedObject_*>_>,0>_>
         *this,pair<std::_Tree<std::_Tmap_traits<unsigned_long,DistributedObject_*,std::less<unsigned_long>,std::allocator<std::pair<unsigned_long_const_,DistributedObject_*>_>,0>_>::iterator,bool>
               *__return_storage_ptr__,pair<unsigned_long_const_,DistributedObject_*> *param_1)

{
  _Node *p_Var1;
  _Node *p_Var2;
  bool bVar3;
  iterator iVar4;
  const_iterator local_18;
  const_iterator local_10;
  _Node *local_8;
  
  p_Var2 = this->_Myhead;
  local_8 = (_Node *)CONCAT31(local_8._1_3_,1);
  if (p_Var2->_Parent->_Isnil == '\0') {
    p_Var1 = p_Var2->_Parent;
    do {
      p_Var2 = p_Var1;
      bVar3 = param_1->first < (p_Var2->_Myval).first;
      local_8 = (_Node *)CONCAT31(local_8._1_3_,bVar3);
      if (bVar3) {
        p_Var1 = p_Var2->_Left;
      }
      else {
        p_Var1 = p_Var2->_Right;
      }
    } while (p_Var1->_Isnil == '\0');
  }
  const_iterator::const_iterator(&local_10,p_Var2,this);
  if ((char)local_8 == '\0') {
LAB_0048cedc:
    p_Var1 = local_8;
    if (param_1->first <= ((local_10._Ptr)->_Myval).first) {
      __return_storage_ptr__->second = false;
      goto LAB_0048cef7;
    }
  }
  else {
    const_iterator::const_iterator(&local_18,this->_Myhead->_Left,this);
    bVar3 = const_iterator::operator==(&local_10,&local_18);
    if (!bVar3) {
      const_iterator::_Dec(&local_10);
      goto LAB_0048cedc;
    }
    p_Var1 = (_Node *)0x1;
  }
  iVar4 = _Insert(this,SUB41(&local_18,0),p_Var1,
                  (pair<unsigned_long_const_,DistributedObject_*> *)p_Var2);
  local_10._padding_ = *iVar4._0_4_;
  local_10._Ptr = (_Node *)iVar4._0_4_[1];
  __return_storage_ptr__->second = true;
LAB_0048cef7:
  *(int *)&__return_storage_ptr__->first = local_10._padding_;
  *(_Node **)&(__return_storage_ptr__->first).field_0x4 = local_10._Ptr;
  return __return_storage_ptr__;
}
