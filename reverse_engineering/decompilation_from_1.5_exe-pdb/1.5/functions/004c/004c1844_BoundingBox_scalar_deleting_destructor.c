/*
 * Entry: 004c1844
 * Name: BoundingBox::`scalar_deleting_destructor'
 * Namespace: BoundingBox
 * Signature: void * `scalar_deleting_destructor'(BoundingBox * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall BoundingBox::_scalar_deleting_destructor_(BoundingBox *this,uint param_1)

{
  DisplayInterface::~DisplayInterface((DisplayInterface *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
