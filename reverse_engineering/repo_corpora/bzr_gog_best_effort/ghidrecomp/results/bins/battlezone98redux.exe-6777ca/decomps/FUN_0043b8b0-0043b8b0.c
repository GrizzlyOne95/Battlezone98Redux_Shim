
void FUN_0043b8b0(int param_1)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  undefined1 local_e8 [28];
  uint local_cc;
  uint local_c8;
  undefined4 local_c4;
  undefined4 local_c0;
  undefined4 local_bc;
  undefined4 local_b8;
  undefined4 local_b4;
  undefined4 local_b0;
  undefined4 local_ac [16];
  undefined4 local_6c [19];
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  if (((((DAT_00915594 != 0) && (iVar1 = ___scrt_is_ucrt_dll_in_use(), iVar1 != 0)) &&
       (param_1 != 0)) && ((*(int *)(param_1 + 0x58) != 0 && (iVar1 = FUN_0043cfb0(), iVar1 != 0))))
     && ((*(uint *)(param_1 + 0x14) & 0x200) != 0)) {
    iVar1 = FUN_0062dfe0();
    if (((iVar1 == 0) || (iVar1 = ___scrt_is_user_matherr_present(), iVar1 != 0)) ||
       (*(float *)(param_1 + 0x20) != 0.0)) {
      puVar2 = (undefined4 *)FUN_0062e070();
      puVar3 = local_ac;
      for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
        *puVar3 = *puVar2;
        puVar2 = puVar2 + 1;
        puVar3 = puVar3 + 1;
      }
      puVar2 = local_ac;
      puVar3 = local_6c;
      for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
        *puVar3 = *puVar2;
        puVar2 = puVar2 + 1;
        puVar3 = puVar3 + 1;
      }
      puVar2 = (undefined4 *)FUN_00439de0();
      local_b8 = *puVar2;
      local_b4 = puVar2[1];
      local_b0 = puVar2[2];
      local_20 = local_b8;
      local_1c = local_b4;
      local_18 = local_b0;
      if (*(float *)(param_1 + 0x20) != 0.0) {
        puVar2 = (undefined4 *)FUN_00439d80();
        local_c4 = *puVar2;
        local_c0 = puVar2[1];
        local_bc = puVar2[2];
        puVar2 = (undefined4 *)
                 FUN_00439d00(local_e8,local_b8,local_b4,local_b0,*(float *)(param_1 + 0x20) * 0.002
                             );
        local_b8 = *puVar2;
        local_b4 = puVar2[1];
        local_b0 = puVar2[2];
        local_14 = local_b8;
        local_10 = local_b4;
        local_c = local_b0;
      }
      FUN_0043c410();
      FUN_0062bec0();
      FUN_0043c450();
    }
    else {
      FUN_0043c3a0();
    }
    if ((*(uint *)(param_1 + 0x14) & 0x400) == 0) {
      local_cc = *(uint *)(param_1 + 0x14) >> 0xc & 0xf;
      local_c8 = local_cc;
      if (local_cc == 3) {
        FUN_0043c5f0();
      }
      else {
        FUN_0043c5f0();
      }
      FUN_0043c610();
    }
    else {
      FUN_0043c5f0();
      FUN_0043c610();
    }
    FUN_0043c690();
  }
  FUN_0083e885();
  return;
}

