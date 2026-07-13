/*
 * Entry: 005341d1
 * Name: std::_Tree<std::_Tmap_traits<std::pair<unsigned_short,unsigned_short>,Ordnance_*,std::less<std::pair<unsigned_short,unsigned_short>_>,std::allocator<std::pair<std::pair<unsigned_short,unsigned_short>_const_,Ordnance_*>_>,0>_>::lower_bound
 * Namespace: std::_Tree<std::_Tmap_traits<std::pair<unsigned_short,unsigned_short>,Ordnance_*,std::less<std::pair<unsigned_short,unsigned_short>_>,std::allocator<std::pair<std::pair<unsigned_short,unsigned_short>_const_,Ordnance_*>_>,0>_>
 * Signature: iterator lower_bound(_Tree<std::_Tmap_traits<std::pair<unsigned_short,unsigned_short>,Ordnance_*,std::less<std::pair<unsigned_short,unsigned_short>_>,std::allocator<std::pair<std::pair<unsigned_short,unsigned_short>_const_,Ordnance_*>_>,0>_> * this, pair<unsigned_short,unsigned_short> * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

iterator __thiscall
std::
_Tree<std::_Tmap_traits<std::pair<unsigned_short,unsigned_short>,Ordnance_*,std::less<std::pair<unsigned_short,unsigned_short>_>,std::allocator<std::pair<std::pair<unsigned_short,unsigned_short>_const_,Ordnance_*>_>,0>_>
::lower_bound(_Tree<std::_Tmap_traits<std::pair<unsigned_short,unsigned_short>,Ordnance_*,std::less<std::pair<unsigned_short,unsigned_short>_>,std::allocator<std::pair<std::pair<unsigned_short,unsigned_short>_const_,Ordnance_*>_>,0>_>
              *this,pair<unsigned_short,unsigned_short> *param_1)

{
  _Node *p_Var1;
  undefined4 extraout_EDX;
  iterator iVar2;
  pair<unsigned_short,unsigned_short> *in_stack_00000008;
  
  p_Var1 = _Lbound(this,in_stack_00000008);
  const_iterator::const_iterator((const_iterator *)param_1,p_Var1,this);
  iVar2._4_4_ = extraout_EDX;
  iVar2._0_4_ = param_1;
  return iVar2;
}
