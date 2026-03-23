
void FUN_0043d460(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  undefined1 local_50 [16];
  undefined4 local_40;
  code *local_28;
  undefined1 local_24 [4];
  undefined4 local_20;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  uVar2 = 0;
  if ((*(int *)(param_1 + 0x18) != 4) ||
     (iVar1 = FUN_00822e60(0), (uint)(iVar1 - *(int *)(param_1 + 0x1c)) < 0x2711)) {
    FUN_0043a990(local_50);
    FUN_0043a9e0(local_24);
    local_28 = FUN_0043d3e0;
    local_40 = 5;
    local_20 = 10000;
    uVar2 = FUN_0043aa30(param_1,0,local_50,local_24);
  }
  FUN_0083e885(uVar2);
  return;
}

