/*
 * Entry: 0048b5f3
 * Name: std::allocator<std::_List_nod<std::pair<unsigned_long_const_,float>,std::allocator<std::pair<unsigned_long_const_,float>_>_>::_Node>::allocate
 * Namespace: std::allocator<std::_List_nod<std::pair<unsigned_long_const_,float>,std::allocator<std::pair<unsigned_long_const_,float>_>_>::_Node>
 * Signature: _Node * allocate(allocator<std::_List_nod<std::pair<unsigned_long_const_,float>,std::allocator<std::pair<unsigned_long_const_,float>_>_>::_Node> * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Node * __thiscall
std::
allocator<std::_List_nod<std::pair<unsigned_long_const_,float>,std::allocator<std::pair<unsigned_long_const_,float>_>_>::_Node>
::allocate(allocator<std::_List_nod<std::pair<unsigned_long_const_,float>,std::allocator<std::pair<unsigned_long_const_,float>_>_>::_Node>
           *this,uint param_1)

{
  _Node *p_Var1;
  
  p_Var1 = _Allocate<std::_List_nod<std::pair<unsigned_long_const_,float>,std::allocator<std::pair<unsigned_long_const_,float>_>_>::_Node>
                     (param_1,(_Node *)0x0);
  return p_Var1;
}
