
void FUN_0082d56c(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = *(int *)(param_1 + 0x10);
  FUN_0082f92f(param_1,*(undefined4 *)(param_1 + 0x20));
  FUN_00830068(param_1);
  FUN_00838869(param_1,**(undefined4 **)(param_1 + 0x10),(*(undefined4 **)(param_1 + 0x10))[2] << 2,
               0);
  uVar2 = FUN_00838869(param_1,*(undefined4 *)(iVar1 + 0x34),*(undefined4 *)(iVar1 + 0x3c),0);
  *(undefined4 *)(iVar1 + 0x34) = uVar2;
  *(undefined4 *)(iVar1 + 0x3c) = 0;
  FUN_0082d63f(param_1,param_1);
  (**(code **)(iVar1 + 0xc))(*(undefined4 *)(iVar1 + 0x10),param_1,0x178,0);
  return;
}

