/*
 * Entry: 004e120c
 * Name: std::allocator<std::_Tree_nod<std::_Tmap_traits<unsigned_short,NetPlayer_*,std::less<unsigned_short>,std::allocator<std::pair<unsigned_short_const_,NetPlayer_*>_>,0>_>::_Node_*>::construct
 * Namespace: std::allocator<std::_Tree_nod<std::_Tmap_traits<unsigned_short,NetPlayer_*,std::less<unsigned_short>,std::allocator<std::pair<unsigned_short_const_,NetPlayer_*>_>,0>_>::_Node_*>
 * Signature: void construct(allocator<std::_Tree_nod<std::_Tmap_traits<unsigned_short,NetPlayer_*,std::less<unsigned_short>,std::allocator<std::pair<unsigned_short_const_,NetPlayer_*>_>,0>_>::_Node_*> * this, _Node * * param_1, _Node * * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::
allocator<std::_Tree_nod<std::_Tmap_traits<unsigned_short,NetPlayer_*,std::less<unsigned_short>,std::allocator<std::pair<unsigned_short_const_,NetPlayer_*>_>,0>_>::_Node_*>
::construct(allocator<std::_Tree_nod<std::_Tmap_traits<unsigned_short,NetPlayer_*,std::less<unsigned_short>,std::allocator<std::pair<unsigned_short_const_,NetPlayer_*>_>,0>_>::_Node_*>
            *this,_Node **param_1,_Node **param_2)

{
  if (param_1 != (_Node **)0x0) {
    *param_1 = *param_2;
  }
  return;
}
