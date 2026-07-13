/*
 * Entry: 0040d0f7
 * Name: SLFFriend::~SLFFriend
 * Namespace: SLFFriend
 * Signature: void ~SLFFriend(SLFFriend * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall SLFFriend::~SLFFriend(SLFFriend *this)

{
  *(undefined ***)this = &ArmoryProcess::_vftable_;
  ArmoryProcess::CleanState((ArmoryProcess *)this);
  AiProcess::~AiProcess((AiProcess *)this);
  return;
}
