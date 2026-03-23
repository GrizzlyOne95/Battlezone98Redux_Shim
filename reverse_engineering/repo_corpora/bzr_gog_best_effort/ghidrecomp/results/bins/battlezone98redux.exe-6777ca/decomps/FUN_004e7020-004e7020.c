
void __fastcall FUN_004e7020(int param_1)

{
  undefined4 uVar1;
  float *pfVar2;
  float10 fVar3;
  undefined1 local_38 [4];
  int local_34;
  float local_30;
  undefined4 local_2c;
  undefined4 local_28;
  int local_24;
  int local_20;
  int *local_1c;
  int local_18;
  float local_14;
  float local_10;
  float local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_18 = param_1;
  uVar1 = FUN_00462630(*(undefined4 *)(param_1 + 0x14));
  *(undefined4 *)(local_18 + 0x18) = uVar1;
  if (*(int *)(local_18 + 0x18) != 0) {
    local_1c = DAT_00917554;
    local_2c = 0x18;
    pfVar2 = (float *)(**(code **)(*(int *)(*(int *)(local_18 + 0x18) + 0x18) + 0xc))();
    local_14 = *pfVar2;
    local_10 = pfVar2[1];
    local_c = pfVar2[2];
    (**(code **)(*local_1c + 0x24))(local_14,local_c,&local_20,&local_28);
    fVar3 = (float10)FUN_00417910(*(undefined4 *)(local_18 + 0x14c));
    local_30 = (float)fVar3;
    local_14 = local_30 + local_14;
    (**(code **)(*local_1c + 0x24))(local_14,local_c,&local_24,local_38);
    local_34 = local_24 - local_20;
    FUN_0068ad00(DAT_00917580,local_20,local_28,local_34,local_2c,DAT_00917560,0);
  }
  FUN_0083e885();
  return;
}

