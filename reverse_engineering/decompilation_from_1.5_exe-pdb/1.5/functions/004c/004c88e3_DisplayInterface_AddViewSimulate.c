/*
 * Entry: 004c88e3
 * Name: DisplayInterface::AddViewSimulate
 * Namespace: DisplayInterface
 * Signature: void AddViewSimulate(DisplayInterface * this, int param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall DisplayInterface::AddViewSimulate(DisplayInterface *this,int param_1,int param_2)

{
  list<DisplayViewInfo_*,std::allocator<DisplayViewInfo_*>_> *this_00;
  _Const_iterator<1> _Var1;
  int iVar2;
  bool bVar3;
  DisplayViewInfo **ppDVar4;
  _Const_iterator<1> local_14;
  _Const_iterator<1> local_c;
  
  this_00 = simulateList[param_1];
  param_1 = (int)operator_new(8);
  iVar2 = param_2;
  *(int *)param_1 = param_2;
  *(DisplayInterface **)(param_1 + 4) = this;
  std::list<DisplayViewInfo_*,std::allocator<DisplayViewInfo_*>_>::_Const_iterator<1>::
  _Const_iterator<1>(&local_14,this_00->_Myhead->_Next,this_00);
  local_c._padding_ = local_14._padding_;
  local_c._Ptr = local_14._Ptr;
  do {
    std::list<DisplayViewInfo_*,std::allocator<DisplayViewInfo_*>_>::_Const_iterator<1>::
    _Const_iterator<1>(&local_14,this_00->_Myhead,this_00);
    bVar3 = std::list<DisplayViewInfo_*,std::allocator<DisplayViewInfo_*>_>::_Const_iterator<1>::
            operator==(&local_c,&local_14);
    if (bVar3) {
LAB_004c8978:
      std::list<DisplayViewInfo_*,std::allocator<DisplayViewInfo_*>_>::_Const_iterator<1>::
      _Const_iterator<1>(&local_14,this_00->_Myhead,this_00);
      bVar3 = std::list<DisplayViewInfo_*,std::allocator<DisplayViewInfo_*>_>::_Const_iterator<1>::
              operator==(&local_c,&local_14);
      if (bVar3) {
        std::list<DisplayViewInfo_*,std::allocator<DisplayViewInfo_*>_>::push_back
                  (this_00,(DisplayViewInfo **)&param_1);
      }
      return;
    }
    if ((-0x8001 < iVar2) &&
       (ppDVar4 = std::list<DisplayViewInfo_*,std::allocator<DisplayViewInfo_*>_>::
                  _Const_iterator<1>::operator*(&local_c), iVar2 < (*ppDVar4)->priority)) {
      _Var1._Ptr = (_Node *)local_c._padding_;
      _Var1._padding_ = (int)&local_14;
      std::list<DisplayViewInfo_*,std::allocator<DisplayViewInfo_*>_>::insert
                (this_00,_Var1,(DisplayViewInfo **)local_c._Ptr);
      goto LAB_004c8978;
    }
    std::list<DisplayViewInfo_*,std::allocator<DisplayViewInfo_*>_>::_Const_iterator<1>::operator++
              (&local_c);
  } while( true );
}
