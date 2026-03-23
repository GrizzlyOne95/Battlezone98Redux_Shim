
/* WARNING: Removing unreachable block (ram,0x004e134d) */
/* WARNING: Removing unreachable block (ram,0x004e12c9) */
/* WARNING: Removing unreachable block (ram,0x004e1498) */

void __thiscall
FUN_004e1190(int param_1,undefined4 *param_2,int param_3,int param_4,uint param_5,char *param_6)

{
  short sVar1;
  undefined4 *puVar2;
  int iVar3;
  float10 fVar4;
  undefined1 local_11c [12];
  undefined1 local_110 [12];
  char *local_104;
  undefined1 *local_100;
  undefined4 local_fc;
  undefined4 local_f8;
  undefined1 *local_f4;
  undefined4 local_f0;
  undefined4 local_ec;
  undefined4 local_e8;
  undefined4 local_e4;
  char *local_e0;
  int local_dc;
  undefined4 *local_d8;
  undefined4 *local_d4;
  int local_d0;
  char *local_cc;
  undefined4 *local_c8;
  char local_c3;
  char local_c2;
  char local_c1;
  int local_c0;
  int local_bc [2];
  int local_b4;
  undefined1 local_b0 [48];
  undefined1 local_80 [20];
  int local_6c;
  undefined4 local_68;
  undefined4 local_64;
  undefined4 local_60;
  undefined4 local_5c;
  undefined4 local_58;
  undefined4 local_54;
  char local_50 [40];
  char local_28 [8];
  undefined1 uStack_20;
  undefined4 uStack_19;
  undefined1 local_14 [4];
  undefined1 uStack_10;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_c0 = param_1;
  if ((int)param_5 < 1) {
    sVar1 = FUN_0062c780(*(undefined4 *)(param_1 + 0x28),*(undefined4 *)(param_1 + 0x2c));
    param_5 = (uint)sVar1;
  }
  if (param_6 == (char *)0x0) {
    sprintf(local_50,"%.8s%d_%s",local_c0 + 0x30,param_5,*(undefined4 *)(local_c0 + 0x18));
    param_6 = local_50;
  }
  memset(local_bc,0,0x54);
  local_bc[0] = FUN_0062ccc0(0,"fun3d\\GameObjectClass.cpp");
  *(undefined4 *)(local_bc[0] + 8) = *(undefined4 *)(local_c0 + 0x30);
  *(undefined4 *)(local_bc[0] + 0xc) = *(undefined4 *)(local_c0 + 0x34);
  puVar2 = (undefined4 *)(local_bc[0] + 0x20);
  for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
    *puVar2 = *param_2;
    param_2 = param_2 + 1;
    puVar2 = puVar2 + 1;
  }
  *(int *)(local_bc[0] + 0x14) = param_3 << 0x10;
  if (param_4 != 0) {
    *(uint *)(local_bc[0] + 0x14) = *(uint *)(local_bc[0] + 0x14) | 0x10;
  }
  FUN_0062b940(local_bc[0],*(undefined4 *)(local_c0 + 0x1c));
  strncpy(local_28,(char *)(local_c0 + 0x28),8);
  local_f0 = 8;
  uStack_20 = 0;
  local_d0 = *(int *)(local_bc[0] + 0x84) + -1;
  switch(*(int *)(local_bc[0] + 0x84)) {
  case 1:
  case 3:
  case 4:
  case 6:
    strncpy((char *)((int)&uStack_19 + 1),(char *)(local_c0 + 0x28),8);
    local_e8 = 8;
    uStack_10 = 0;
    puVar2 = &uStack_19;
    do {
      local_d8 = puVar2;
      local_c2 = *(char *)((int)local_d8 + 1);
      puVar2 = (undefined4 *)((int)local_d8 + 1);
    } while (local_c2 != '\0');
    *puVar2 = 0x6664762e;
    *(undefined1 *)((int)local_d8 + 5) = 0;
    local_d8 = puVar2;
    local_dc = FUN_008258d0(0,local_bc,(int)&uStack_19 + 1);
    FUN_0062e650(local_bc[0],local_c0 + 0x10c,local_c0 + 0x118);
    puVar2 = (undefined4 *)FUN_004e0040(local_11c,local_bc[0]);
    local_5c = *puVar2;
    local_58 = puVar2[1];
    local_54 = puVar2[2];
    *(undefined4 *)(local_c0 + 0x124) = local_5c;
    *(undefined4 *)(local_c0 + 0x128) = local_58;
    *(undefined4 *)(local_c0 + 300) = local_54;
    fVar4 = (float10)FUN_0062e590(local_bc[0],*(undefined4 *)(local_c0 + 0x124),
                                  *(undefined4 *)(local_c0 + 0x128),*(undefined4 *)(local_c0 + 300))
    ;
    *(float *)(local_c0 + 0x130) = (float)fVar4;
    break;
  case 2:
  case 5:
  case 7:
  case 8:
  case 10:
  case 0xf:
    strncpy((char *)((int)&uStack_19 + 1),(char *)(local_c0 + 0x28),8);
    local_ec = 8;
    uStack_10 = 0;
    puVar2 = &uStack_19;
    do {
      local_d4 = puVar2;
      local_c3 = *(char *)((int)local_d4 + 1);
      puVar2 = (undefined4 *)((int)local_d4 + 1);
    } while (local_c3 != '\0');
    *puVar2 = 0x6664732e;
    *(undefined1 *)((int)local_d4 + 5) = 0;
    local_d4 = puVar2;
    local_dc = FUN_008253f0(0,local_bc,(int)&uStack_19 + 1);
    FUN_0062e650(local_bc[0],local_c0 + 0x10c,local_c0 + 0x118);
    puVar2 = (undefined4 *)FUN_004e0040(local_110,local_bc[0]);
    local_68 = *puVar2;
    local_64 = puVar2[1];
    local_60 = puVar2[2];
    *(undefined4 *)(local_c0 + 0x124) = local_68;
    *(undefined4 *)(local_c0 + 0x128) = local_64;
    *(undefined4 *)(local_c0 + 300) = local_60;
    fVar4 = (float10)FUN_0062e590(local_bc[0],*(undefined4 *)(local_c0 + 0x124),
                                  *(undefined4 *)(local_c0 + 0x128),*(undefined4 *)(local_c0 + 300))
    ;
    *(float *)(local_c0 + 0x130) = (float)fVar4;
    break;
  default:
    local_dc = 0;
  }
  if (local_dc == 0) {
    FUN_007d6c70("GameObject \"%s\" could not load \"%s\"\n",local_c0 + 0x38,(int)&uStack_19 + 1);
  }
  if (local_b4 == 0) {
    local_f8 = 0;
  }
  else {
    local_f8 = FUN_00825510(local_b0);
  }
  local_fc = local_f8;
  if (local_6c == 0) {
    local_f4 = (undefined1 *)0x0;
  }
  else {
    local_f4 = local_80;
  }
  local_100 = local_f4;
  local_c8 = (undefined4 *)FUN_0062c4a0(local_bc[0],param_5 & 0xffff,local_f8,local_f4);
  local_e0 = local_28;
  local_104 = (char *)(local_c8 + 0x1d);
  local_cc = local_104;
  do {
    local_c1 = *local_e0;
    *local_cc = local_c1;
    local_e0 = local_e0 + 1;
    local_cc = local_cc + 1;
  } while (local_c1 != '\0');
  if ((*(char *)(local_c8 + 0x1d) != '\0') && (iVar3 = FUN_00684ca0(0), iVar3 != 0)) {
    FUN_0067f480(local_c8);
  }
  FUN_0062baf0();
  local_e4 = FUN_00479f30(*local_c8);
  FUN_004d9630(param_6);
  if ((*(char *)(local_c8 + 0x1d) != '\0') && (iVar3 = FUN_00684ca0(0), iVar3 != 0)) {
    FUN_006802b0(local_e4);
  }
  FUN_0083e885();
  return;
}

