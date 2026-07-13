/*
 * Entry: 0041d3c9
 * Name: MineLayerEnemy::~MineLayerEnemy
 * Namespace: MineLayerEnemy
 * Signature: void ~MineLayerEnemy(MineLayerEnemy * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall MineLayerEnemy::~MineLayerEnemy(MineLayerEnemy *this)

{
  *(undefined ***)this = &MineLayerProcess::_vftable_;
  UnitProcess::CleanState((UnitProcess *)this);
  *(undefined4 *)&this->field_0x18 = 0;
  UnitProcess::~UnitProcess((UnitProcess *)this);
  return;
}
