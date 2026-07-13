/*
 * Entry: 004b30e1
 * Name: Tug::PackTempState
 * Namespace: Tug
 * Signature: void PackTempState(Tug * this, void * param_1, uint * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Tug::PackTempState(Tug *this,void *param_1,uint *param_2)

{
  int iVar1;
  ulong uVar2;
  
  *param_2 = *param_2 + 8;
  iVar1 = this->_padding_;
  if (iVar1 == 0) {
    *(undefined1 *)((int)param_1 + 4) = 0;
  }
  else if (iVar1 == 1) {
    *(undefined1 *)((int)param_1 + 4) = 1;
  }
  else if (iVar1 == 2) {
    *(undefined1 *)((int)param_1 + 4) = 2;
  }
  else if (iVar1 == 3) {
    *(undefined1 *)((int)param_1 + 4) = 3;
  }
  if (this->_padding_ == 0) {
    *(undefined4 *)param_1 = 0;
  }
  else {
    uVar2 = DistributedObject::GetID((DistributedObject *)(this->_padding_ + 0x20));
    *(ulong *)param_1 = uVar2;
  }
  HoverCraft::PackTempState((HoverCraft *)this,(void *)((int)param_1 + 8),param_2);
  return;
}
