/*
 * Entry: 0053397a
 * Name: std::_Tree<std::_Tmap_traits<std::pair<unsigned_short,unsigned_short>,Ordnance_*,std::less<std::pair<unsigned_short,unsigned_short>_>,std::allocator<std::pair<std::pair<unsigned_short,unsigned_short>_const_,Ordnance_*>_>,0>_>::_Eqrange
 * Namespace: std::_Tree<std::_Tmap_traits<std::pair<unsigned_short,unsigned_short>,Ordnance_*,std::less<std::pair<unsigned_short,unsigned_short>_>,std::allocator<std::pair<std::pair<unsigned_short,unsigned_short>_const_,Ordnance_*>_>,0>_>
 * Signature: pair<std::_Tree<std::_Tmap_traits<std::pair<unsigned_short,unsigned_short>,Ordnance_*,std::less<std::pair<unsigned_short,unsigned_short>_>,std::allocator<std::pair<std::pair<unsigned_short,unsigned_short>_const_,Ordnance_*>_>,0>_>::iterator,std::_Tree<std::_Tmap_traits<std::pair<unsigned_short,unsigned_short>,Ordnance_*,std::less<std::pair<unsigned_short,unsigned_short>_>,std::allocator<std::pair<std::pair<unsigned_short,unsigned_short>_const_,Ordnance_*>_>,0>_>::iterator> * _Eqrange(_Tree<std::_Tmap_traits<std::pair<unsigned_short,unsigned_short>,Ordnance_*,std::less<std::pair<unsigned_short,unsigned_short>_>,std::allocator<std::pair<std::pair<unsigned_short,unsigned_short>_const_,Ordnance_*>_>,0>_> * this, pair<std::_Tree<std::_Tmap_traits<std::pair<unsigned_short,unsigned_short>,Ordnance_*,std::less<std::pair<unsigned_short,unsigned_short>_>,std::allocator<std::pair<std::pair<unsigned_short,unsigned_short>_const_,Ordnance_*>_>,0>_>::iterator,std::_Tree<std::_Tmap_traits<std::pair<unsigned_short,unsigned_short>,Ordnance_*,std::less<std::pair<unsigned_short,unsigned_short>_>,std::allocator<std::pair<std::pair<unsigned_short,unsigned_short>_const_,Ordnance_*>_>,0>_>::iterator> * __return_storage_ptr__, pair<unsigned_short,unsigned_short> * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

pair<std::_Tree<std::_Tmap_traits<std::pair<unsigned_short,unsigned_short>,Ordnance_*,std::less<std::pair<unsigned_short,unsigned_short>_>,std::allocator<std::pair<std::pair<unsigned_short,unsigned_short>_const_,Ordnance_*>_>,0>_>::iterator,std::_Tree<std::_Tmap_traits<std::pair<unsigned_short,unsigned_short>,Ordnance_*,std::less<std::pair<unsigned_short,unsigned_short>_>,std::allocator<std::pair<std::pair<unsigned_short,unsigned_short>_const_,Ordnance_*>_>,0>_>::iterator>
* __thiscall
std::
_Tree<std::_Tmap_traits<std::pair<unsigned_short,unsigned_short>,Ordnance_*,std::less<std::pair<unsigned_short,unsigned_short>_>,std::allocator<std::pair<std::pair<unsigned_short,unsigned_short>_const_,Ordnance_*>_>,0>_>
::_Eqrange(_Tree<std::_Tmap_traits<std::pair<unsigned_short,unsigned_short>,Ordnance_*,std::less<std::pair<unsigned_short,unsigned_short>_>,std::allocator<std::pair<std::pair<unsigned_short,unsigned_short>_const_,Ordnance_*>_>,0>_>
           *this,pair<std::_Tree<std::_Tmap_traits<std::pair<unsigned_short,unsigned_short>,Ordnance_*,std::less<std::pair<unsigned_short,unsigned_short>_>,std::allocator<std::pair<std::pair<unsigned_short,unsigned_short>_const_,Ordnance_*>_>,0>_>::iterator,std::_Tree<std::_Tmap_traits<std::pair<unsigned_short,unsigned_short>,Ordnance_*,std::less<std::pair<unsigned_short,unsigned_short>_>,std::allocator<std::pair<std::pair<unsigned_short,unsigned_short>_const_,Ordnance_*>_>,0>_>::iterator>
                 *__return_storage_ptr__,pair<unsigned_short,unsigned_short> *param_1)

{
  bool bVar1;
  _Node *p_Var2;
  _Node *p_Var3;
  _Node *p_Var4;
  const_iterator local_14;
  const_iterator local_c;
  
  p_Var2 = this->_Myhead;
  p_Var4 = p_Var2->_Parent;
  local_c._Ptr = p_Var2;
  while (p_Var3 = p_Var4, p_Var3->_Isnil == '\0') {
    bVar1 = operator<<unsigned_short,unsigned_short>(&(p_Var3->_Myval).first,param_1);
    if (bVar1) {
      p_Var4 = p_Var3->_Right;
    }
    else {
      if (p_Var2->_Isnil != '\0') {
        bVar1 = operator<<unsigned_short,unsigned_short>(param_1,&(p_Var3->_Myval).first);
        if (bVar1) {
          p_Var2 = p_Var3;
        }
      }
      p_Var4 = p_Var3->_Left;
      local_c._Ptr = p_Var3;
    }
  }
  if (p_Var2->_Isnil == '\0') {
    p_Var4 = p_Var2->_Left;
  }
  else {
    p_Var4 = this->_Myhead->_Parent;
  }
  while (p_Var4->_Isnil == '\0') {
    bVar1 = operator<<unsigned_short,unsigned_short>(param_1,&(p_Var4->_Myval).first);
    if (bVar1) {
      p_Var2 = p_Var4;
      p_Var4 = p_Var4->_Left;
    }
    else {
      p_Var4 = p_Var4->_Right;
    }
  }
  const_iterator::const_iterator(&local_c,local_c._Ptr,this);
  const_iterator::const_iterator(&local_14,p_Var2,this);
  *(int *)&__return_storage_ptr__->first = local_c._padding_;
  *(_Node **)&(__return_storage_ptr__->first).field_0x4 = local_c._Ptr;
  *(int *)&__return_storage_ptr__->second = local_14._padding_;
  *(_Node **)&(__return_storage_ptr__->second).field_0x4 = local_14._Ptr;
  return __return_storage_ptr__;
}
