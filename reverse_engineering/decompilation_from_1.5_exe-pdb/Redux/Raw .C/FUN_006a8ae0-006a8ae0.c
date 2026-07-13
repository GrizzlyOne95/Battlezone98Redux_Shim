
void __thiscall FUN_006a8ae0(undefined4 param_1,int param_2,int param_3,undefined4 param_4)

{
  undefined4 uVar1;
  int iVar2;
  
  uVar1 = FUN_0069d330(param_2 + 0xc,param_3,param_1);
  *(undefined4 *)(param_3 + 0x1c) = uVar1;
  iVar2 = FUN_00694a90(param_3,param_4);
  *(int *)(param_2 + 0x34) = *(int *)(param_2 + 0x34) + iVar2;
  *(int *)(param_3 + 0x24) = param_2;
  return;
}

