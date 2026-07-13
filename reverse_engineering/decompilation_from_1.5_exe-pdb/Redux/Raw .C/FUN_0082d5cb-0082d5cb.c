
void FUN_0082d5cb(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  
  iVar1 = *(int *)(param_1 + 0x10);
  FUN_0082d86b(param_1,param_1);
  uVar2 = FUN_00830f66(param_1,0,2);
  *(undefined4 *)(param_1 + 0x48) = uVar2;
  *(undefined4 *)(param_1 + 0x50) = 5;
  iVar3 = *(int *)(param_1 + 0x10);
  uVar2 = FUN_00830f66(param_1,0,2);
  *(undefined4 *)(iVar3 + 0x60) = uVar2;
  *(undefined4 *)(iVar3 + 0x68) = 5;
  FUN_00830af4(param_1,0x20);
  FUN_008334ee(param_1);
  FUN_00838eb8(param_1);
  iVar3 = FUN_008309f4(param_1,"not enough memory",0x11);
  *(byte *)(iVar3 + 5) = *(byte *)(iVar3 + 5) | 0x20;
  *(int *)(iVar1 + 0x40) = *(int *)(iVar1 + 0x44) << 2;
  return;
}

