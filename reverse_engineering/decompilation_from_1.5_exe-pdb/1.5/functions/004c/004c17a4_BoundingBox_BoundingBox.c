/*
 * Entry: 004c17a4
 * Name: BoundingBox::BoundingBox
 * Namespace: BoundingBox
 * Signature: BoundingBox * BoundingBox(BoundingBox * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

BoundingBox * __thiscall BoundingBox::BoundingBox(BoundingBox *this)

{
  DisplayInterface::DisplayInterface((DisplayInterface *)this);
  this->_padding_ = (int)&_vftable_;
  this->showCollision = false;
  return this;
}
