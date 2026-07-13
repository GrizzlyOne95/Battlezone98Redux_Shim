/*
 * Entry: 004aa970
 * Name: Producer::PackTempState
 * Namespace: Producer
 * Signature: void PackTempState(Producer * this, void * param_1, uint * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Producer::PackTempState(Producer *this,void *param_1,uint *param_2)

{
  int iVar1;
  
  *param_2 = *param_2 + 1;
  iVar1 = this->_padding_;
  if (iVar1 == 0) {
    *(undefined1 *)param_1 = 0;
  }
  else if (iVar1 == 1) {
    *(undefined1 *)param_1 = 1;
  }
  else if (iVar1 == 2) {
    *(undefined1 *)param_1 = 2;
  }
  else if (iVar1 == 3) {
    *(undefined1 *)param_1 = 3;
  }
  HoverCraft::PackTempState((HoverCraft *)this,(void *)((int)param_1 + 1),param_2);
  return;
}
