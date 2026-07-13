
void FUN_00499540(void)

{
  char cVar1;
  undefined4 *puVar2;
  int *piVar3;
  int iVar4;
  float10 fVar5;
  undefined1 local_80 [16];
  undefined1 local_70 [8];
  undefined4 local_68;
  float local_64;
  int local_60;
  float *local_5c;
  int local_58;
  undefined4 local_54;
  int local_50;
  undefined4 local_4c;
  int local_44;
  int *local_40;
  int *local_3c;
  int local_38;
  int local_34;
  int local_30;
  int local_2c;
  int local_28;
  int local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  FUN_00422170();
  puVar2 = (undefined4 *)FID_conflict_begin();
  local_4c = *puVar2;
  while( true ) {
    FID_conflict_end();
    cVar1 = FID_conflict_operator__();
    if (cVar1 == '\0') break;
    piVar3 = (int *)FUN_00421ec0();
    local_44 = *piVar3;
    local_5c = (float *)(**(code **)(*(int *)(local_44 + 0x18) + 0xc))();
    puVar2 = (undefined4 *)
             FUN_006897e0(local_80,DAT_00917594,(double)*local_5c,(double)local_5c[1],
                          (double)local_5c[2]);
    local_20 = *puVar2;
    local_1c = puVar2[1];
    local_18 = puVar2[2];
    local_14 = local_20;
    local_10 = local_1c;
    local_c = local_18;
    iVar4 = FUN_00462400();
    local_68 = *(undefined4 *)(iVar4 + 0xc);
    iVar4 = FUN_006895d0();
    if (iVar4 < 1) {
      fVar5 = (float10)FUN_004428b0(&local_14,&local_14);
      local_64 = (float)fVar5;
      if (local_64 <= 40000.0) {
        local_54 = FUN_00492ce0();
        local_3c = (int *)(**(code **)(*(int *)(local_44 + 0x18) + 0x2c))();
        FUN_00499b80(local_3c + 0x11,local_3c + 0x14,0,DAT_00917570);
        FUN_00499ab0(local_3c + 2,local_3c[5],*local_3c + 0x20,DAT_00917570);
        local_50 = local_3c[9];
        if (local_50 == 1) {
          local_60 = *local_3c;
          local_40 = (int *)local_3c[10];
          if (local_40 == (int *)0x0) {
            FUN_0062e650();
          }
          else {
            local_38 = local_40[3];
            local_34 = local_40[7];
            local_30 = local_40[0xb];
            local_2c = local_40[*local_40 + 2];
            local_28 = local_40[local_40[1] + 6];
            local_24 = local_40[local_40[2] + 10];
          }
          FUN_00499b80(&local_38,&local_2c,local_60 + 0x20,local_54);
        }
        else if (local_50 == 2) {
          local_58 = *local_3c;
          FUN_00499ab0(local_58 + 0xa0,*(undefined4 *)(local_58 + 0xac),local_58 + 0x20,local_54);
        }
        else if (local_50 == 3) {
          FUN_00499840();
        }
      }
    }
    FUN_0046b260(local_70,0);
  }
  FUN_0083e885();
  return;
}

