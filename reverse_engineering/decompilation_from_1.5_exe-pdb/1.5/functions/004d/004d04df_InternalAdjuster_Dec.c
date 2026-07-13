/*
 * Entry: 004d04df
 * Name: InternalAdjuster::Dec
 * Namespace: InternalAdjuster
 * Signature: void Dec(InternalAdjuster * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall InternalAdjuster::Dec(InternalAdjuster *this)

{
  bool bVar1;
  AdjustItem **ppAVar2;
  _Const_iterator<1> local_c;
  
  local_c._padding_ = (int)this;
  local_c._Ptr = (_Node *)this;
  std::list<AdjustItem_*,std::allocator<AdjustItem_*>_>::_Const_iterator<1>::_Const_iterator<1>
            (&local_c,(this->adjustList)._Myhead,&this->adjustList);
  bVar1 = std::list<AdjustItem_*,std::allocator<AdjustItem_*>_>::_Const_iterator<1>::operator==
                    ((_Const_iterator<1> *)&this->curAdjItem,&local_c);
  if (!bVar1) {
    ppAVar2 = std::list<AdjustItem_*,std::allocator<AdjustItem_*>_>::_Const_iterator<1>::operator*
                        ((_Const_iterator<1> *)&this->curAdjItem);
    (**(code **)((int)**ppAVar2 + 0xc))();
  }
  return;
}
