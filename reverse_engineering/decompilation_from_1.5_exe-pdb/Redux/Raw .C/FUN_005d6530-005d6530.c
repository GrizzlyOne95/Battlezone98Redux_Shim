
void __fastcall FUN_005d6530(int param_1)

{
  char cVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined8 uVar4;
  undefined1 local_b8 [56];
  undefined8 local_80;
  undefined4 local_78;
  int *local_74;
  undefined8 local_70;
  undefined4 *local_68;
  int local_64;
  float local_60;
  int local_5c;
  float local_58;
  int *local_54;
  int local_50;
  undefined4 local_4c;
  undefined4 local_48;
  undefined4 local_44;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  int local_28;
  int local_24;
  int local_20;
  int local_1c;
  int local_18;
  int local_14;
  int local_10;
  int local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  if (DAT_008eaab0 == 0) {
    *(undefined1 *)(param_1 + 0x1e8) = 0;
  }
  local_50 = param_1;
  if (*(char *)(param_1 + 0x1e8) != '\0') {
    *(undefined1 *)(param_1 + 0x1e8) = 0;
    *(undefined1 *)(param_1 + 0x1e9) = 1;
    local_28 = (int)(((float)(*(int *)(&DAT_008724f8 + (uint)*(byte *)(param_1 + 0x1ea) * 8) +
                             -0x140) * DAT_00917594[2] * DAT_00917594[10]) / 240.0 + *DAT_00917594);
    local_24 = (int)(((float)(*(int *)(&DAT_008724fc + (uint)*(byte *)(param_1 + 0x1ea) * 8) + -0xf0
                             ) * DAT_00917594[3] * DAT_00917594[10]) / -240.0 + DAT_00917594[1]);
    local_20 = (int)(((float)(*(int *)(&DAT_008724f8 + (uint)*(byte *)(param_1 + 0x1ea) * 8) + -0xc0
                             ) * DAT_00917594[2] * DAT_00917594[10]) / 240.0 + *DAT_00917594);
    local_1c = (int)(((float)(*(int *)(&DAT_008724fc + (uint)*(byte *)(param_1 + 0x1ea) * 8) + -0x70
                             ) * DAT_00917594[3] * DAT_00917594[10]) / -240.0 + DAT_00917594[1]);
    local_18 = local_28;
    local_14 = local_24;
    local_10 = local_20;
    local_c = local_1c;
    iVar2 = FUN_0068f360();
    if (-1 < iVar2) {
      if ((((*(float *)(local_50 + 0x24) != (float)local_28) ||
           (*(float *)(local_50 + 0x28) != (float)local_24)) ||
          (*(float *)(local_50 + 0x2c) != (float)local_20)) ||
         (*(float *)(local_50 + 0x30) != (float)local_1c)) {
        FUN_006886a0(local_50 + 0x10,local_18,local_14,local_10,local_c);
      }
      local_58 = DAT_00920ef4;
      FUN_00684f50(local_50 + 0x10);
      DAT_02cecf74 = 1;
      FUN_00616e80(local_50 + 0x10);
      FUN_005d6130();
      FUN_00616500();
      FUN_00780c70(local_50 + 0x10);
      FUN_00584d30(local_50 + 0x10);
      FUN_004d4610(local_50 + 0x10);
      local_74 = (int *)FUN_00417c70();
      FUN_005b28e0(*(undefined8 *)(local_50 + 0x90),*(undefined8 *)(local_50 + 0xa0),
                   *(undefined8 *)(local_50 + 0xa8),local_b8);
      local_80 = CONCAT44(local_80._4_4_,(undefined4)local_80);
      local_70 = CONCAT44(local_70._4_4_,(undefined4)local_70);
      while( true ) {
        cVar1 = FUN_00462710(&local_68);
        if (cVar1 == '\0') break;
        local_54 = (int *)FUN_004da060(*local_68);
        if ((local_54 != (int *)0x0) && (local_54 != local_74)) {
          cVar1 = (**(code **)(*local_54 + 0x14))();
          if (cVar1 != '\0') {
            iVar2 = FUN_00462400();
            local_78 = *(undefined4 *)(iVar2 + 0xc);
            puVar3 = (undefined4 *)(**(code **)(local_54[6] + 0xc))();
            local_34 = *puVar3;
            local_30 = puVar3[1];
            local_2c = puVar3[2];
            FUN_00820180();
            iVar2 = FUN_006895d0(local_50 + 0x10,&local_34,local_78);
            if (iVar2 < 1) {
              local_64 = local_54[0x8c];
              puVar3 = (undefined4 *)FUN_0062e120();
              local_4c = *puVar3;
              local_48 = puVar3[1];
              local_44 = puVar3[2];
              local_40 = local_4c;
              local_3c = local_48;
              local_38 = local_44;
              uVar4 = FUN_00497780(&local_4c,local_50 + 0x10,&local_60);
              local_80 = uVar4;
              local_70 = uVar4;
              if (0.0 < local_60) {
                local_5c = (int)(local_60 * 1.0);
                FUN_0068ce80(local_50 + 0x10,*(undefined4 *)(local_50 + 0xc),uVar4,0x3f800000,
                             local_5c,local_5c,0x250004);
              }
            }
          }
        }
      }
      DAT_00920ef4 = local_58 + 0.09;
      FUN_0068c0f0();
      DAT_00920ef4 = local_58 + 0.02;
      FUN_0043fb00(&DAT_0100ff00,local_28,local_24,local_20,local_1c);
      DAT_00920ef4 = local_58;
      DAT_02cecf74 = 0;
      FUN_00684f10();
    }
  }
  FUN_0083e885();
  return;
}

