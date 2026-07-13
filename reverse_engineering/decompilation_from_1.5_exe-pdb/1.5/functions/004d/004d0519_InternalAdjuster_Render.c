/*
 * Entry: 004d0519
 * Name: InternalAdjuster::Render
 * Namespace: InternalAdjuster
 * Signature: void Render(InternalAdjuster * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall InternalAdjuster::Render(InternalAdjuster *this)

{
  bool bVar1;
  AdjustItem **ppAVar2;
  uint *this_00;
  _Const_iterator<1> local_c;
  
  local_c._padding_ = (int)this;
  local_c._Ptr = (_Node *)this;
  std::list<AdjustItem_*,std::allocator<AdjustItem_*>_>::_Const_iterator<1>::_Const_iterator<1>
            (&local_c,(_Node *)(this->adjustList)._padding_,
             (list<AdjustItem_*,std::allocator<AdjustItem_*>_> *)&this->_padding_);
  this_00 = &(this->adjustList)._Mysize;
  bVar1 = std::list<AdjustItem_*,std::allocator<AdjustItem_*>_>::_Const_iterator<1>::operator==
                    ((_Const_iterator<1> *)this_00,&local_c);
  if (!bVar1) {
    DisplayInterface::SetTextPos(100,0x28);
    ppAVar2 = std::list<AdjustItem_*,std::allocator<AdjustItem_*>_>::_Const_iterator<1>::operator*
                        ((_Const_iterator<1> *)this_00);
    (**(code **)((int)**ppAVar2 + 4))();
  }
  return;
}
