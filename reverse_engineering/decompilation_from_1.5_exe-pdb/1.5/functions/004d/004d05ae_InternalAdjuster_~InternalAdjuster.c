/*
 * Entry: 004d05ae
 * Name: InternalAdjuster::~InternalAdjuster
 * Namespace: InternalAdjuster
 * Signature: void ~InternalAdjuster(InternalAdjuster * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall InternalAdjuster::~InternalAdjuster(InternalAdjuster *this)

{
  std::list<AdjustItem_*,std::allocator<AdjustItem_*>_>::_Tidy(&this->adjustList);
  operator_delete((void *)(this->adjustList)._padding_);
  DisplayInterface::~DisplayInterface((DisplayInterface *)&this->_padding_);
  return;
}
