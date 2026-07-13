/*
 * Entry: 0053458c
 * Name: std::_Tree<std::_Tmap_traits<std::pair<unsigned_short,unsigned_short>,Ordnance_*,std::less<std::pair<unsigned_short,unsigned_short>_>,std::allocator<std::pair<std::pair<unsigned_short,unsigned_short>_const_,Ordnance_*>_>,0>_>::erase
 * Namespace: std::_Tree<std::_Tmap_traits<std::pair<unsigned_short,unsigned_short>,Ordnance_*,std::less<std::pair<unsigned_short,unsigned_short>_>,std::allocator<std::pair<std::pair<unsigned_short,unsigned_short>_const_,Ordnance_*>_>,0>_>
 * Signature: uint erase(_Tree<std::_Tmap_traits<std::pair<unsigned_short,unsigned_short>,Ordnance_*,std::less<std::pair<unsigned_short,unsigned_short>_>,std::allocator<std::pair<std::pair<unsigned_short,unsigned_short>_const_,Ordnance_*>_>,0>_> * this, pair<unsigned_short,unsigned_short> * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

uint __thiscall
std::
_Tree<std::_Tmap_traits<std::pair<unsigned_short,unsigned_short>,Ordnance_*,std::less<std::pair<unsigned_short,unsigned_short>_>,std::allocator<std::pair<std::pair<unsigned_short,unsigned_short>_const_,Ordnance_*>_>,0>_>
::erase(_Tree<std::_Tmap_traits<std::pair<unsigned_short,unsigned_short>,Ordnance_*,std::less<std::pair<unsigned_short,unsigned_short>_>,std::allocator<std::pair<std::pair<unsigned_short,unsigned_short>_const_,Ordnance_*>_>,0>_>
        *this,pair<unsigned_short,unsigned_short> *param_1)

{
  iterator iVar1;
  const_iterator cVar2;
  iterator iVar3;
  const_iterator cVar4;
  _Node *local_14;
  int local_10;
  _Node *local_c [2];
  
  _Eqrange(this,(pair<std::_Tree<std::_Tmap_traits<std::pair<unsigned_short,unsigned_short>,Ordnance_*,std::less<std::pair<unsigned_short,unsigned_short>_>,std::allocator<std::pair<std::pair<unsigned_short,unsigned_short>_const_,Ordnance_*>_>,0>_>::iterator,std::_Tree<std::_Tmap_traits<std::pair<unsigned_short,unsigned_short>,Ordnance_*,std::less<std::pair<unsigned_short,unsigned_short>_>,std::allocator<std::pair<std::pair<unsigned_short,unsigned_short>_const_,Ordnance_*>_>,0>_>::iterator>
                 *)&local_14,param_1);
  param_1 = (pair<unsigned_short,unsigned_short> *)0x0;
  iVar1._4_4_ = local_10;
  iVar1._0_4_ = local_14;
  iVar3._4_4_ = local_c[1];
  iVar3._0_4_ = local_c[0];
  _Distance<std::_Tree<std::_Tmap_traits<std::pair<unsigned_short,unsigned_short>,Ordnance_*,std::less<std::pair<unsigned_short,unsigned_short>_>,std::allocator<std::pair<std::pair<unsigned_short,unsigned_short>_const_,Ordnance_*>_>,0>_>::iterator,unsigned_int>
            (iVar1,iVar3,(uint *)&param_1);
  cVar2._Ptr = local_14;
  cVar2._padding_ = (int)local_c;
  cVar4._Ptr = local_c[0];
  cVar4._padding_ = local_10;
  erase(this,cVar2,cVar4);
  return (uint)param_1;
}
