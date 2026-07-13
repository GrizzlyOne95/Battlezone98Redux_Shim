
void __fastcall FUN_004e6220(int param_1)

{
  int iVar1;
  undefined4 *puVar2;
  undefined1 local_28 [12];
  int local_1c;
  int local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_1c = *(int *)(param_1 + 8);
  local_18 = param_1;
  if (local_1c == 1) {
    *(undefined4 *)(param_1 + 0xc) = 2;
    FUN_00602920();
    FUN_004e5e80();
    iVar1 = *(int *)(*(int *)(local_18 + 0x134) + 8);
    puVar2 = (undefined4 *)
             FUN_004e5270(local_28,*(undefined4 *)(iVar1 + *(int *)(local_18 + 0x138) * 8),
                          *(undefined4 *)(iVar1 + 4 + *(int *)(local_18 + 0x138) * 8));
    local_14 = *puVar2;
    local_10 = puVar2[1];
    local_c = puVar2[2];
    *(undefined4 *)(local_18 + 0x28) = local_14;
    *(undefined4 *)(local_18 + 0x2c) = local_10;
    *(undefined4 *)(local_18 + 0x30) = local_c;
  }
  else if (local_1c == 2) {
    FUN_00601070();
  }
  else if (local_1c == 3) {
    FUN_006028d0();
  }
  FUN_0083e885();
  return;
}

