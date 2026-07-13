/*
 * Entry: 004091c4
 * Name: std::_Tree<std::_Tmap_traits<GameObject_*,Area,std::less<GameObject_*>,std::allocator<std::pair<GameObject_*_const,Area>_>,0>_>::_Make_iter
 * Namespace: std::_Tree<std::_Tmap_traits<GameObject_*,Area,std::less<GameObject_*>,std::allocator<std::pair<GameObject_*_const,Area>_>,0>_>
 * Signature: iterator _Make_iter(_Tree<std::_Tmap_traits<GameObject_*,Area,std::less<GameObject_*>,std::allocator<std::pair<GameObject_*_const,Area>_>,0>_> * this, const_iterator param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

iterator __thiscall
std::
_Tree<std::_Tmap_traits<GameObject_*,Area,std::less<GameObject_*>,std::allocator<std::pair<GameObject_*_const,Area>_>,0>_>
::_Make_iter(_Tree<std::_Tmap_traits<GameObject_*,Area,std::less<GameObject_*>,std::allocator<std::pair<GameObject_*_const,Area>_>,0>_>
             *this,const_iterator param_1)

{
  undefined4 extraout_EDX;
  iterator iVar1;
  _Node *in_stack_0000000c;
  const_iterator local_c;
  
  local_c._padding_ = (int)this;
  local_c._Ptr = (_Node *)this;
  const_iterator::const_iterator(&local_c,in_stack_0000000c,this);
  *(int *)param_1._padding_ = local_c._padding_;
  *(_Node **)(param_1._padding_ + 4) = local_c._Ptr;
  iVar1._4_4_ = extraout_EDX;
  iVar1._0_4_ = param_1._padding_;
  return iVar1;
}
