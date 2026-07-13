/*
 * Entry: 0048cab4
 * Name: std::_Tree<std::_Tmap_traits<unsigned_long,DistributedObject_*,std::less<unsigned_long>,std::allocator<std::pair<unsigned_long_const_,DistributedObject_*>_>,0>_>::find
 * Namespace: std::_Tree<std::_Tmap_traits<unsigned_long,DistributedObject_*,std::less<unsigned_long>,std::allocator<std::pair<unsigned_long_const_,DistributedObject_*>_>,0>_>
 * Signature: iterator find(_Tree<std::_Tmap_traits<unsigned_long,DistributedObject_*,std::less<unsigned_long>,std::allocator<std::pair<unsigned_long_const_,DistributedObject_*>_>,0>_> * this, ulong * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

iterator __thiscall
std::
_Tree<std::_Tmap_traits<unsigned_long,DistributedObject_*,std::less<unsigned_long>,std::allocator<std::pair<unsigned_long_const_,DistributedObject_*>_>,0>_>
::find(_Tree<std::_Tmap_traits<unsigned_long,DistributedObject_*,std::less<unsigned_long>,std::allocator<std::pair<unsigned_long_const_,DistributedObject_*>_>,0>_>
       *this,ulong *param_1)

{
  ulong uVar1;
  _Node *p_Var2;
  bool bVar3;
  const_iterator *pcVar4;
  iterator iVar5;
  uint *in_stack_00000008;
  const_iterator local_14;
  const_iterator local_c;
  
  lower_bound(this,(ulong *)&local_c);
  const_iterator::const_iterator(&local_14,this->_Myhead,this);
  bVar3 = const_iterator::operator==(&local_c,&local_14);
  if ((bVar3) || (*in_stack_00000008 < ((local_c._Ptr)->_Myval).first)) {
    const_iterator::const_iterator(&local_14,this->_Myhead,this);
    pcVar4 = &local_14;
  }
  else {
    pcVar4 = &local_c;
  }
  uVar1 = pcVar4->_padding_;
  p_Var2 = pcVar4->_Ptr;
  *param_1 = uVar1;
  param_1[1] = (ulong)p_Var2;
  iVar5._4_4_ = uVar1;
  iVar5._0_4_ = param_1;
  return iVar5;
}
