/*
 * Entry: 00402a1a
 * Name: std::list<AiProcess_*,std::allocator<AiProcess_*>_>::remove
 * Namespace: std::list<AiProcess_*,std::allocator<AiProcess_*>_>
 * Signature: void remove(list<AiProcess_*,std::allocator<AiProcess_*>_> * this, AiProcess * * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::list<AiProcess_*,std::allocator<AiProcess_*>_>::remove
          (list<AiProcess_*,std::allocator<AiProcess_*>_> *this,AiProcess **param_1)

{
  AiProcess *pAVar1;
  _Const_iterator<1> _Var2;
  bool bVar3;
  AiProcess **ppAVar4;
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
