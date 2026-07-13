/*
 * Entry: 0044bfa9
 * Name: MultDMMission::AddObject
 * Namespace: MultDMMission
 * Signature: void AddObject(MultDMMission * this, GameObject * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall MultDMMission::AddObject(MultDMMission *this,GameObject *param_1)

{
  int iVar1;
  
  iVar1 = (**(code **)(param_1->_padding_ + 4))();
  if (iVar1 != 0) {
    LuaMission::AddObject((LuaMission *)this,param_1);
  }
  return;
}
