/*
 * Entry: 004e1915
 * Name: std::_Tree<std::_Tmap_traits<unsigned_short,NetPlayer_*,std::less<unsigned_short>,std::allocator<std::pair<unsigned_short_const_,NetPlayer_*>_>,0>_>::lower_bound
 * Namespace: std::_Tree<std::_Tmap_traits<unsigned_short,NetPlayer_*,std::less<unsigned_short>,std::allocator<std::pair<unsigned_short_const_,NetPlayer_*>_>,0>_>
 * Signature: iterator lower_bound(_Tree<std::_Tmap_traits<unsigned_short,NetPlayer_*,std::less<unsigned_short>,std::allocator<std::pair<unsigned_short_const_,NetPlayer_*>_>,0>_> * this, ushort * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

iterator __thiscall
std::
_Tree<std::_Tmap_traits<unsigned_short,NetPlayer_*,std::less<unsigned_short>,std::allocator<std::pair<unsigned_short_const_,NetPlayer_*>_>,0>_>
::lower_bound(_Tree<std::_Tmap_traits<unsigned_short,NetPlayer_*,std::less<unsigned_short>,std::allocator<std::pair<unsigned_short_const_,NetPlayer_*>_>,0>_>
              *this,ushort *param_1)

{
  _Node *p_Var1;
  undefined4 extraout_EDX;
  iterator iVar2;
  ushort *in_stack_00000008;
  
  p_Var1 = _Lbound(this,in_stack_00000008);
  const_iterator::const_iterator((const_iterator *)param_1,p_Var1,this);
  iVar2._4_4_ = extraout_EDX;
  iVar2._0_4_ = param_1;
  return iVar2;
}
