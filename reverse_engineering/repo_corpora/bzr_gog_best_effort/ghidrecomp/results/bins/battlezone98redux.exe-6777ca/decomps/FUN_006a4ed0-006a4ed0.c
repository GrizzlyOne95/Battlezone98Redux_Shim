
void FUN_006a4ed0(int param_1,undefined4 param_2,undefined4 param_3)

{
  int *piVar1;
  int iVar2;
  undefined4 local_8;
  
  if (*(int *)(param_1 + 0x14) != 0) {
    for (local_8 = 0; local_8 < *(int *)(param_1 + 0x14); local_8 = local_8 + 1) {
      piVar1 = (int *)FUN_0069d590(param_1 + 0xc,local_8);
      iVar2 = (*(code *)**(undefined4 **)(*piVar1 + 0x18))();
      if (*(int *)(iVar2 + 0x14) == 0x57494e47) {
        FUN_004dbd60(4,param_3);
      }
    }
  }
  return;
}

