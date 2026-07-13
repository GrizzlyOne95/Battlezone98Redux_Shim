
void __thiscall FUN_005aa900(undefined4 param_1,undefined4 *param_2,int *param_3)

{
  int iVar1;
  undefined4 uVar2;
  
  *param_3 = *param_3 + 8;
  iVar1 = FUN_004b0400(param_1);
  if (iVar1 == 0) {
    *param_2 = 0;
  }
  else {
    uVar2 = FUN_004b9a90();
    *param_2 = uVar2;
  }
  iVar1 = FUN_00462610();
  if (iVar1 == 0) {
    param_2[1] = 0;
  }
  else {
    uVar2 = FUN_004b9a90();
    param_2[1] = uVar2;
  }
  FUN_004dfe80(param_2 + 2,param_3);
  return;
}

