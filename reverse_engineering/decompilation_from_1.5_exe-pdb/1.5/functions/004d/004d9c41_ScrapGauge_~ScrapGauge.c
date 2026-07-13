/*
 * Entry: 004d9c41
 * Name: ScrapGauge::~ScrapGauge
 * Namespace: ScrapGauge
 * Signature: void ~ScrapGauge(ScrapGauge * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall ScrapGauge::~ScrapGauge(ScrapGauge *this)

{
  this->_padding_ = (int)&_vftable_;
  DisplayInterface::~DisplayInterface((DisplayInterface *)this);
  return;
}
