/*
 * Entry: 004d041c
 * Name: InternalAdjuster::Advance
 * Namespace: InternalAdjuster
 * Signature: void Advance(InternalAdjuster * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall InternalAdjuster::Advance(InternalAdjuster *this)

{
  list<AdjustItem_*,std::allocator<AdjustItem_*>_> *plVar1;
  bool bVar2;
  char cVar3;
  AdjustItem **ppAVar4;
  _Iterator<1> *this_00;
  _Const_iterator<1> local_c;
  
  plVar1 = &this->adjustList;
  local_c._padding_ = (int)this;
  local_c._Ptr = (_Node *)this;
  std::list<AdjustItem_*,std::allocator<AdjustItem_*>_>::_Const_iterator<1>::_Const_iterator<1>
            (&local_c,(this->adjustList)._Myhead,plVar1);
  this_00 = &this->curAdjItem;
  bVar2 = std::list<AdjustItem_*,std::allocator<AdjustItem_*>_>::_Const_iterator<1>::operator==
                    ((_Const_iterator<1> *)this_00,&local_c);
  if (bVar2) {
    std::list<AdjustItem_*,std::allocator<AdjustItem_*>_>::_Const_iterator<1>::_Const_iterator<1>
              (&local_c,((this->adjustList)._Myhead)->_Next,plVar1);
    *(int *)&this_00->field_0x0 = local_c._padding_;
    *(_Node **)&(this->curAdjItem).field_0x4 = local_c._Ptr;
  }
  else {
    ppAVar4 = std::list<AdjustItem_*,std::allocator<AdjustItem_*>_>::_Const_iterator<1>::operator*
                        ((_Const_iterator<1> *)this_00);
    cVar3 = (**(code **)**ppAVar4)();
    if (cVar3 != '\0') {
      return;
    }
    std::list<AdjustItem_*,std::allocator<AdjustItem_*>_>::_Const_iterator<1>::operator++
              ((_Const_iterator<1> *)this_00);
    std::list<AdjustItem_*,std::allocator<AdjustItem_*>_>::_Const_iterator<1>::_Const_iterator<1>
              (&local_c,(this->adjustList)._Myhead,plVar1);
    bVar2 = std::list<AdjustItem_*,std::allocator<AdjustItem_*>_>::_Const_iterator<1>::operator==
                      ((_Const_iterator<1> *)this_00,&local_c);
    if (bVar2) {
      return;
    }
  }
  ppAVar4 = std::list<AdjustItem_*,std::allocator<AdjustItem_*>_>::_Const_iterator<1>::operator*
                      ((_Const_iterator<1> *)this_00);
  (**(code **)**ppAVar4)();
  return;
}
