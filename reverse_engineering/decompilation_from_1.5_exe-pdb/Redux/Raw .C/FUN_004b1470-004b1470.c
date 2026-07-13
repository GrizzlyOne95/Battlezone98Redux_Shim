
void __fastcall FUN_004b1470(int param_1)

{
  int iVar1;
  undefined4 *puVar2;
  float10 fVar3;
  undefined1 local_60 [12];
  undefined1 local_54 [12];
  float local_48;
  float local_44;
  int local_40;
  int local_3c;
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
  local_3c = param_1;
  puVar2 = (undefined4 *)(**(code **)(*(int *)(*(int *)(param_1 + 0x10) + 0x18) + 0xc))();
  puVar2 = (undefined4 *)
           FUN_004401a0(local_54,*(undefined4 *)(local_3c + 0x28),*(undefined4 *)(local_3c + 0x2c),
                        *(undefined4 *)(local_3c + 0x30),*puVar2,puVar2[1],puVar2[2]);
  local_38 = *puVar2;
  local_34 = puVar2[1];
  local_30 = puVar2[2];
  local_2c = local_38;
  local_28 = local_34;
  local_24 = local_30;
  fVar3 = (float10)FUN_004428b0(&local_38,&local_38);
  local_44 = (float)fVar3;
  if (25.0 <= local_44) {
    fVar3 = (float10)FUN_00820570((double)local_44,local_38,local_34,local_30);
    local_48 = (float)fVar3;
    puVar2 = (undefined4 *)FUN_004462d0(local_60,local_48);
    local_20 = *puVar2;
    local_1c = puVar2[1];
    local_18 = puVar2[2];
    local_14 = local_20;
    local_10 = local_1c;
    local_c = local_18;
  }
  else {
    puVar2 = (undefined4 *)FUN_00462490();
    local_14 = *puVar2;
    local_10 = puVar2[1];
    local_c = puVar2[2];
  }
  FUN_00465320(*(undefined4 *)(local_3c + 0x10),*(undefined4 *)(local_3c + 0x80),0x42200000,
               *(undefined4 *)(local_3c + 0x28),*(undefined4 *)(local_3c + 0x2c),
               *(undefined4 *)(local_3c + 0x30),&local_38,0);
  FUN_004675f0();
  FUN_00607320(&local_14);
  FUN_00606f70(&local_38);
  iVar1 = *(int *)(*(int *)(local_3c + 0x10) + 0x230);
  local_40 = iVar1 + 0xc4;
  if (*(float *)(iVar1 + 0xd0) == 1.0) {
    *(undefined4 *)(iVar1 + 0xd4) = 1;
  }
  FUN_0083e885();
  return;
}

