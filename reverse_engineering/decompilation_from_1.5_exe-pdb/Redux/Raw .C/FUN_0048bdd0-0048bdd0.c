
/* WARNING: Removing unreachable block (ram,0x0048be67) */
/* WARNING: Removing unreachable block (ram,0x0048bf38) */
/* WARNING: Removing unreachable block (ram,0x0048c009) */
/* WARNING: Removing unreachable block (ram,0x0048c06c) */
/* WARNING: Removing unreachable block (ram,0x0048c0f2) */
/* WARNING: Removing unreachable block (ram,0x0048c183) */
/* WARNING: Removing unreachable block (ram,0x0048c139) */
/* WARNING: Removing unreachable block (ram,0x0048c1d0) */
/* WARNING: Removing unreachable block (ram,0x0048c239) */
/* WARNING: Removing unreachable block (ram,0x0048c273) */
/* WARNING: Removing unreachable block (ram,0x0048c2e2) */
/* WARNING: Removing unreachable block (ram,0x0048c373) */
/* WARNING: Removing unreachable block (ram,0x0048c329) */
/* WARNING: Removing unreachable block (ram,0x0048c3bd) */
/* WARNING: Removing unreachable block (ram,0x0048bf5f) */
/* WARNING: Removing unreachable block (ram,0x0048bfc0) */
/* WARNING: Removing unreachable block (ram,0x0048c004) */
/* WARNING: Removing unreachable block (ram,0x0048be8e) */
/* WARNING: Removing unreachable block (ram,0x0048beed) */
/* WARNING: Removing unreachable block (ram,0x0048bf2f) */
/* WARNING: Removing unreachable block (ram,0x0048c3c1) */

