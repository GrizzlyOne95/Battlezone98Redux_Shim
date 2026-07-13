/*
 * Entry: 0041d3b2
 * Name: MineLayerFriend::~MineLayerFriend
 * Namespace: MineLayerFriend
 * Signature: void ~MineLayerFriend(MineLayerFriend * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall MineLayerFriend::~MineLayerFriend(MineLayerFriend *this)

{
  *(undefined ***)this = &MineLayerProcess::_vftable_;
  UnitProcess::CleanState((UnitProcess *)this);
  *(undefined4 *)&this->field_0x18 = 0;
  UnitProcess::~UnitProcess((UnitProcess *)this);
  return;
}
