
void FUN_00440960(undefined4 *param_1,int param_2,undefined4 param_3,undefined4 param_4,int *param_5
                 ,undefined4 *param_6)

{
  undefined4 *puVar1;
  int iVar2;
  int *piVar3;
  int *piVar4;
  undefined4 *puVar5;
  undefined1 local_240 [64];
  undefined1 local_200 [12];
  undefined1 local_1f4 [4];
  float local_1f0;
  int local_1ec;
  undefined4 local_1e8;
  undefined4 local_1e4;
  undefined4 local_1e0;
  undefined4 local_1dc;
  int local_1d8;
  undefined4 local_1d4;
  undefined4 local_1d0;
  undefined4 local_1cc;
  undefined4 local_1c8;
  undefined4 local_1c4;
  undefined4 local_1c0;
  undefined4 local_1bc;
  int local_1b8;
  undefined4 local_1b4;
  undefined4 local_1b0;
  undefined4 local_1ac;
  undefined4 local_1a8;
  undefined4 local_1a4;
  undefined4 local_1a0;
  undefined4 local_19c [16];
  undefined4 local_15c [30];
  undefined1 local_e4 [12];
  int local_d8 [20];
  undefined4 local_88;
  undefined4 local_60 [16];
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_1e0 = 0;
  for (; param_2 != 0; param_2 = *(int *)(param_2 + 0x7c)) {
    puVar1 = (undefined4 *)FUN_0081fe60(local_240,param_2 + 0x20,param_3);
    puVar5 = local_60;
    for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
      *puVar5 = *puVar1;
      puVar1 = puVar1 + 1;
      puVar5 = puVar5 + 1;
    }
    local_1ec = FUN_0043fff0(param_2);
    if (local_1ec != 0x1000) {
      FUN_00820180(&local_20,param_2 + 0xa0,1,local_60);
      puVar1 = (undefined4 *)
               FUN_00444ba0(local_200,*(undefined4 *)(param_2 + 0xa0),
                            *(undefined4 *)(param_2 + 0xa4),*(undefined4 *)(param_2 + 0xa8),param_2)
      ;
      local_14 = *puVar1;
      local_10 = puVar1[1];
      local_c = puVar1[2];
      local_1f0 = (float)param_1[6] + *(float *)(param_2 + 0xac);
      iVar2 = FUN_00443370(*param_1,param_1[1],param_1[2],param_1[3],param_1[4],param_1[5],local_20,
                           local_1c,local_18,local_14,local_10,local_c,local_1f0,param_4,local_1f4,
                           local_e4);
      if (iVar2 != 0) {
        local_1dc = 0;
        local_15c[0] = 0;
        local_d8[0] = 0;
        local_1d8 = local_1ec;
        if (local_1ec < 0x4001) {
          if (local_1ec == 0x4000) {
            local_1dc = FUN_004423d0(param_1,param_2,0x3f800000,local_60,param_4,local_d8,local_15c)
            ;
          }
          else if (local_1ec == 0x2000) {
            local_1d4 = local_20;
            local_1d0 = local_1c;
            local_1cc = local_18;
            local_1c8 = local_14;
            local_1c4 = local_10;
            local_1c0 = local_c;
            local_1bc = *(undefined4 *)(param_2 + 0xac);
            local_1b8 = param_2;
            local_1b4 = *(undefined4 *)(param_2 + 0xb0);
            local_1b0 = *(undefined4 *)(param_2 + 0xb4);
            local_1ac = *(undefined4 *)(param_2 + 0xb8);
            local_1a8 = *(undefined4 *)(param_2 + 0xbc);
            local_1a4 = *(undefined4 *)(param_2 + 0xc0);
            local_1a0 = *(undefined4 *)(param_2 + 0xc4);
            puVar1 = local_60;
            puVar5 = local_19c;
            for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
              *puVar5 = *puVar1;
              puVar1 = puVar1 + 1;
              puVar5 = puVar5 + 1;
            }
            iVar2 = FUN_00440e60(param_1,&local_1d4,param_4,local_d8,local_15c);
            if ((iVar2 == 0) &&
               (iVar2 = FUN_00440e60(&local_1d4,param_1,param_4,local_15c,local_d8), iVar2 == 0)) {
              local_1e4 = 0;
            }
            else {
              local_1e4 = 1;
            }
            local_1dc = local_1e4;
          }
          else if (local_1ec == 0x3000) {
            iVar2 = FUN_00441720(param_1,param_2,local_60,param_4,local_d8,local_15c);
            if ((iVar2 != 0) ||
               (((*(int *)(param_1[7] + 0x84) == 6 ||
                 (10.0 <= (float)param_1[0xc] - (float)param_1[9])) &&
                (iVar2 = FUN_00441ef0(param_2,local_60,param_1,param_4,local_15c,local_d8),
                iVar2 != 0)))) {
              local_1e8 = 1;
            }
            else {
              local_1e8 = 0;
            }
            local_1dc = local_1e8;
          }
        }
        else if (local_1ec == 0x5000) {
          local_1dc = FUN_004423d0(param_1,param_2,0x3f400000,local_60,param_4,local_d8,local_15c);
        }
        if (local_d8[0] != 0) {
          param_4 = local_88;
          piVar3 = local_d8;
          piVar4 = param_5;
          for (iVar2 = 0x1e; iVar2 != 0; iVar2 = iVar2 + -1) {
            *piVar4 = *piVar3;
            piVar3 = piVar3 + 1;
            piVar4 = piVar4 + 1;
          }
          puVar1 = local_15c;
          puVar5 = param_6;
          for (iVar2 = 0x1e; iVar2 != 0; iVar2 = iVar2 + -1) {
            *puVar5 = *puVar1;
            puVar1 = puVar1 + 1;
            puVar5 = puVar5 + 1;
          }
          local_1e0 = 1;
        }
      }
    }
    if ((*(int *)(param_2 + 0x80) != 0) &&
       (iVar2 = FUN_00440960(param_1,*(undefined4 *)(param_2 + 0x80),local_60,param_4,param_5,
                             param_6), iVar2 != 0)) {
      local_1e0 = 1;
    }
  }
  FUN_0083e885();
  return;
}