undefined4 FUN_0048bdd0(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  undefined4 uVar2;
  uint uStack_1d0;
  undefined1 local_1b4 [8];
  undefined1 local_1ac [4];
  undefined1 local_1a8 [8];
  undefined4 local_1a0;
  undefined4 local_184;
  undefined4 local_17c;
  undefined4 local_174;
  undefined4 local_16c;
  char *local_164;
  undefined4 *local_15c;
  undefined4 local_154;
  undefined4 local_14c;
  undefined4 local_144;
  undefined4 local_13c;
  undefined4 local_134;
  undefined4 local_12c;
  undefined4 local_124;
  undefined4 local_11c;
  undefined4 local_114;
  undefined4 local_10c;
  undefined4 local_104;
  undefined4 local_100;
  undefined4 local_fc;
  undefined4 local_f8;
  undefined4 local_f4;
  undefined4 local_ec;
  char *local_e4;
  undefined4 *local_dc;
  undefined4 local_d4;
  undefined4 local_cc;
  undefined4 local_c4;
  undefined4 local_c0;
  undefined4 local_bc;
  undefined4 local_b4;
  undefined4 local_ac;
  undefined4 local_a4;
  undefined4 local_9c;
  undefined4 local_94;
  undefined4 local_8c;
  undefined4 *local_84;
  undefined4 local_7c;
  undefined4 local_74;
  undefined4 local_6c;
  undefined4 local_64;
  undefined4 *local_5c;
  undefined4 local_54;
  undefined4 local_4c;
  undefined4 local_44;
  undefined1 local_38;
  undefined1 local_37;
  undefined1 local_36;
  undefined1 local_35 [2];
  undefined1 local_33 [2];
  undefined1 local_31 [3];
  char local_2e;
  char local_29;
  char local_28;
  char local_26;
  char local_25;
  char local_23;
  char local_21;
  char local_1f;
  char local_1e;
  undefined1 local_1d;
  undefined4 local_1c;
  undefined4 *local_18;
  undefined1 *local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00849230;
  local_10 = ExceptionList;
  uStack_1d0 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_14 = (undefined1 *)&uStack_1d0;
  ExceptionList = &local_10;
  FUN_00422170();
  local_1d = 0;
  local_8 = 0;
  iVar1 = FUN_00416410();
  if (iVar1 == 0) {
    local_c0 = FUN_00417780(param_3);
    FUN_0048d930(param_1,1,*local_18,local_c0,param_4);
    ExceptionList = local_10;
    return param_1;
  }
  uVar2 = FUN_00420260(local_1a8);
  local_26 = FUN_004221b0(uVar2);
  if (local_26 == '\0') {
    uVar2 = FID_conflict_begin(local_1ac);
    local_28 = FUN_004221b0(uVar2);
    if (local_28 == '\0') {
      local_8c = get();
      local_94 = FUN_00422f10(local_8c);
      local_9c = FUN_004241e0(param_3);
      local_a4 = FUN_00422f60(local_31);
      local_23 = FUN_00422f40(local_9c,local_94);
      if (local_23 != '\0') {
        local_1c = param_2;
        local_bc = FUN_004241e0(param_3);
        local_ac = FUN_00428280();
        local_b4 = get();
        local_c4 = FUN_00422f10(local_b4);
        local_cc = FUN_00422f60(local_33);
        local_25 = FUN_00422f40(local_c4,local_bc);
        if (local_25 != '\0') {
          local_d4 = get();
          local_dc = (undefined4 *)FUN_004242f0(local_d4);
          local_e4 = (char *)FUN_004242d0(*local_dc);
          if (*local_e4 != '\0') {
            local_ec = FUN_00417780(param_3);
            local_f4 = get();
            FUN_0048d930(param_1,0,local_f4,local_ec,param_4);
            ExceptionList = local_10;
            return param_1;
          }
          local_fc = FUN_00417780(param_3);
          local_104 = get();
          FUN_0048d930(param_1,1,local_104,local_fc,param_4);
          ExceptionList = local_10;
          return param_1;
        }
      }
      local_114 = FUN_004241e0(param_3);
      local_10c = get();
      local_11c = FUN_00422f10(local_10c);
      local_124 = FUN_00422f60(local_35);
      local_1e = FUN_00422f40(local_11c,local_114);
      if (local_1e != '\0') {
        local_1c = param_2;
        local_12c = FUN_00422190();
        uVar2 = FID_conflict_begin(local_1b4);
        local_29 = FUN_004221b0(uVar2);
        if (local_29 == '\0') {
          local_134 = get();
          local_13c = FUN_00422f10(local_134);
          local_144 = FUN_004241e0(param_3);
          local_14c = FUN_00422f60(&local_37);
          local_1f = FUN_00422f40(local_144,local_13c);
          if (local_1f == '\0') goto LAB_0048c913;
        }
        local_154 = get();
        local_15c = (undefined4 *)FUN_004242f0(local_154);
        local_164 = (char *)FUN_004242d0(*local_15c);
        if (*local_164 != '\0') {
          local_16c = FUN_00417780(param_3);
          local_174 = get();
          FUN_0048d930(param_1,0,local_174,local_16c,param_4);
          ExceptionList = local_10;
          return param_1;
        }
        local_17c = FUN_00417780(param_3);
        local_184 = get();
        FUN_0048d930(param_1,1,local_184,local_17c,param_4);
        ExceptionList = local_10;
        return param_1;
      }
    }
    else {
      local_64 = FUN_004241e0(param_3);
      local_5c = (undefined4 *)FUN_00422e80();
      local_6c = FUN_00422f10(*local_5c);
      local_74 = FUN_00422f60(&local_36);
      local_21 = FUN_00422f40(local_6c,local_64);
      if (local_21 != '\0') {
        local_7c = FUN_00417780(param_3);
        local_84 = (undefined4 *)FUN_00422e80();
        FUN_0048d930(param_1,0,*local_84,local_7c,param_4);
        ExceptionList = local_10;
        return param_1;
      }
      local_21 = 0;
    }
  }
  else {
    local_f8 = get();
    local_1a0 = FUN_00422f10(local_f8);
    local_100 = FUN_004241e0(param_3);
    local_44 = FUN_00422f60(&local_38);
    local_2e = FUN_00422f40(local_100,local_1a0);
    if (local_2e != '\0') {
      local_4c = FUN_00417780(param_3);
      local_54 = get();
      FUN_0048d930(param_1,1,local_54,local_4c,param_4);
      ExceptionList = local_10;
      return param_1;
    }
    local_2e = 0;
  }
LAB_0048c913:
  uVar2 = FUN_0048c930();
  return uVar2;
}

