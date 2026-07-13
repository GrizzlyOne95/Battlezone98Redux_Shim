/*
 * Entry: 0041cfbb
 * Name: MineLayerProcess::~MineLayerProcess
 * Namespace: MineLayerProcess
 * Signature: void ~MineLayerProcess(MineLayerProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall MineLayerProcess::~MineLayerProcess(MineLayerProcess *this)

{
  *(undefined ***)this = &_vftable_;
  UnitProcess::CleanState((UnitProcess *)this);
  *(undefined4 *)&this->field_0x18 = 0;
  UnitProcess::~UnitProcess((UnitProcess *)this);
  return;
}
