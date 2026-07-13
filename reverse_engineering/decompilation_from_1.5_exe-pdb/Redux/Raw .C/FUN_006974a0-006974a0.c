
void __fastcall FUN_006974a0(int param_1)

{
  int iVar1;
  undefined4 *puVar2;
  undefined1 local_1c [4];
  undefined1 local_18 [4];
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  iVar1 = FUN_00417f90();
  if (iVar1 == 0) {
    puVar2 = (undefined4 *)(**(code **)(*(int *)(*(int *)(param_1 + 0x40) + 0x18) + 0xc))();
    local_14 = *puVar2;
    local_10 = puVar2[1];
    local_c = puVar2[2];
    FUN_006a09e0(local_14,local_10,local_c,local_18,local_1c);
  }
  FUN_0083e885();
  return;
}

