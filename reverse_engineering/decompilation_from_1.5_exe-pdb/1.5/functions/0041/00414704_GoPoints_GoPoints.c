/*
 * Entry: 00414704
 * Name: GoPoints::GoPoints
 * Namespace: GoPoints
 * Signature: GoPoints * GoPoints(GoPoints * this, Craft * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GoPoints * __thiscall GoPoints::GoPoints(GoPoints *this,Craft *param_1)

{
  GotoTask::GotoTask((GotoTask *)this,param_1,(AiPath *)0x0,true);
  this->lastPlan = (AiPath *)0x0;
  this->_padding_ = 6;
  this->_padding_ = 6;
  this->_padding_ = (int)&_vftable_;
  *(undefined1 *)((int)&this->_padding_ + 2) = 1;
  return this;
}
