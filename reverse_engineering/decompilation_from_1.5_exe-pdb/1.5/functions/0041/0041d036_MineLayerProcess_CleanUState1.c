/*
 * Entry: 0041d036
 * Name: MineLayerProcess::CleanUState1
 * Namespace: MineLayerProcess
 * Signature: void CleanUState1(MineLayerProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall MineLayerProcess::CleanUState1(MineLayerProcess *this)

{
  if (*(undefined4 **)&this->field_0x30 != (undefined4 *)0x0) {
    (**(code **)**(undefined4 **)&this->field_0x30)(1);
  }
  *(undefined4 *)&this->field_0x30 = 0;
  return;
}
