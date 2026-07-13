
void __fastcall FUN_0041b390(int param_1)

{
  double dVar1;
  int iVar2;
  undefined4 *puVar3;
  float10 fVar4;
  float fVar5;
  float fVar6;
  double dVar7;
  double dVar8;
  undefined8 uVar9;
  undefined4 local_78;
  undefined4 local_74;
  int *local_70;
  int *local_6c;
  int local_68;
  int *local_64;
  float local_60;
  uint local_5c;
  float local_58;
  float local_54;
  float local_50;
  undefined8 local_4c;
  float local_44;
  uint local_40;
  int local_3c;
  undefined8 local_38;
  undefined4 local_30;
  undefined4 local_2c;
  undefined8 local_28;
  undefined4 local_20;
  undefined4 local_1c;
  undefined8 local_18;
  undefined4 local_10;
  undefined4 local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_50 = 1.0;
  local_3c = param_1;
  if (*(int *)(param_1 + 0x14) == 0) {
    iVar2 = FUN_0068f090(*(undefined4 *)(param_1 + 0x6c));
  }
  else {
    iVar2 = *(int *)(param_1 + 0x14);
  }
  local_54 = (float)iVar2;
  if (*(int *)(local_3c + 0x18) == 0) {
    iVar2 = FUN_0068f0c0(*(undefined4 *)(local_3c + 0x6c));
  }
  else {
    iVar2 = *(int *)(local_3c + 0x18);
  }
  local_58 = (float)iVar2;
  local_40 = size();
  if (local_40 != 0) {
    local_60 = (360.0 - *(float *)(local_3c + 0x9c)) * 0.5 * 0.017453292;
    fVar5 = local_58 * 1.65;
    if (local_40 < 3) {
      local_44 = local_58 * 1.65;
    }
    else {
      dVar7 = (double)local_58;
      local_68 = local_40 - 1;
      dVar8 = (double)local_68;
      dVar1 = (double)(&DAT_008a2fd0)[-(local_68 >> 0x1f)];
      fVar4 = (float10)FUN_00417950(local_60);
      local_44 = (float)((dVar7 * 1.65 * (dVar8 + dVar1) * 0.5) / (double)fVar4);
      if (local_54 * 1.5 < local_44) {
        if (local_54 * 1.75 <= local_44) {
          local_50 = (local_54 * 1.75) / local_44;
        }
      }
      else {
        local_50 = (local_54 * 1.5) / local_44;
      }
    }
    local_78 = *(undefined4 *)(local_3c + 0xc);
    local_74 = *(undefined4 *)(local_3c + 0x10);
    local_4c = FUN_00418580(&local_78,local_60,local_44,local_50);
    local_10 = 0;
    local_c = 0;
    local_18 = local_4c;
    puVar3 = (undefined4 *)FUN_004200d0(0);
    local_70 = (int *)*puVar3;
    (**(code **)(*local_70 + 4))(&local_18,0);
    if (1 < local_40) {
      local_40 = local_40 - 1;
      uVar9 = local_4c;
      for (local_5c = 1; local_4c._4_4_ = (int)((ulonglong)uVar9 >> 0x20), local_4c = uVar9,
          local_5c < local_40; local_5c = local_5c + 1) {
        fVar6 = (float)local_4c._4_4_;
        uVar9 = FUN_00418610(&local_78,fVar6 - fVar5,local_44,local_50);
        local_20 = 0;
        local_1c = 0;
        local_10 = 0;
        local_c = 0;
        local_4c = uVar9;
        local_28 = uVar9;
        local_18 = uVar9;
        puVar3 = (undefined4 *)FUN_004200d0(local_5c);
        local_6c = (int *)*puVar3;
        (**(code **)(*local_6c + 4))(&local_18,0);
        uVar9 = local_4c;
      }
      local_38 = FUN_00418580(&local_78,*(float *)(local_3c + 0x9c) * 0.017453292 + local_60,
                              local_44,local_50);
      local_30 = 0;
      local_2c = 0;
      local_10 = 0;
      local_c = 0;
      local_4c = local_38;
      local_18 = local_38;
      puVar3 = (undefined4 *)FUN_004200d0(local_40);
      local_64 = (int *)*puVar3;
      (**(code **)(*local_64 + 4))(&local_18,0);
    }
  }
  FUN_0083e885();
  return;
}

