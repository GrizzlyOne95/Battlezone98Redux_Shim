/*
 * Entry: 0040cd38
 * Name: UnitTask::GetHim
 * Namespace: UnitTask
 * Signature: GameObject * GetHim(UnitTask * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GameObject * __thiscall UnitTask::GetHim(UnitTask *this)

{
  GameObject *pGVar1;
  
  pGVar1 = GameObjectHandle::GetObj(this->himHandle);
  return pGVar1;
}
