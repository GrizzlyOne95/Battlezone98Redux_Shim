/*
 * Entry: 004c8744
 * Name: std::list<DisplayInterface_*,std::allocator<DisplayInterface_*>_>::remove
 * Namespace: std::list<DisplayInterface_*,std::allocator<DisplayInterface_*>_>
 * Signature: void remove(list<DisplayInterface_*,std::allocator<DisplayInterface_*>_> * this, DisplayInterface * * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::list<DisplayInterface_*,std::allocator<DisplayInterface_*>_>::remove
          (list<DisplayInterface_*,std::allocator<DisplayInterface_*>_> *this,
          DisplayInterface **param_1)

{
  DisplayInterface *pDVar1;
  _Const_iterator<1> _Var2;
  bool bVar3;
  DisplayInterface **ppDVar4;
  _Iterator<1> _Var5;
  undefined1 local_1c [8];
  _Const_iterator<1> local_14;
  _Const_iterator<1> local_c;
  
  pDVar1 = *param_1;
  _Const_iterator<1>::_Const_iterator<1>(&local_14,this->_Myhead,this);
  _Const_iterator<1>::_Const_iterator<1>(&local_c,this->_Myhead->_Next,this);
  while( true ) {
    bVar3 = _Const_iterator<1>::operator==(&local_c,&local_14);
    if (bVar3) break;
    ppDVar4 = _Const_iterator<1>::operator*(&local_c);
    if (*ppDVar4 == pDVar1) {
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
