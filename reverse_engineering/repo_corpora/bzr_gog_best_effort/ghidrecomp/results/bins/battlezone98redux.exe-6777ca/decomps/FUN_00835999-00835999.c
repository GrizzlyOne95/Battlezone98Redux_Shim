
void FUN_00835999(undefined4 param_1)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  int local_124;
  int local_120;
  undefined4 local_11c;
  int local_118;
  uint local_114;
  undefined4 local_110;
  undefined4 local_10c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  iVar1 = FUN_0082d377(param_1,0xffffd8ed,&local_124);
  local_120 = iVar1;
  local_11c = FUN_0082d377(param_1,0xffffd8ec,0);
  local_114 = local_124 + iVar1;
  local_110 = param_1;
  local_118 = iVar1;
  iVar2 = FUN_0082d338(param_1,0xffffd8eb);
  uVar4 = iVar1 + iVar2;
  do {
    if (local_114 < uVar4) {
LAB_00835a3a:
      FUN_0083e885();
      return;
    }
    local_10c = 0;
    uVar3 = FUN_00835b72(&local_118,uVar4,local_11c);
    if (uVar3 != 0) {
      iVar1 = uVar3 - local_120;
      if (uVar3 == uVar4) {
        iVar1 = iVar1 + 1;
      }
      FUN_0082ccca(param_1,iVar1);
      FUN_0082cfd8(param_1,0xffffd8eb);
      FUN_0083600d(&local_118,uVar4,uVar3);
      goto LAB_00835a3a;
    }
    uVar4 = uVar4 + 1;
  } while( true );
}

