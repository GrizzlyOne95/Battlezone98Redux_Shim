/*
 * Entry: 0041036a
 * Name: UnBuild::UnBuild
 * Namespace: UnBuild
 * Signature: UnBuild * UnBuild(UnBuild * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

UnBuild * __thiscall UnBuild::UnBuild(UnBuild *this)

{
  GotoTask::GotoTask((GotoTask *)this);
  this->unbuildStage = 0;
  this->_padding_ = (int)&_vftable_;
  return this;
}
