
int FUN_0082d69e(int param_1)

{
  undefined4 uVar1;
  int iVar2;
  
  iVar2 = FUN_00838869(param_1,0,0,0x78);
  FUN_0083010b(param_1,iVar2,8);
  FUN_0082d824(iVar2,*(undefined4 *)(param_1 + 0x10));
  FUN_0082d86b(iVar2,param_1);
  *(undefined4 *)(iVar2 + 0x48) = *(undefined4 *)(param_1 + 0x48);
  *(undefined4 *)(iVar2 + 0x4c) = *(undefined4 *)(param_1 + 0x4c);
  *(undefined4 *)(iVar2 + 0x50) = *(undefined4 *)(param_1 + 0x50);
  *(undefined1 *)(iVar2 + 0x38) = *(undefined1 *)(param_1 + 0x38);
  uVar1 = *(undefined4 *)(param_1 + 0x3c);
  *(undefined4 *)(iVar2 + 0x3c) = uVar1;
  *(undefined4 *)(iVar2 + 0x44) = *(undefined4 *)(param_1 + 0x44);
  *(undefined4 *)(iVar2 + 0x40) = uVar1;
  return iVar2;
}

