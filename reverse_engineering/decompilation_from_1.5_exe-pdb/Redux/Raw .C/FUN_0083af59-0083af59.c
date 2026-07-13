
void FUN_0083af59(int param_1,int param_2)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined1 local_38 [24];
  undefined1 local_20 [24];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  iVar1 = *(int *)(param_1 + 0x30);
  uVar2 = *(undefined4 *)(iVar1 + 0x24);
  if (*(int *)(param_1 + 0x10) == 0x11d) {
    if (0x7ffffffd < *(int *)(param_2 + 0x1c)) {
      FUN_0083a089(iVar1,0x7ffffffd,"items in a constructor");
    }
    FUN_00839b96(param_1,local_20);
  }
  else {
    FUN_0083b767(param_1,local_20);
  }
  *(int *)(param_2 + 0x1c) = *(int *)(param_2 + 0x1c) + 1;
  FUN_00839bb2(param_1,0x3d);
  uVar3 = FUN_0083c706(iVar1,local_20);
  FUN_0083b5a6(param_1,local_38,0);
  uVar4 = FUN_0083c706(iVar1,local_38);
  FUN_0083c5d2(iVar1,9,*(undefined4 *)(*(int *)(param_2 + 0x18) + 8),uVar3,uVar4);
  *(undefined4 *)(iVar1 + 0x24) = uVar2;
  FUN_0083e885();
  return;
}

