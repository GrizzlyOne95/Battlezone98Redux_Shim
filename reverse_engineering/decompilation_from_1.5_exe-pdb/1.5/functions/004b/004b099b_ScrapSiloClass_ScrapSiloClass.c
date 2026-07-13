/*
 * Entry: 004b099b
 * Name: ScrapSiloClass::ScrapSiloClass
 * Namespace: ScrapSiloClass
 * Signature: ScrapSiloClass * ScrapSiloClass(ScrapSiloClass * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

ScrapSiloClass * __thiscall ScrapSiloClass::ScrapSiloClass(ScrapSiloClass *this)

{
  BuildingClass::BuildingClass((BuildingClass *)this);
  this->_padding_ = (int)&_vftable_;
  this->_padding_ = 0x53494c4f;
  this->_padding_ = (int)"scrapsilo";
  this->_padding_ = 0x46;
  this->_padding_ = 0x4a;
  return this;
}
