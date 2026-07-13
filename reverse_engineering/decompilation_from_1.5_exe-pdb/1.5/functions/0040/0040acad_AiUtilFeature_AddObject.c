/*
 * Entry: 0040acad
 * Name: AiUtilFeature::AddObject
 * Namespace: AiUtilFeature
 * Signature: void AddObject(AiUtilFeature * this, GameObject * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall AiUtilFeature::AddObject(AiUtilFeature *this,GameObject *param_1)

{
  int iVar1;
  int iVar2;
  
  iVar1 = (**(code **)param_1->_padding_)();
  iVar2 = (**(code **)param_1->_padding_)();
  iVar1 = *(int *)(iVar1 + 0x28);
  iVar2 = *(int *)(iVar2 + 0x20);
  if (((((iVar1 == 2) || (iVar1 == 10)) || (iVar1 == 5)) || (iVar2 == 0x54555252)) &&
     (((iVar2 != 0x50524f58 && (iVar2 != 0x4745495a)) &&
      ((iVar2 != 0x53464c44 && (iVar2 != 0x5350574e)))))) {
    BlockCells(param_1,true);
  }
  return;
}
