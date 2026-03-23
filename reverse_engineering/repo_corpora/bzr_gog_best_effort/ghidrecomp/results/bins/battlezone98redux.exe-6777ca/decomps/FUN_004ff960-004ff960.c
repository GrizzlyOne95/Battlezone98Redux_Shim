
void FUN_004ff960(undefined4 param_1)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 uVar3;
  uint local_5c;
  undefined4 local_58;
  undefined1 local_50 [16];
  undefined4 local_40;
  undefined1 local_24 [4];
  undefined4 local_20;
  uint local_18;
  undefined4 local_14;
  undefined4 local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  uVar1 = FUN_0082ba59(param_1,1,0);
  local_58 = 0;
  iVar2 = FUN_0082d490(param_1,2,uVar1);
  if (0 < iVar2) {
    uVar3 = FUN_004ff750(param_1,2);
    iVar2 = FUN_00462630(uVar3);
    if (iVar2 != 0) {
      local_58 = (**(code **)(*(int *)(iVar2 + 0x18) + 0x30))();
    }
  }
  FUN_0043a990(local_50);
  local_40 = 1;
  FUN_0043a9e0(local_24);
  local_20 = FUN_0082c1fd(param_1,3,local_20);
  iVar2 = FUN_0082d2e8(param_1,4);
  local_5c = (uint)(iVar2 != 0);
  local_18 = local_5c;
  local_14 = FUN_0082c1fd(param_1,5,local_14);
  local_c = FUN_0082c1fd(param_1,6,local_c);
  FUN_0043aa30(uVar1,local_58,local_50,local_24);
  FUN_0083e885();
  return;
}

