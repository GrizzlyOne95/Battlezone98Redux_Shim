/*
 * Entry: 00459ac7
 * Name: RecycleTask::PostInit
 * Namespace: RecycleTask
 * Signature: void PostInit(RecycleTask * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall RecycleTask::PostInit(RecycleTask *this)

{
  int iVar1;
  
  iVar1 = (**(code **)this->me->_padding_)();
  this->deployMsg = (char *)(iVar1 + 0x3d4);
  this->foundMsg = (char *)(iVar1 + 0x3e4);
  this->notFoundMsg = (char *)(iVar1 + 0x3f4);
  this->noDropMsg = (char *)(iVar1 + 0x404);
  return;
}
