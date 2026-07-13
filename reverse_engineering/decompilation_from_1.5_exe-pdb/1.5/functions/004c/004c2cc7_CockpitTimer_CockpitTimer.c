/*
 * Entry: 004c2cc7
 * Name: CockpitTimer::CockpitTimer
 * Namespace: CockpitTimer
 * Signature: CockpitTimer * CockpitTimer(CockpitTimer * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

CockpitTimer * __thiscall CockpitTimer::CockpitTimer(CockpitTimer *this)

{
  DisplayInterface::DisplayInterface((DisplayInterface *)this);
  this->_padding_ = (int)&_vftable_;
  DisplayInterface::AddViewSimulate((DisplayInterface *)this,0,0);
  DisplayInterface::AddViewSimulate((DisplayInterface *)this,1,0);
  DisplayInterface::AddViewSimulate((DisplayInterface *)this,2,0);
  DisplayInterface::AddViewSimulate((DisplayInterface *)this,3,0);
  DisplayInterface::AddViewSimulate((DisplayInterface *)this,4,0);
  DisplayInterface::AddViewSimulate((DisplayInterface *)this,5,0);
  DisplayInterface::AddViewSimulate((DisplayInterface *)this,6,0);
  DisplayInterface::AddViewSimulate((DisplayInterface *)this,7,0);
  DisplayInterface::AddViewSimulate((DisplayInterface *)this,8,0);
  return this;
}
