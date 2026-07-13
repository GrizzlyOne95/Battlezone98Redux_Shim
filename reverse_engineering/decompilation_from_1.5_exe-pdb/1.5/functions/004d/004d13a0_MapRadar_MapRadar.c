/*
 * Entry: 004d13a0
 * Name: MapRadar::MapRadar
 * Namespace: MapRadar
 * Signature: MapRadar * MapRadar(MapRadar * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

MapRadar * __thiscall MapRadar::MapRadar(MapRadar *this)

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
