
void __fastcall FUN_006977a0(int *param_1)

{
  int iVar1;
  undefined4 *puVar2;
  int iVar3;
  int iVar4;
  undefined4 uVar5;
  int local_c;
  
  iVar1 = FUN_00417f90();
  if (((iVar1 == 0) && (param_1[0xb] == 0)) && (param_1[5] != 0)) {
    iVar1 = param_1[0x10];
    for (local_c = 0; local_c < *(int *)(param_1[5] + 0x14); local_c = local_c + 1) {
      puVar2 = (undefined4 *)FUN_0069d590(param_1[5] + 0xc,local_c);
      iVar3 = FUN_00462630(puVar2[1]);
      if (((iVar3 == 0) || (iVar4 = FUN_0045bdf0(), iVar4 == 0)) ||
         (iVar3 = (**(code **)(*(int *)(iVar3 + 0x18) + 4))(), iVar3 != *(int *)param_1[0xf])) {
        FUN_006a8b30(param_1[5],puVar2,param_1[0xf]);
      }
      else {
        uVar5 = *puVar2;
        FUN_004dbd60(5,iVar1);
        (**(code **)(*param_1 + 0x24))(puVar2,uVar5);
      }
    }
  }
  return;
}

