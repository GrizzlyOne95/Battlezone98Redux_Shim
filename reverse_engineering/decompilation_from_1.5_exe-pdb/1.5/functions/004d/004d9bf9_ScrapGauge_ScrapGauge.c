/*
 * Entry: 004d9bf9
 * Name: ScrapGauge::ScrapGauge
 * Namespace: ScrapGauge
 * Signature: ScrapGauge * ScrapGauge(ScrapGauge * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

ScrapGauge * __thiscall ScrapGauge::ScrapGauge(ScrapGauge *this)

{
  DisplayInterface::DisplayInterface((DisplayInterface *)this);
  this->_padding_ = (int)&_vftable_;
  DisplayInterface::AddView((DisplayInterface *)this,0,2);
  DisplayInterface::AddView((DisplayInterface *)this,1,2);
  DisplayInterface::AddView((DisplayInterface *)this,2,2);
  DisplayInterface::AddView((DisplayInterface *)this,3,2);
  DisplayInterface::AddView((DisplayInterface *)this,7,2);
  return this;
}
