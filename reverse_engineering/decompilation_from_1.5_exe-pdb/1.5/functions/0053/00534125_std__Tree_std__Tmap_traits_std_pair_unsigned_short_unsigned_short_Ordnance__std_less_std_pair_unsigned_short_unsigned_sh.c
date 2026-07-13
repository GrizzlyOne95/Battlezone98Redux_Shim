/*
 * Entry: 00534125
 * Name: std::_Tree<std::_Tmap_traits<std::pair<unsigned_short,unsigned_short>,Ordnance_*,std::less<std::pair<unsigned_short,unsigned_short>_>,std::allocator<std::pair<std::pair<unsigned_short,unsigned_short>_const_,Ordnance_*>_>,0>_>::erase
 * Namespace: std::_Tree<std::_Tmap_traits<std::pair<unsigned_short,unsigned_short>,Ordnance_*,std::less<std::pair<unsigned_short,unsigned_short>_>,std::allocator<std::pair<std::pair<unsigned_short,unsigned_short>_const_,Ordnance_*>_>,0>_>
 * Signature: iterator erase(_Tree<std::_Tmap_traits<std::pair<unsigned_short,unsigned_short>,Ordnance_*,std::less<std::pair<unsigned_short,unsigned_short>_>,std::allocator<std::pair<std::pair<unsigned_short,unsigned_short>_const_,Ordnance_*>_>,0>_> * this, const_iterator param_1, const_iterator param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

iterator __thiscall
std::
_Tree<std::_Tmap_traits<std::pair<unsigned_short,unsigned_short>,Ordnance_*,std::less<std::pair<unsigned_short,unsigned_short>_>,std::allocator<std::pair<std::pair<unsigned_short,unsigned_short>_const_,Ordnance_*>_>,0>_>
::erase(_Tree<std::_Tmap_traits<std::pair<unsigned_short,unsigned_short>,Ordnance_*,std::less<std::pair<unsigned_short,unsigned_short>_>,std::allocator<std::pair<std::pair<unsigned_short,unsigned_short>_const_,Ordnance_*>_>,0>_>
        *this,const_iterator param_1,const_iterator param_2)

{
  const_iterator cVar1;
  const_iterator cVar2;
  _Node *p_Var3;
  bool bVar4;
  undefined4 uVar5;
  iterator iVar6;
  iterator iVar7;
  const_iterator local_c;
  
  local_c._padding_ = (int)this;
  local_c._Ptr = (_Node *)this;
  const_iterator::const_iterator(&local_c,this->_Myhead->_Left,this);
  bVar4 = const_iterator::operator==((const_iterator *)&param_1._Ptr,&local_c);
  if (bVar4) {
    const_iterator::const_iterator(&local_c,this->_Myhead,this);
    bVar4 = const_iterator::operator==((const_iterator *)&param_2._Ptr,&local_c);
    if (bVar4) {
      clear(this);
      iVar6 = begin(this);
      uVar5 = iVar6._4_4_;
      goto LAB_005341c9;
    }
  }
  bVar4 = const_iterator::operator==
                    ((const_iterator *)&param_1._Ptr,(const_iterator *)&param_2._Ptr);
  p_Var3 = param_1._Ptr;
  while (param_1._Ptr = p_Var3, !bVar4) {
    const_iterator::_Inc((const_iterator *)&param_1._Ptr);
    cVar1._Ptr = p_Var3;
    cVar1._padding_ = (int)&local_c;
    erase(this,cVar1);
    bVar4 = const_iterator::operator==
                      ((const_iterator *)&param_1._Ptr,(const_iterator *)&param_2._Ptr);
    p_Var3 = param_1._Ptr;
  }
  cVar2._Ptr = p_Var3;
  cVar2._padding_ = param_1._padding_;
  iVar7 = _Make_iter(this,cVar2);
  uVar5 = iVar7._4_4_;
LAB_005341c9:
  iVar7._4_4_ = uVar5;
  iVar7._0_4_ = param_1._padding_;
  return iVar7;
}
