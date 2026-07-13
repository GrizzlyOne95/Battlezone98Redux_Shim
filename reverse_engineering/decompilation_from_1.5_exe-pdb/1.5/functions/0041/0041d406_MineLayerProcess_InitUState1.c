/*
 * Entry: 0041d406
 * Name: MineLayerProcess::InitUState1
 * Namespace: MineLayerProcess
 * Signature: void InitUState1(MineLayerProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall MineLayerProcess::InitUState1(MineLayerProcess *this)

{
  LayMinesTask *pLVar1;
  
  pLVar1 = operator_new(0x17c);
  if (pLVar1 == (LayMinesTask *)0x0) {
    pLVar1 = (LayMinesTask *)0x0;
  }
  else {
    pLVar1 = LayMinesTask::LayMinesTask(pLVar1,*(Craft **)&this->field_0x2c);
  }
  *(LayMinesTask **)&this->field_0x30 = pLVar1;
  return;
}
