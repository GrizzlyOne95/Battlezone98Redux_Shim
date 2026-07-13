/*
 * Entry: 0047cd12
 * Name: std::_Tree<std::_Tmap_traits<unsigned_long,DistributedObject_*,std::less<unsigned_long>,std::allocator<std::pair<unsigned_long_const_,DistributedObject_*>_>,0>_>::_Erase
 * Namespace: std::_Tree<std::_Tmap_traits<unsigned_long,DistributedObject_*,std::less<unsigned_long>,std::allocator<std::pair<unsigned_long_const_,DistributedObject_*>_>,0>_>
 * Signature: void _Erase(_Tree<std::_Tmap_traits<unsigned_long,DistributedObject_*,std::less<unsigned_long>,std::allocator<std::pair<unsigned_long_const_,DistributedObject_*>_>,0>_> * this, _Node * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::
_Tree<std::_Tmap_traits<unsigned_long,DistributedObject_*,std::less<unsigned_long>,std::allocator<std::pair<unsigned_long_const_,DistributedObject_*>_>,0>_>
::_Erase(_Tree<std::_Tmap_traits<unsigned_long,DistributedObject_*,std::less<unsigned_long>,std::allocator<std::pair<unsigned_long_const_,DistributedObject_*>_>,0>_>
         *this,_Node *param_1)

{
  char cVar1;
  _Node *p_Var2;
  
  cVar1 = param_1->_Isnil;
  while (cVar1 == '\0') {
    _Erase(this,param_1->_Right);
    p_Var2 = param_1->_Left;
    operator_delete(param_1);
    param_1 = p_Var2;
    cVar1 = p_Var2->_Isnil;
  }
  return;
}
