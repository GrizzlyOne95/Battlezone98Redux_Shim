
void FUN_00692990(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  int local_8;
  
  iVar1 = *(int *)(DAT_00920f04 + param_1 * 4);
  FUN_006a5fd0("AIBuild_CreditDistribute team %d",param_1);
  uVar2 = *(undefined4 *)(iVar1 + 0xbc);
  for (local_8 = 0; local_8 < 0x20; local_8 = local_8 + 1) {
    *(undefined4 *)(iVar1 + 0xbc + local_8 * 4) = 0;
  }
  FUN_00692ba0(param_1,uVar2);
  return;
}

