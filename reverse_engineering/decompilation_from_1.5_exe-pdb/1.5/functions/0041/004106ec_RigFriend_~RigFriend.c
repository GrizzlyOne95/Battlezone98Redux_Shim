/*
 * Entry: 004106ec
 * Name: RigFriend::~RigFriend
 * Namespace: RigFriend
 * Signature: void ~RigFriend(RigFriend * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall RigFriend::~RigFriend(RigFriend *this)

{
  *(undefined ***)this = &RigProcess::_vftable_;
  UnitProcess::CleanState((UnitProcess *)this);
  *(undefined4 *)&this->field_0x18 = 0;
  UnitProcess::~UnitProcess((UnitProcess *)this);
  return;
}
