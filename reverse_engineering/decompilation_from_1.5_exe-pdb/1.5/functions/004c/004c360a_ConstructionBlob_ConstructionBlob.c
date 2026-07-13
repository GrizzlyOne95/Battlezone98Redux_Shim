/*
 * Entry: 004c360a
 * Name: ConstructionBlob::ConstructionBlob
 * Namespace: ConstructionBlob
 * Signature: ConstructionBlob * ConstructionBlob(ConstructionBlob * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

ConstructionBlob * __thiscall ConstructionBlob::ConstructionBlob(ConstructionBlob *this)

{
  GameFeature::GameFeature((GameFeature *)this);
  *(byte *)&this->_padding_ = (byte)this->_padding_ | 1;
  this->_padding_ = (int)&_vftable_;
  return this;
}
