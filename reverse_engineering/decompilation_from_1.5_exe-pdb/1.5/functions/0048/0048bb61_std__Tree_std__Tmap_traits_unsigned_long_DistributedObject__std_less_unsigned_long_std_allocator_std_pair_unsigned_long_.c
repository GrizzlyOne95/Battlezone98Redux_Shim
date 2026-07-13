/*
 * Entry: 0048bb61
 * Name: std::_Tree<std::_Tmap_traits<unsigned_long,DistributedObject_*,std::less<unsigned_long>,std::allocator<std::pair<unsigned_long_const_,DistributedObject_*>_>,0>_>::_Eqrange
 * Namespace: std::_Tree<std::_Tmap_traits<unsigned_long,DistributedObject_*,std::less<unsigned_long>,std::allocator<std::pair<unsigned_long_const_,DistributedObject_*>_>,0>_>
 * Signature: pair<std::_Tree<std::_Tmap_traits<unsigned_long,DistributedObject_*,std::less<unsigned_long>,std::allocator<std::pair<unsigned_long_const_,DistributedObject_*>_>,0>_>::iterator,std::_Tree<std::_Tmap_traits<unsigned_long,DistributedObject_*,std::less<unsigned_long>,std::allocator<std::pair<unsigned_long_const_,DistributedObject_*>_>,0>_>::iterator> * _Eqrange(_Tree<std::_Tmap_traits<unsigned_long,DistributedObject_*,std::less<unsigned_long>,std::allocator<std::pair<unsigned_long_const_,DistributedObject_*>_>,0>_> * this, pair<std::_Tree<std::_Tmap_traits<unsigned_long,DistributedObject_*,std::less<unsigned_long>,std::allocator<std::pair<unsigned_long_const_,DistributedObject_*>_>,0>_>::iterator,std::_Tree<std::_Tmap_traits<unsigned_long,DistributedObject_*,std::less<unsigned_long>,std::allocator<std::pair<unsigned_long_const_,DistributedObject_*>_>,0>_>::iterator> * __return_storage_ptr__, ulong * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

pair<std::_Tree<std::_Tmap_traits<unsigned_long,DistributedObject_*,std::less<unsigned_long>,std::allocator<std::pair<unsigned_long_const_,DistributedObject_*>_>,0>_>::iterator,std::_Tree<std::_Tmap_traits<unsigned_long,DistributedObject_*,std::less<unsigned_long>,std::allocator<std::pair<unsigned_long_const_,DistributedObject_*>_>,0>_>::iterator>
* __thiscall
std::
_Tree<std::_Tmap_traits<unsigned_long,DistributedObject_*,std::less<unsigned_long>,std::allocator<std::pair<unsigned_long_const_,DistributedObject_*>_>,0>_>
::_Eqrange(_Tree<std::_Tmap_traits<unsigned_long,DistributedObject_*,std::less<unsigned_long>,std::allocator<std::pair<unsigned_long_const_,DistributedObject_*>_>,0>_>
           *this,pair<std::_Tree<std::_Tmap_traits<unsigned_long,DistributedObject_*,std::less<unsigned_long>,std::allocator<std::pair<unsigned_long_const_,DistributedObject_*>_>,0>_>::iterator,std::_Tree<std::_Tmap_traits<unsigned_long,DistributedObject_*,std::less<unsigned_long>,std::allocator<std::pair<unsigned_long_const_,DistributedObject_*>_>,0>_>::iterator>
                 *__return_storage_ptr__,ulong *param_1)

{
  uint uVar1;
  _Node *p_Var2;
  _Node *p_Var3;
  _Node *p_Var4;
  const_iterator local_14;
  const_iterator local_c;
  
  p_Var4 = this->_Myhead;
  local_c._Ptr = p_Var4;
  if (p_Var4->_Parent->_Isnil == '\0') {
    p_Var2 = p_Var4->_Parent;
    do {
      uVar1 = (p_Var2->_Myval).first;
      if (uVar1 < *param_1) {
        p_Var3 = p_Var2->_Right;
      }
      else {
        if ((p_Var4->_Isnil != '\0') && (*param_1 < uVar1)) {
          p_Var4 = p_Var2;
        }
        p_Var3 = p_Var2->_Left;
        local_c._Ptr = p_Var2;
      }
      p_Var2 = p_Var3;
    } while (p_Var3->_Isnil == '\0');
  }
  if (p_Var4->_Isnil == '\0') {
    p_Var2 = p_Var4->_Left;
  }
  else {
    p_Var2 = this->_Myhead->_Parent;
  }
  if (p_Var2->_Isnil == '\0') {
    do {
      if (*param_1 < (p_Var2->_Myval).first) {
        p_Var3 = p_Var2->_Left;
        p_Var4 = p_Var2;
      }
      else {
        p_Var3 = p_Var2->_Right;
      }
      p_Var2 = p_Var3;
    } while (p_Var3->_Isnil == '\0');
  }
  const_iterator::const_iterator(&local_c,local_c._Ptr,this);
  const_iterator::const_iterator(&local_14,p_Var4,this);
  *(int *)&__return_storage_ptr__->first = local_c._padding_;
  *(_Node **)&(__return_storage_ptr__->first).field_0x4 = local_c._Ptr;
  *(int *)&__return_storage_ptr__->second = local_14._padding_;
  *(_Node **)&(__return_storage_ptr__->second).field_0x4 = local_14._Ptr;
  return __return_storage_ptr__;
}
