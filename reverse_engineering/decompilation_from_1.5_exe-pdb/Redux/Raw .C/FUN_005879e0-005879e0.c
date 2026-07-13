
void __thiscall FUN_005879e0(undefined4 param_1,int param_2,int param_3)

{
  char cVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  int *piVar4;
  int iVar5;
  undefined1 local_50 [4];
  undefined1 local_4c [4];
  undefined1 local_48 [4];
  int local_44;
  undefined8 local_40;
  float local_38;
  int local_34;
  float local_30;
  float local_2c;
  undefined8 local_28;
  undefined4 local_20;
  float local_1c;
  int local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_30 = 1e+37;
  local_34 = 0;
  FUN_00422170(param_1);
  puVar2 = (undefined4 *)FID_conflict_begin(local_4c);
  local_20 = *puVar2;
  while( true ) {
    uVar3 = FID_conflict_end(local_48);
    cVar1 = FID_conflict_operator__(uVar3);
    if (cVar1 == '\0') break;
    piVar4 = (int *)FUN_00421ec0();
    local_18 = *piVar4;
    local_44 = (**(code **)(*(int *)(local_18 + 0x18) + 0x30))();
    if ((*(uint *)(local_44 + 0x14) & 1) == 0) {
      iVar5 = (**(code **)(*(int *)(local_18 + 0x18) + 0x2c))();
      if (iVar5 != 0) {
        puVar2 = (undefined4 *)(**(code **)(*(int *)(local_18 + 0x18) + 0xc))();
        local_14 = *puVar2;
        local_10 = puVar2[1];
        local_c = puVar2[2];
        local_28 = FUN_00497780(&local_14,DAT_00917594,&local_38);
        local_40 = local_28;
        iVar5 = FUN_00462400();
        local_1c = local_38 * *(float *)(iVar5 + 0xc) + 5.0;
        local_1c = local_1c * local_1c;
        local_28._0_4_ = (int)local_28 - param_2;
        local_28._4_4_ = local_28._4_4_ - param_3;
        local_2c = (float)(int)local_28 * (float)(int)local_28 +
                   (float)local_28._4_4_ * (float)local_28._4_4_;
        if ((local_2c < local_1c) && (local_2c < local_30)) {
          local_34 = local_18;
          local_30 = local_2c;
        }
      }
    }
    FUN_0046b260(local_50,0);
  }
  FUN_0083e885();
  return;
}

