/*
 * Entry: 00519b28
 * Name: FindSendPoints::~FindSendPoints
 * Namespace: FindSendPoints
 * Signature: void ~FindSendPoints(FindSendPoints * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall FindSendPoints::~FindSendPoints(FindSendPoints *this)

{
  long *plVar1;
  
  plVar1 = sendPoints;
  this->_padding_ = (int)&_vftable_;
  if (plVar1 != (long *)0x0) {
    operator_delete__(plVar1);
  }
  sendPoints = (long *)0x0;
  while (((int)gridPoints._Mylast - (int)gridPoints._Myfirst & 0xfffffff8U) != 0) {
    std::vector<GridPoint,std::allocator<GridPoint>_>::pop_back(&gridPoints);
  }
  AiProcess::~AiProcess((AiProcess *)this);
  return;
}
