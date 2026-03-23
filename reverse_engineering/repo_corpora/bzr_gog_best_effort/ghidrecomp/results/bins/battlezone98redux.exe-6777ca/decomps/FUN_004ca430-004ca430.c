
void __thiscall FUN_004ca430(int param_1,float param_2)

{
  char cVar1;
  undefined4 uVar2;
  int iVar3;
  undefined4 *puVar4;
  float *pfVar5;
  float10 fVar6;
  undefined1 local_b0 [44];
  undefined1 local_84 [12];
  float local_78;
  float local_74;
  float local_70;
  float local_6c;
  float local_68;
  float local_64;
  undefined4 *local_60;
  float local_5c;
  float local_58;
  float local_54;
  float local_50;
  float local_4c;
  float local_48;
  float local_44;
  int local_40;
  float local_3c;
  float local_38;
  int local_34;
  int local_30;
  float local_2c;
  undefined4 local_28;
  float local_24;
  float local_20;
  float local_1c;
  float local_18;
  float local_14;
  float local_10;
  float local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  *(float *)(param_1 + 0x14) =
       param_2 * *(float *)(*(int *)(param_1 + 8) + 0x38) + *(float *)(param_1 + 0x14);
  if (*(float *)(param_1 + 0x18) <= *(float *)(param_1 + 0x14)) {
    *(uint *)(*(int *)(param_1 + 0xc) + 0x14) = *(uint *)(*(int *)(param_1 + 0xc) + 0x14) | 0x200;
  }
  local_30 = param_1;
  if (0.0 < *(float *)(param_1 + 0x2c)) {
    local_44 = *(float *)(*(int *)(param_1 + 8) + 0x50) * *(float *)(*(int *)(param_1 + 8) + 0x50);
    local_4c = *(float *)(*(int *)(param_1 + 8) + 0x3c) * *(float *)(*(int *)(param_1 + 8) + 0x3c);
    iVar3 = *(int *)(param_1 + 0xc);
    local_2c = *(float *)(iVar3 + 0xa0);
    local_28 = *(undefined4 *)(iVar3 + 0xa4);
    local_24 = *(float *)(iVar3 + 0xa8);
    FUN_00820180();
    FUN_005b28e0((double)local_2c,(double)local_24,(double)*(float *)(*(int *)(local_30 + 8) + 0x50)
                 ,local_b0);
    while (cVar1 = FUN_00462710(&local_60), cVar1 != '\0') {
      local_40 = FUN_004da060(*local_60);
      if (local_40 != 0) {
        uVar2 = (**(code **)(*(int *)(local_40 + 0x18) + 0x30))();
        iVar3 = FUN_0062e000(uVar2);
        if (iVar3 != 0) {
          puVar4 = (undefined4 *)
                   (**(code **)(*(int *)(local_40 + 0x18) + 0xc))(local_2c,local_28,local_24);
          pfVar5 = (float *)FUN_004401a0(local_84,*puVar4,puVar4[1]);
          local_20 = *pfVar5;
          local_1c = pfVar5[1];
          local_18 = pfVar5[2];
          local_48 = local_20 * local_20 + local_1c * local_1c + local_18 * local_18;
          local_14 = local_20;
          local_10 = local_1c;
          local_c = local_18;
          if (local_48 < local_44) {
            if (local_4c <= local_48) {
              local_54 = (param_2 * *(float *)(local_30 + 0x2c) * (local_44 - local_48)) /
                         (local_44 - local_4c);
            }
            else {
              local_54 = param_2 * *(float *)(local_30 + 0x2c);
            }
            local_3c = local_54;
            local_68 = 2.0;
            fVar6 = (float10)FUN_00822d80();
            local_58 = (float)fVar6;
            local_38 = local_58 * local_68;
            local_34 = FUN_0045c490();
            fVar6 = (float10)FUN_00822970(local_38 + 8.53);
            local_70 = (float)fVar6;
            *(float *)(local_34 + 0x24) = local_70 * local_3c * 2.0 + *(float *)(local_34 + 0x24);
            fVar6 = (float10)FUN_00822970(local_38 + 17.67);
            local_78 = (float)fVar6;
            *(float *)(local_34 + 0x28) = local_78 * local_3c * 1.0 + *(float *)(local_34 + 0x28);
            fVar6 = (float10)FUN_00822970(local_38 + 5.19);
            local_64 = (float)fVar6;
            *(float *)(local_34 + 0x2c) = local_64 * local_3c * 2.0 + *(float *)(local_34 + 0x2c);
            fVar6 = (float10)FUN_00822970(local_38);
            local_74 = (float)fVar6;
            *(float *)(local_34 + 0x18) = local_74 * local_3c * 5.0 + *(float *)(local_34 + 0x18);
            fVar6 = (float10)FUN_00822970(local_38 + 2.27);
            local_6c = (float)fVar6;
            *(float *)(local_34 + 0x1c) = local_6c * local_3c * 2.0 + *(float *)(local_34 + 0x1c);
            fVar6 = (float10)FUN_00822970(local_38 + 23.41);
            local_5c = (float)fVar6;
            *(float *)(local_34 + 0x20) = local_5c * local_3c * 5.0 + *(float *)(local_34 + 0x20);
            fVar6 = (float10)FUN_0045c420(*(undefined4 *)(local_34 + 0x18),
                                          *(undefined4 *)(local_34 + 0x1c),
                                          *(undefined4 *)(local_34 + 0x20));
            *(float *)(local_34 + 8) = (float)fVar6;
            if (*(float *)(local_34 + 8) <= 0.0) {
              local_50 = 1e+30;
            }
            else {
              local_50 = 1.0 / *(float *)(local_34 + 8);
            }
            *(float *)(local_34 + 0xc) = local_50;
          }
        }
      }
    }
    *(float *)(local_30 + 0x2c) =
         *(float *)(local_30 + 0x2c) - param_2 * *(float *)(local_30 + 0x30);
  }
  FUN_0083e885();
  return;
}

