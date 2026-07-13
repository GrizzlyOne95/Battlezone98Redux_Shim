/*
 * Entry: 00459c2f
 * Name: RecycleTask::PostLoad
 * Namespace: RecycleTask
 * Signature: bool PostLoad(RecycleTask * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall RecycleTask::PostLoad(RecycleTask *this)

{
  bool bVar1;
  int iVar2;
  
  iVar2 = ConvertHandle(this->scrapHandle);
  this->scrapHandle = iVar2;
  iVar2 = ConvertHandle(this->dropHandle);
  this->dropHandle = iVar2;
  bVar1 = SObject::PostLoad((SObject *)this);
  (**(code **)(this->_padding_ + 0x24))();
  return bVar1;
}
