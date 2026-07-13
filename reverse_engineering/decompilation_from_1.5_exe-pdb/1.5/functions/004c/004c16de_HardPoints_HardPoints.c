/*
 * Entry: 004c16de
 * Name: HardPoints::HardPoints
 * Namespace: HardPoints
 * Signature: HardPoints * HardPoints(HardPoints * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

HardPoints * __thiscall HardPoints::HardPoints(HardPoints *this)

{
  DisplayInterface::DisplayInterface((DisplayInterface *)this);
  this->_padding_ = (int)&_vftable_;
  this->showHardpoints = false;
  return this;
}
