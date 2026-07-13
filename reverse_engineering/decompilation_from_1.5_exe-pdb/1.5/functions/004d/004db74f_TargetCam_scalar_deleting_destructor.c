/*
 * Entry: 004db74f
 * Name: TargetCam::`scalar_deleting_destructor'
 * Namespace: TargetCam
 * Signature: void * `scalar_deleting_destructor'(TargetCam * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall TargetCam::_scalar_deleting_destructor_(TargetCam *this,uint param_1)

{
  DisplayInterface::~DisplayInterface((DisplayInterface *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
