
void FUN_00838ef5(int param_1,undefined4 param_2,int param_3)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined1 local_58 [80];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  FUN_0082e741(local_58,*(int *)(param_1 + 0x40) + 0x10,0x50);
  uVar1 = FUN_0082e8cd(*(undefined4 *)(param_1 + 0x34),"%s:%d: %s",local_58,
                       *(undefined4 *)(param_1 + 4),param_2);
  if (param_3 != 0) {
    if (param_3 - 0x11cU < 3) {
      FUN_00839600(param_1,0);
      uVar2 = **(undefined4 **)(param_1 + 0x3c);
    }
    else {
      uVar2 = FUN_008390ce(param_1,param_3);
    }
    FUN_0082e8cd(*(undefined4 *)(param_1 + 0x34),"%s near \'%s\'",uVar1,uVar2);
  }
  FUN_0082f657(*(undefined4 *)(param_1 + 0x34),3);
  FUN_0083e885();
  return;
}

