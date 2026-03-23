
void FUN_00445690(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                 undefined4 param_5,undefined4 param_6,int param_7,undefined4 param_8,
                 undefined4 param_9,int *param_10,undefined4 *param_11,undefined4 *param_12,
                 float param_13,int param_14)

{
  undefined4 *puVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined1 local_17c [64];
  undefined1 local_13c [12];
  undefined1 local_130 [12];
  undefined1 local_124 [12];
  undefined1 local_118 [12];
  undefined1 local_10c [12];
  undefined1 local_100 [12];
  undefined1 local_f4 [12];
  undefined1 local_e8 [12];
  undefined1 local_dc [12];
  undefined1 local_d0 [12];
  int local_c4;
  int local_c0;
  float local_bc;
  int local_b8;
  int local_b4;
  int local_b0;
  undefined4 local_ac;
  undefined4 local_a8;
  undefined4 local_a4;
  undefined4 local_a0;
  undefined4 local_9c;
  undefined4 local_98;
  undefined4 local_94;
  undefined4 local_90 [16];
  undefined4 local_50;
  undefined4 local_4c;
  undefined4 local_48;
  undefined4 local_44;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_b0 = 0;
  do {
    if (param_7 == 0) {
      if (local_b0 != 0) {
        *param_11 = param_9;
        *param_12 = local_14;
        param_12[1] = local_10;
        param_12[2] = local_c;
        *param_10 = local_b8;
      }
      FUN_0083e885();
      return;
    }
    puVar1 = (undefined4 *)FUN_0081fe60(local_17c,param_7 + 0x20,param_8);
    puVar3 = local_90;
    for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
      *puVar3 = *puVar1;
      puVar1 = puVar1 + 1;
      puVar3 = puVar3 + 1;
    }
    local_c0 = FUN_0043fff0(param_7);
    if (local_c0 != 0x1000) {
      FUN_00820180(&local_a8,param_7 + 0xa0,1,local_90);
      puVar1 = (undefined4 *)FUN_00440000(local_100,0,0,0,param_7);
      puVar1 = (undefined4 *)FUN_00444ba0(local_e8,*puVar1,puVar1[1],puVar1[2]);
      local_9c = *puVar1;
      local_98 = puVar1[1];
      local_94 = puVar1[2];
      local_bc = *(float *)(param_7 + 0xac);
      if ((local_c0 == 0x3000) && ((param_14 == 0 || (*(int *)(param_7 + 0x9c) == 0)))) {
        local_c0 = 0x2000;
      }
      local_b4 = local_c0;
      if (local_c0 < 0x4001) {
        if (local_c0 == 0x4000) {
LAB_0044584b:
          iVar2 = FUN_00443370(param_1,param_2,param_3,param_4,param_5,param_6,local_a8,local_a4,
                               local_a0,local_9c,local_98,local_94,local_bc + param_13,param_9,
                               &local_ac,&local_20);
          if (iVar2 != 0) {
            local_b0 = 1;
            param_9 = local_ac;
            local_14 = local_20;
            local_10 = local_1c;
            local_c = local_18;
            local_b8 = param_7;
          }
        }
        else if (local_c0 == 0x2000) {
          puVar1 = (undefined4 *)FUN_00445260(local_d0,&param_1,local_90);
          local_50 = *puVar1;
          local_4c = puVar1[1];
          local_48 = puVar1[2];
          puVar1 = (undefined4 *)
                   FUN_004401a0(local_118,param_4,param_5,param_6,local_9c,local_98,local_94);
          local_44 = *puVar1;
          local_40 = puVar1[1];
          local_3c = puVar1[2];
          puVar1 = (undefined4 *)FUN_00440300(local_130,&local_44,local_90);
          local_44 = *puVar1;
          local_40 = puVar1[1];
          local_3c = puVar1[2];
          iVar2 = FUN_00445d90(local_50,local_4c,local_48,local_44,local_40,local_3c,
                               *(undefined4 *)(param_7 + 0xb0),*(undefined4 *)(param_7 + 0xb4),
                               *(undefined4 *)(param_7 + 0xb8),*(undefined4 *)(param_7 + 0xbc),
                               *(undefined4 *)(param_7 + 0xc0),*(undefined4 *)(param_7 + 0xc4),
                               param_9,&local_ac,&local_20,param_13);
          if (iVar2 != 0) {
            local_b0 = 1;
            param_9 = local_ac;
            puVar1 = (undefined4 *)FUN_00440210(local_13c,&local_20,local_90);
            local_14 = *puVar1;
            local_10 = puVar1[1];
            local_c = puVar1[2];
            local_b8 = param_7;
          }
        }
        else if ((local_c0 == 0x3000) &&
                (iVar2 = FUN_00443370(param_1,param_2,param_3,param_4,param_5,param_6,local_a8,
                                      local_a4,local_a0,local_9c,local_98,local_94,
                                      local_bc + param_13,param_9,&local_ac,&local_20), iVar2 != 0))
        {
          puVar1 = (undefined4 *)FUN_00445260(local_f4,&param_1,local_90);
          local_38 = *puVar1;
          local_34 = puVar1[1];
          local_30 = puVar1[2];
          puVar1 = (undefined4 *)
                   FUN_004401a0(local_124,param_4,param_5,param_6,local_9c,local_98,local_94);
          local_2c = *puVar1;
          local_28 = puVar1[1];
          local_24 = puVar1[2];
          puVar1 = (undefined4 *)FUN_00440300(local_10c,&local_2c,local_90);
          local_2c = *puVar1;
          local_28 = puVar1[1];
          local_24 = puVar1[2];
          iVar2 = FUN_00444580(local_38,local_34,local_30,local_2c,local_28,local_24,
                               *(undefined4 *)(param_7 + 0x9c),param_9,&local_ac,&local_20);
          if (iVar2 != 0) {
            local_b0 = 1;
            param_9 = local_ac;
            puVar1 = (undefined4 *)FUN_00440210(local_dc,&local_20,local_90);
            local_14 = *puVar1;
            local_10 = puVar1[1];
            local_c = puVar1[2];
            local_b8 = param_7;
          }
        }
      }
      else if (local_c0 == 0x5000) {
        local_bc = local_bc * 0.75;
        goto LAB_0044584b;
      }
    }
    if ((*(int *)(param_7 + 0x80) != 0) &&
       (iVar2 = FUN_00445690(param_1,param_2,param_3,param_4,param_5,param_6,
                             *(undefined4 *)(param_7 + 0x80),local_90,param_9,&local_c4,&local_ac,
                             &local_20,param_13,param_14), iVar2 != 0)) {
      local_b0 = 1;
      param_9 = local_ac;
      local_14 = local_20;
      local_10 = local_1c;
      local_c = local_18;
      local_b8 = local_c4;
    }
    param_7 = *(int *)(param_7 + 0x7c);
  } while( true );
}

