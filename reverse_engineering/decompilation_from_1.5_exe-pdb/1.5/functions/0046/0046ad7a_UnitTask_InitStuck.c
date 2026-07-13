/*
 * Entry: 0046ad7a
 * Name: UnitTask::InitStuck
 * Namespace: UnitTask
 * Signature: void InitStuck(UnitTask * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall UnitTask::InitStuck(UnitTask *this)

{
  ulong *puVar1;
  
  this->stuckState = 0;
  puVar1 = &this->me->vhcl->flags;
  *puVar1 = *puVar1 | 0x20000;
  return;
}
