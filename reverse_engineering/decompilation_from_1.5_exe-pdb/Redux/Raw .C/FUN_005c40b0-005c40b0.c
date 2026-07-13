
void __fastcall FUN_005c40b0(int param_1)

{
  undefined4 *puVar1;
  undefined1 local_28 [12];
  int local_1c;
  int local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_1c = param_1 + 0x38;
  local_18 = param_1;
  if ((*(int *)(param_1 + 0x1c) == 4) && (*(int *)(param_1 + 0x58) != 0)) {
    puVar1 = (undefined4 *)FUN_005b5370(local_28,*(undefined4 *)(param_1 + 0x58));
    local_14 = *puVar1;
    local_10 = puVar1[1];
    local_c = puVar1[2];
    *(undefined4 *)(local_18 + 0x38) = local_14;
    *(undefined4 *)(local_18 + 0x3c) = local_10;
    *(undefined4 *)(local_18 + 0x40) = local_c;
  }
  else {
    *(undefined4 *)(param_1 + 0x3c) = 0xbf800000;
  }
  FUN_0083e885();
  return;
}

