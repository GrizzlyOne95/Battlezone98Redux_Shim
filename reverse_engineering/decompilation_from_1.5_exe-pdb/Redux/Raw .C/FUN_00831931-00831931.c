
void FUN_00831931(int param_1,int param_2,int param_3)

{
  undefined4 uVar1;
  int iVar2;
  
  iVar2 = *(int *)(param_1 + 0x20);
  if ((iVar2 == param_2) || (*(int *)(param_3 + 0xc) != 0)) {
    iVar2 = 0;
  }
  FUN_008319de(iVar2,param_3);
  FUN_008319c8(*(undefined4 *)(param_1 + 0x3c),param_3);
  FUN_008319c8(*(undefined4 *)(param_1 + 0x40),param_3);
  FUN_0083177c(*(undefined1 *)(param_1 + 0x48),param_3);
  FUN_0083177c(*(undefined1 *)(param_1 + 0x49),param_3);
  FUN_0083177c(*(undefined1 *)(param_1 + 0x4a),param_3);
  FUN_0083177c(*(undefined1 *)(param_1 + 0x4b),param_3);
  iVar2 = *(int *)(param_1 + 0x2c);
  uVar1 = *(undefined4 *)(param_1 + 0xc);
  FUN_008319c8(iVar2,param_3);
  FUN_00831758(uVar1,iVar2 << 2,param_3);
  FUN_00831798(param_1,param_3);
  FUN_00831856(param_1,param_3);
  return;
}

