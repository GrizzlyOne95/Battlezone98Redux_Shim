/*
 * Entry: 0047ccf8
 * Name: std::_Tree<std::_Tmap_traits<unsigned_long,DistributedObject_*,std::less<unsigned_long>,std::allocator<std::pair<unsigned_long_const_,DistributedObject_*>_>,0>_>::const_iterator::operator++
 * Namespace: std::_Tree<std::_Tmap_traits<unsigned_long,DistributedObject_*,std::less<unsigned_long>,std::allocator<std::pair<unsigned_long_const_,DistributedObject_*>_>,0>_>::const_iterator
 * Signature: const_iterator operator++(const_iterator * this, int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

const_iterator __thiscall
std::
_Tree<std::_Tmap_traits<unsigned_long,DistributedObject_*,std::less<unsigned_long>,std::allocator<std::pair<unsigned_long_const_,DistributedObject_*>_>,0>_>
::const_iterator::operator++(const_iterator *this,int param_1)

{
  _Node *extraout_EDX;
  const_iterator cVar1;
  
  *(int *)param_1 = this->_padding_;
  *(_Node **)(param_1 + 4) = this->_Ptr;
  _Inc(this);
  cVar1._Ptr = extraout_EDX;
  cVar1._padding_ = param_1;
  return cVar1;
}
