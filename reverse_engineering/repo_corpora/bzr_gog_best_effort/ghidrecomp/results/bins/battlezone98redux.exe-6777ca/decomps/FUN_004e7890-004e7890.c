
void FUN_004e7890(void)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  float10 fVar3;
  undefined1 local_7c [12];
  undefined1 local_70 [12];
  undefined1 local_64 [12];
  float local_58;
  int local_54;
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
  fVar3 = (float10)FUN_00822d80();
  local_58 = (float)fVar3;
  if (local_58 <= *(float *)(local_54 + 0x154) + 5.0) {
    uVar1 = FUN_0045c4d0();
    puVar2 = (undefined4 *)FUN_00439de0(local_64,uVar1);
    local_50 = *puVar2;
    local_4c = puVar2[1];
    local_48 = puVar2[2];
    local_20 = local_50;
    local_1c = local_4c;
    local_18 = local_48;
    puVar2 = (undefined4 *)
             (**(code **)(*(int *)(*(int *)(local_54 + 0x18) + 0x18) + 0xc))
                       (local_50,local_4c,local_48);
    puVar2 = (undefined4 *)FUN_004401a0(local_70,*puVar2,puVar2[1],puVar2[2]);
    local_38 = *puVar2;
    local_34 = puVar2[1];
    local_30 = puVar2[2];
    local_2c = local_38;
    local_28 = local_34;
    local_24 = local_30;
    puVar2 = (undefined4 *)FUN_004621a0(local_7c,&local_38);
    local_44 = *puVar2;
    local_40 = puVar2[1];
    local_3c = puVar2[2];
    local_14 = local_44;
    local_10 = local_40;
    local_c = local_3c;
    FUN_00607320(&local_44);
    FUN_00606f70(&local_38);
  }
  else {
    *(undefined4 *)(local_54 + 0xc) = 0xd;
  }
  FUN_0083e885();
  return;
}

