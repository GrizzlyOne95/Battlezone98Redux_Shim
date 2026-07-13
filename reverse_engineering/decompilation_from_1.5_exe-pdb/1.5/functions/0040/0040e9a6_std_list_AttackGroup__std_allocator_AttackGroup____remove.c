/*
 * Entry: 0040e9a6
 * Name: std::list<AttackGroup_*,std::allocator<AttackGroup_*>_>::remove
 * Namespace: std::list<AttackGroup_*,std::allocator<AttackGroup_*>_>
 * Signature: void remove(list<AttackGroup_*,std::allocator<AttackGroup_*>_> * this, AttackGroup * * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::list<AttackGroup_*,std::allocator<AttackGroup_*>_>::remove
          (list<AttackGroup_*,std::allocator<AttackGroup_*>_> *this,AttackGroup **param_1)

{
  AttackGroup *pAVar1;
  _Const_iterator<1> _Var2;
  bool bVar3;
  AttackGroup **ppAVar4;
  _Iterator<1> _Var5;
  undefined1 local_1c [8];
  _Const_iterator<1> local_14;
  _Const_iterator<1> local_c;
  
  pAVar1 = *param_1;
  _Const_iterator<1>::_Const_iterator<1>(&local_14,this->_Myhead,this);
  _Const_iterator<1>::_Const_iterator<1>(&local_c,this->_Myhead->_Next,this);
  while( true ) {
    bVar3 = _Const_iterator<1>::operator==(&local_c,&local_14);
    if (bVar3) break;
    ppAVar4 = _Const_iterator<1>::operator*(&local_c);
    if (*ppAVar4 == pAVar1) {
      _Var2._Ptr = (_Node *)local_c._padding_;
      _Var2._padding_ = (int)local_1c;
      _Var5 = erase(this,_Var2);
      local_c._padding_ = *_Var5._0_4_;
      local_c._Ptr = (_Node *)_Var5._0_4_[1];
    }
    else {
      _Const_iterator<1>::operator++(&local_c);
    }
  }
  return;
}
