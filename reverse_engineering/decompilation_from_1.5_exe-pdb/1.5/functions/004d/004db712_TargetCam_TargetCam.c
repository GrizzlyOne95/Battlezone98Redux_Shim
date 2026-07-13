/*
 * Entry: 004db712
 * Name: TargetCam::TargetCam
 * Namespace: TargetCam
 * Signature: TargetCam * TargetCam(TargetCam * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

TargetCam * __thiscall TargetCam::TargetCam(TargetCam *this)

{
  DisplayInterface::DisplayInterface((DisplayInterface *)this);
  this->_padding_ = (int)&_vftable_;
  DisplayInterface::AddView((DisplayInterface *)this,0,0);
  DisplayInterface::AddView((DisplayInterface *)this,2,0);
  DisplayInterface::AddView((DisplayInterface *)this,1,0);
  DisplayInterface::AddView((DisplayInterface *)this,7,0);
  return this;
}
