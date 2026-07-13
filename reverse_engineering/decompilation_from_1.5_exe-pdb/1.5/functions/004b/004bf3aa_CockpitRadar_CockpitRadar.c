/*
 * Entry: 004bf3aa
 * Name: CockpitRadar::CockpitRadar
 * Namespace: CockpitRadar
 * Signature: CockpitRadar * CockpitRadar(CockpitRadar * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

CockpitRadar * __thiscall CockpitRadar::CockpitRadar(CockpitRadar *this)

{
  DisplayInterface::DisplayInterface((DisplayInterface *)this);
  this->_padding_ = (int)&_vftable_;
  DisplayInterface::AddView((DisplayInterface *)this,0,2);
  DisplayInterface::AddView((DisplayInterface *)this,2,2);
  DisplayInterface::AddView((DisplayInterface *)this,1,2);
  DisplayInterface::AddView((DisplayInterface *)this,7,2);
  DisplayInterface::AddView((DisplayInterface *)this,3,2);
  return this;
}
