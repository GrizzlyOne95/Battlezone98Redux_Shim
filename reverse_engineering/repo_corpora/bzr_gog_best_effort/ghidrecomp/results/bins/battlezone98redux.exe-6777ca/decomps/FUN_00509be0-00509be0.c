
/* WARNING: Function: __alloca_probe_16 replaced with injection: alloca_probe */
/* WARNING: Unable to track spacebase fully for stack */

void FUN_00509be0(undefined4 param_1,undefined4 param_2,byte param_3,int param_4)

{
  undefined4 *puVar1;
  float *pfVar2;
  int iVar3;
  float *pfVar4;
  undefined8 local_a0;
  undefined8 local_98;
  double local_88;
  undefined1 *local_80;
  int local_7c;
  int local_78;
  int local_74;
  char *local_70;
  undefined1 *local_6c;
  int local_68;
  undefined4 local_64;
  int local_60;
  int local_5c;
  char local_56;
  byte local_55;
  float local_54 [4];
  float local_44;
  float local_40;
  float local_3c;
  float local_38;
  float local_34;
  undefined8 local_2c;
  double local_24;
  double local_1c;
  undefined4 local_14;
  float local_10;
  float local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_98 = (double)CONCAT44(1,&local_55);
  local_a0 = (double)CONCAT44(param_1,0x509c04);
  FUN_004ce730();
  local_55 = local_55 - 0x30;
  local_60 = local_55 - 1;
  switch(local_60) {
  case 0:
    local_98 = (double)CONCAT44(1,&local_56);
    local_a0 = (double)CONCAT44(param_1,0x509c66);
    FUN_004ce5e0();
    if (local_56 == '\0') {
      local_70 = "false";
    }
    else {
      local_70 = "true";
    }
    local_98 = (double)CONCAT44(local_70,0x509c8a);
    FUN_007d6a70();
    if (param_3 != 0) {
      local_98 = (double)(ulonglong)CONCAT14(local_56,param_2);
      local_a0 = (double)CONCAT44(0x509ca3,(undefined4)local_a0);
      FUN_0082cbf5();
    }
    break;
  case 1:
    local_98 = (double)CONCAT44(4,&local_64);
    local_a0 = (double)CONCAT44(param_1,0x509cba);
    FUN_004ce910();
    local_98 = (double)CONCAT44(local_64,0x509cc6);
    local_64 = FUN_004cf880();
    local_98 = (double)CONCAT44(local_64,&DAT_0087d0f0);
    local_a0 = (double)CONCAT44(0x509cda,(undefined4)local_a0);
    FUN_007d6a70();
    if (param_3 != 0) {
      local_98 = (double)CONCAT44(local_64,param_2);
      local_a0 = (double)CONCAT44(0x509cf2,(undefined4)local_a0);
      FUN_0082cced();
    }
    break;
  case 2:
    local_98 = (double)CONCAT44(8,&local_88);
    local_a0 = (double)CONCAT44(param_1,0x509d0c);
    FUN_004cec20();
    local_98 = local_88;
    local_a0 = 4.239439310141163e-306;
    FUN_007d6a70();
    if (param_3 != 0) {
      local_98 = local_88;
      local_a0 = (double)CONCAT44(param_2,0x509d4a);
      FUN_0082cd58();
    }
    break;
  case 3:
    local_98 = (double)CONCAT44(4,&local_5c);
    local_a0 = (double)CONCAT44(param_1,0x509d61);
    FUN_004ce910();
    local_98 = (double)CONCAT44(0x509d6f,(undefined4)local_98);
    iVar3 = -(local_5c + 1);
    local_80 = &stack0xffffff70 + iVar3;
    local_6c = &stack0xffffff70 + iVar3;
    *(int *)((int)&local_98 + iVar3 + 4) = local_5c;
    *(undefined1 **)((int)&local_98 + iVar3) = local_6c;
    *(undefined4 *)((int)&local_a0 + iVar3 + 4) = param_1;
    *(undefined4 *)((int)&local_a0 + iVar3) = 0x509d89;
    FUN_004ce2f0();
    *(undefined1 **)((int)&local_98 + iVar3 + 4) = local_6c;
    *(int *)((int)&local_98 + iVar3) = local_5c;
    *(char **)((int)&local_a0 + iVar3 + 4) = "\"%.*s\"";
    *(undefined4 *)((int)&local_a0 + iVar3) = 0x509d9e;
    FUN_007d6a70();
    if (param_3 != 0) {
      *(int *)((int)&local_98 + iVar3 + 4) = local_5c;
      *(undefined1 **)((int)&local_98 + iVar3) = local_6c;
      *(undefined4 *)((int)&local_a0 + iVar3 + 4) = param_2;
      *(undefined4 *)((int)&local_a0 + iVar3) = 0x509dba;
      FUN_0082cd08();
    }
    break;
  case 4:
    local_98 = (double)CONCAT44(4,&local_7c);
    local_a0 = (double)CONCAT44(param_1,0x509dd1);
    FUN_004ce910();
    local_98 = 0.0;
    local_a0 = (double)CONCAT44(param_2,0x509de1);
    FUN_0082c68b();
    local_98 = 4.239873894879279e-306;
    FUN_007d6a70();
    iVar3 = param_4 + 1;
    for (local_68 = 0; local_68 < local_7c; local_68 = local_68 + 1) {
      local_98 = (double)CONCAT44("                                ",iVar3 * 2);
      local_a0 = 4.2399825410638136e-306;
      FUN_007d6a70();
      local_98 = (double)CONCAT44(iVar3,(uint)param_3);
      local_a0 = (double)CONCAT44(param_2,param_1);
      FUN_00509be0();
      local_98 = 4.240004270300737e-306;
      FUN_007d6a70();
      local_98 = (double)CONCAT44(iVar3,(uint)param_3);
      local_a0 = (double)CONCAT44(param_2,param_1);
      FUN_00509be0();
      if (param_3 != 0) {
        local_98 = (double)CONCAT44(0xfffffffd,param_2);
        local_a0 = (double)CONCAT44(0x509e7e,(undefined4)local_a0);
        FUN_0082ced4();
      }
    }
    local_98 = (double)CONCAT44("                                ",param_4 << 1);
    local_a0 = 4.240015134919239e-306;
    FUN_007d6a70();
    break;
  default:
    local_98 = 4.239406716285665e-306;
    FUN_007d6a70();
    if (param_3 != 0) {
      local_98 = (double)CONCAT44(param_2,0x509c4f);
      FUN_0082cd45();
    }
    break;
  case 6:
    local_98 = (double)CONCAT44(4,&local_78);
    local_a0 = (double)CONCAT44(param_1,0x509eb8);
    FUN_004cea20();
    local_74 = local_78;
    if (local_78 == 0xe3f3088) {
      local_98 = (double)CONCAT44(0xc,&local_14);
      local_a0 = (double)CONCAT44(param_1,0x509ee7);
      FUN_004ced10();
      local_98 = (double)local_c;
      local_a0 = (double)local_10;
      FUN_007d6a70();
      if (param_3 != 0) {
        local_98 = (double)CONCAT44(param_2,0x509f2f);
        puVar1 = (undefined4 *)FUN_004ff7e0();
        *puVar1 = local_14;
        puVar1[1] = local_10;
        puVar1[2] = local_c;
      }
    }
    else if (local_78 == 0x247e1851) {
      local_98 = (double)CONCAT44(0x40,local_54);
      local_a0 = (double)CONCAT44(param_1,0x509f57);
      FUN_004cef70();
      local_98 = local_1c;
      local_a0 = local_24;
      FUN_007d6a70("{right_x=%f, right_y=%f, right_z=%f, up_x=%f, up_y=%f, up_z=%f, front_x=%f, front_y=%f, front_z=%f, posit_x=%f, posit_y=%f, posit_z=%f}"
                   ,(double)local_54[0],(double)local_54[1],(double)local_54[2],(double)local_54[3],
                   (double)local_44,(double)local_40,(double)local_3c,(double)local_38,
                   (double)local_34,local_2c);
      if (param_3 != 0) {
        local_98 = (double)CONCAT44(param_2,0x50a011);
        pfVar2 = (float *)FUN_004ff840();
        pfVar4 = local_54;
        for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
          *pfVar2 = *pfVar4;
          pfVar4 = pfVar4 + 1;
          pfVar2 = pfVar2 + 1;
        }
      }
    }
  }
  FUN_0083e885();
  return;
}

