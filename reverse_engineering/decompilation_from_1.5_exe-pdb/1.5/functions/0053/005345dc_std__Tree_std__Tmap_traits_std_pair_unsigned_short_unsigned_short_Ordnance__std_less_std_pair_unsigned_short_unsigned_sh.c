/*
 * Entry: 005345dc
 * Name: std::_Tree<std::_Tmap_traits<std::pair<unsigned_short,unsigned_short>,Ordnance_*,std::less<std::pair<unsigned_short,unsigned_short>_>,std::allocator<std::pair<std::pair<unsigned_short,unsigned_short>_const_,Ordnance_*>_>,0>_>::find
 * Namespace: std::_Tree<std::_Tmap_traits<std::pair<unsigned_short,unsigned_short>,Ordnance_*,std::less<std::pair<unsigned_short,unsigned_short>_>,std::allocator<std::pair<std::pair<unsigned_short,unsigned_short>_const_,Ordnance_*>_>,0>_>
 * Signature: iterator find(_Tree<std::_Tmap_traits<std::pair<unsigned_short,unsigned_short>,Ordnance_*,std::less<std::pair<unsigned_short,unsigned_short>_>,std::allocator<std::pair<std::pair<unsigned_short,unsigned_short>_const_,Ordnance_*>_>,0>_> * this, pair<unsigned_short,unsigned_short> * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

iterator __thiscall
std::
_Tree<std::_Tmap_traits<std::pair<unsigned_short,unsigned_short>,Ordnance_*,std::less<std::pair<unsigned_short,unsigned_short>_>,std::allocator<std::pair<std::pair<unsigned_short,unsigned_short>_const_,Ordnance_*>_>,0>_>
::find(_Tree<std::_Tmap_traits<std::pair<unsigned_short,unsigned_short>,Ordnance_*,std::less<std::pair<unsigned_short,unsigned_short>_>,std::allocator<std::pair<std::pair<unsigned_short,unsigned_short>_const_,Ordnance_*>_>,0>_>
       *this,pair<unsigned_short,unsigned_short> *param_1)

{
  pair<unsigned_short,unsigned_short> pVar1;
  pair<unsigned_short,unsigned_short> pVar2;
  bool bVar3;
  const_iterator *pcVar4;
  iterator iVar5;
  pair<unsigned_short,unsigned_short> *in_stack_00000008;
  const_iterator local_14;
  const_iterator local_c;
  
  lower_bound(this,(pair<unsigned_short,unsigned_short> *)&local_c);
  const_iterator::const_iterator(&local_14,this->_Myhead,this);
  bVar3 = const_iterator::operator==(&local_c,&local_14);
  if (!bVar3) {
    bVar3 = operator<<unsigned_short,unsigned_short>
                      (in_stack_00000008,&((local_c._Ptr)->_Myval).first);
    if (!bVar3) {
      pcVar4 = &local_c;
      goto LAB_00534636;
    }
  }
  const_iterator::const_iterator(&local_14,this->_Myhead,this);
  pcVar4 = &local_14;
LAB_00534636:
  pVar1 = (pair<unsigned_short,unsigned_short>)pcVar4->_padding_;
  pVar2 = (pair<unsigned_short,unsigned_short>)pcVar4->_Ptr;
  *param_1 = pVar1;
  param_1[1] = pVar2;
  iVar5._4_2_ = pVar1.first;
  iVar5._6_2_ = pVar1.second;
  iVar5._0_4_ = param_1;
  return iVar5;
}
