
undefined4 * __thiscall
FUN_008412a0(undefined4 *param_1,int param_2,int param_3,int param_4,int param_5)

{
  int iVar1;
  int iVar2;
  undefined4 *puVar3;
  
  if (param_4 != param_5) {
    puVar3 = param_1;
    if (7 < (uint)param_1[5]) {
      puVar3 = (undefined4 *)*param_1;
    }
    if (param_3 == 0) {
      iVar2 = 0;
    }
    else {
      iVar2 = param_3 - param_2 >> 1;
    }
    iVar1 = 0;
    if (param_2 != 0) {
      iVar1 = param_2 - (int)puVar3 >> 1;
    }
    FUN_007744d0(iVar1,iVar2,param_4,param_5 - param_4 >> 1);
    return param_1;
  }
  puVar3 = param_1;
  if (7 < (uint)param_1[5]) {
    puVar3 = (undefined4 *)*param_1;
  }
  if (param_3 == 0) {
    iVar2 = 0;
  }
  else {
    iVar2 = param_3 - param_2 >> 1;
  }
  if (param_2 != 0) {
    FID_conflict_erase(param_2 - (int)puVar3 >> 1,iVar2);
    return param_1;
  }
  FID_conflict_erase(0,iVar2);
  return param_1;
}

