
/* WARNING: Removing unreachable block (ram,0x0058ecde) */
/* WARNING: Removing unreachable block (ram,0x0058e9bc) */
/* WARNING: Removing unreachable block (ram,0x0058ed15) */

void FUN_0058e9b0(undefined4 *param_1,int param_2)

{
  undefined4 uVar1;
  float *pfVar2;
  wchar_t *pwVar3;
  int iVar4;
  undefined4 *puVar5;
  undefined4 *puVar6;
  float10 fVar7;
  undefined4 *local_20;
  int local_14;
  undefined4 *local_10;
  undefined4 *local_c;
  undefined4 *local_8;
  
  *(uint *)(param_2 + 0x10) = *(uint *)(param_2 + 0x10) | 8;
  if (*(char *)((int)param_1 + 0x1f) == '\0') {
    local_c = (undefined4 *)param_1[0xc];
    local_8 = (undefined4 *)param_1[0xd];
    while (local_8 != DAT_02a13c94) {
      puVar5 = (undefined4 *)local_8[0xc];
      local_8[0xc] = local_c;
      fVar7 = (float10)FUN_00447ed0(local_c[9],*local_8,(float)local_8[2] - 0.01);
      local_8[9] = (float)fVar7;
      fVar7 = (float10)FUN_00447ed0(local_c[10],local_8[1],(float)local_8[3] - 0.01);
      local_8[10] = (float)fVar7;
      local_c = local_8;
      local_8 = puVar5;
    }
    puVar5 = local_8;
    puVar6 = param_1;
    for (iVar4 = 0xe; iVar4 != 0; iVar4 = iVar4 + -1) {
      *puVar6 = *puVar5;
      puVar5 = puVar5 + 1;
      puVar6 = puVar6 + 1;
    }
    *(undefined1 *)((int)param_1 + 0x1d) = 1;
    param_1[5] = 0xffffffff;
    fVar7 = (float10)FUN_00447ed0(local_c[9],*local_8,(float)local_8[2] - 0.01);
    param_1[9] = (float)fVar7;
    fVar7 = (float10)FUN_00447ed0(local_c[10],local_8[1],(float)local_8[3] - 0.01);
    param_1[10] = (float)fVar7;
    local_8[0xc] = param_1;
    param_1[0xc] = local_c;
  }
  else {
    local_c = (undefined4 *)param_1[0xd];
    local_8 = (undefined4 *)param_1[0xc];
    while (local_8 != DAT_02a13c94) {
      puVar5 = (undefined4 *)local_8[0xc];
      local_8[0xc] = local_c;
      fVar7 = (float10)FUN_00447ed0(local_c[9],*local_8,(float)local_8[2] - 0.01);
      local_8[9] = (float)fVar7;
      fVar7 = (float10)FUN_00447ed0(local_c[10],local_8[1],(float)local_8[3] - 0.01);
      local_8[10] = (float)fVar7;
      local_c = local_8;
      local_8 = puVar5;
    }
    puVar5 = local_8;
    puVar6 = param_1;
    for (iVar4 = 0xe; iVar4 != 0; iVar4 = iVar4 + -1) {
      *puVar6 = *puVar5;
      puVar5 = puVar5 + 1;
      puVar6 = puVar6 + 1;
    }
    *(undefined1 *)((int)param_1 + 0x1d) = 1;
    param_1[5] = 0xffffffff;
    fVar7 = (float10)FUN_00447ed0(local_c[9],*local_8,(float)local_8[2] - 0.01);
    param_1[9] = (float)fVar7;
    fVar7 = (float10)FUN_00447ed0(local_c[10],local_8[1],(float)local_8[3] - 0.01);
    param_1[10] = (float)fVar7;
    local_8[0xc] = param_1;
    param_1[0xc] = local_c;
  }
  DAT_0091815c = 0;
  local_10 = DAT_02a13c94;
  while (DAT_02a13cb0 = (undefined4 *)local_10[0xc], DAT_02a13cb0 != DAT_02a13ca0) {
    puVar5 = (undefined4 *)DAT_02a13cb0[0xc];
    local_20 = local_10;
    FUN_0058e0b0(puVar5,DAT_02a13cb0,local_10);
    if (puVar5 == DAT_02a13ca0) {
      local_10 = DAT_02a13cb0;
    }
    else {
      local_10 = (undefined4 *)FUN_0058e540(puVar5,DAT_02a13cb0);
    }
    for (; local_20 != local_10; local_20 = (undefined4 *)local_20[0xc]) {
    }
  }
  local_14 = 1;
  for (DAT_02a13cb0 = DAT_02a13c94; DAT_02a13cb0 != DAT_02a13ca0;
      DAT_02a13cb0 = (undefined4 *)DAT_02a13cb0[0xc]) {
    local_14 = local_14 + 1;
  }
  FUN_00592340();
  FUN_005920f0(local_14);
  DAT_02a13cb0 = DAT_02a13c94;
  while (local_14 != 0) {
    pfVar2 = (float *)FUN_005111d0(local_14 + -1);
    *pfVar2 = (float)DAT_02a13cb0[9] * DAT_02cc50e0;
    pfVar2[1] = (float)DAT_02a13cb0[10] * DAT_02cc50e0;
    if (DAT_02a13cb0[5] == -1) {
      pfVar2[2] = 0.0;
      pfVar2[3] = 0.0;
    }
    else {
      pfVar2[2] = (float)DAT_02a13cb0;
      pfVar2[3] = (float)DAT_02a13cb0[5];
    }
    DAT_02a13cb0 = (undefined4 *)DAT_02a13cb0[0xc];
    local_14 = local_14 + -1;
  }
  *(undefined4 *)(param_2 + 0x10) = 0;
  *(undefined4 *)(param_2 + 0x14) = 0;
  pwVar3 = std::
           basic_string<wchar_t,struct_std::char_traits<wchar_t>,class_std::allocator<wchar_t>_>::
           back((basic_string<wchar_t,struct_std::char_traits<wchar_t>,class_std::allocator<wchar_t>_>
                 *)(param_2 + 4));
  uVar1 = *(undefined4 *)(pwVar3 + 2);
  *(undefined4 *)(param_2 + 0x18) = *(undefined4 *)pwVar3;
  *(undefined4 *)(param_2 + 0x1c) = uVar1;
  return;
}

