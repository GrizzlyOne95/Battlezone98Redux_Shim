
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __fastcall FUN_005c0380(int param_1)

{
  undefined4 *puVar1;
  undefined4 uVar2;
  float *pfVar3;
  int iVar4;
  uint uVar5;
  float10 fVar6;
  undefined1 local_7c [12];
  undefined1 local_70 [12];
  undefined1 local_64 [12];
  undefined4 local_58;
  float local_54;
  int local_50;
  ushort local_4c;
  byte local_49;
  int local_48;
  float local_44;
  float local_40;
  float local_3c;
  float local_38;
  float local_34;
  float local_30;
  undefined4 local_2c;
  undefined4 local_28;
  float local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  float local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_50 = *(int *)(*(int *)(param_1 + 0x10) + 0x230);
  local_48 = param_1;
  puVar1 = (undefined4 *)(**(code **)(*(int *)(*(int *)(param_1 + 0x10) + 0x18) + 0xc))();
  puVar1 = (undefined4 *)
           (**(code **)(*(int *)(*(int *)(local_48 + 0x18) + 0x18) + 0xc))
                     (*puVar1,puVar1[1],puVar1[2]);
  puVar1 = (undefined4 *)FUN_004401a0(local_64,*puVar1,puVar1[1],puVar1[2]);
  local_20 = *puVar1;
  local_1c = puVar1[1];
  local_18 = puVar1[2];
  local_14 = local_20;
  local_10 = local_1c;
  local_c = (float)local_18;
  uVar2 = FUN_0045c4d0();
  puVar1 = (undefined4 *)FUN_00440300(local_70,&local_14,uVar2);
  local_2c = *puVar1;
  local_28 = puVar1[1];
  local_24 = (float)puVar1[2];
  local_14 = local_2c;
  local_10 = local_28;
  local_c = local_24;
  pfVar3 = (float *)FUN_004621a0(local_7c,&local_14);
  local_44 = *pfVar3;
  local_40 = pfVar3[1];
  local_3c = pfVar3[2];
  *(undefined4 *)(local_50 + 0xd4) = 0;
  *(undefined4 *)(local_50 + 0xcc) = 0;
  local_38 = local_44;
  local_34 = local_40;
  local_30 = local_3c;
  fVar6 = (float10)FUN_00447ed0((local_c + 1.0) * 0.001,0xbe800000,0x3e800000);
  *(float *)(local_50 + 0xd0) = (float)fVar6;
  local_54 = local_44 * -5.0;
  iVar4 = FUN_0045c490(0xbf800000,0x3f800000);
  fVar6 = (float10)FUN_00447ed0(local_54 - *(float *)(iVar4 + 0x28));
  *(float *)(local_50 + 0xc4) = (float)fVar6;
  fVar6 = (float10)FUN_00447ed0(*(float *)(local_48 + 0xb0) + local_40,0xbf800000,0x3f800000);
  *(float *)(local_48 + 0xb0) = (float)fVar6;
  *(undefined4 *)(local_50 + 200) = *(undefined4 *)(local_48 + 0xb0);
  if ((0.0 < local_c) && (local_c < 5.0)) {
    _DAT_02a13cf8 = (**(code **)(*(int *)(*(int *)(local_48 + 0x10) + 0x18) + 0x30))();
    _DAT_02a13cfc = (**(code **)(*(int *)(*(int *)(local_48 + 0x10) + 0x18) + 0x30))();
    _DAT_02a13d00 = _DAT_02a13d00 & 0xfff0 | 4;
    uVar5 = FUN_0045c4b0();
    local_4c = (ushort)((uVar5 & 0x30) != 0);
    _DAT_02a13d00 = _DAT_02a13d00 & 0xffef | local_4c << 4;
    local_49 = FUN_004b9830();
    _DAT_02a13d00 = _DAT_02a13d00 & 0xffdf | (local_49 & 1) << 5;
    local_58 = (**(code **)(*(int *)(*(int *)(local_48 + 0x10) + 0x18) + 4))();
    _DAT_02a13d00 = _DAT_02a13d00 & 0xfc3f | ((ushort)local_58 & 0xf) << 6;
    _DAT_02a13d04 = 0x42960000;
    _DAT_02a13d08 = 0;
    _DAT_02a13d0c = 0x3f800000;
    _DAT_02a13d10 = 0;
    (**(code **)(*(int *)(*(int *)(local_48 + 0x18) + 0x18) + 0x38))(&DAT_02a13cf8,&DAT_02a13d08);
  }
  FUN_0083e885();
  return;
}

