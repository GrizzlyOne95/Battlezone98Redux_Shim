
void FUN_00609d10(void)

{
  char cVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  undefined1 local_2a0 [152];
  undefined1 local_208 [44];
  undefined4 *local_1dc;
  int local_1d8;
  undefined4 *local_1d4;
  int local_1d0;
  undefined4 *local_1cc;
  float local_1c8;
  float local_1c4;
  int local_1c0;
  int local_1bc;
  int local_1b8;
  undefined4 local_1b4 [16];
  undefined4 local_174 [16];
  undefined4 local_134 [16];
  undefined4 local_f4 [16];
  undefined1 local_b4 [24];
  undefined4 local_9c [6];
  float local_84;
  float local_7c;
  double local_74;
  double local_64;
  undefined4 local_5c;
  undefined4 local_58;
  undefined4 local_54;
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
  local_1d8 = FUN_00417ca0();
  if (local_1d8 == 0) {
    *(undefined4 *)(local_1b8 + 0x78) = 0;
    local_44 = 0;
    local_40 = 0;
    local_3c = 0;
    *(undefined4 *)(local_1b8 + 0x7c) = 0;
    *(undefined4 *)(local_1b8 + 0x80) = 0;
    *(undefined4 *)(local_1b8 + 0x84) = 0;
    *(undefined4 *)(local_1b8 + 0x88) = *(undefined4 *)(local_1b8 + 0x7c);
    *(undefined4 *)(local_1b8 + 0x8c) = *(undefined4 *)(local_1b8 + 0x80);
    *(undefined4 *)(local_1b8 + 0x90) = *(undefined4 *)(local_1b8 + 0x84);
  }
  else {
    iVar2 = (**(code **)(*(int *)(*(int *)(local_1b8 + 0xc) + 0x18) + 0x2c))();
    if (*(int *)(iVar2 + 0xe0) == 0) {
      puVar3 = (undefined4 *)
               FUN_0062e070(local_2a0,
                            *(undefined4 *)(*(int *)(*(int *)(local_1b8 + 0xc) + 0x230) + 0xfc),0);
      puVar4 = local_f4;
      for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
        *puVar4 = *puVar3;
        puVar3 = puVar3 + 1;
        puVar4 = puVar4 + 1;
      }
      puVar3 = local_f4;
      puVar4 = local_134;
      for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
        *puVar4 = *puVar3;
        puVar3 = puVar3 + 1;
        puVar4 = puVar4 + 1;
      }
      local_1cc = local_134;
    }
    else {
      (**(code **)(*(int *)(*(int *)(local_1b8 + 0xc) + 0x18) + 0x2c))();
      puVar3 = (undefined4 *)FUN_0067dac0();
      puVar4 = local_1b4;
      for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
        *puVar4 = *puVar3;
        puVar3 = puVar3 + 1;
        puVar4 = puVar4 + 1;
      }
      puVar3 = local_1b4;
      puVar4 = local_174;
      for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
        *puVar4 = *puVar3;
        puVar3 = puVar3 + 1;
        puVar4 = puVar4 + 1;
      }
      local_1cc = local_174;
    }
    local_1d4 = local_1cc;
    puVar3 = local_1cc;
    puVar4 = local_9c;
    for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
      *puVar4 = *puVar3;
      puVar3 = puVar3 + 1;
      puVar4 = puVar4 + 1;
    }
    puVar3 = (undefined4 *)FUN_00447f60();
    local_5c = *puVar3;
    local_58 = puVar3[1];
    local_54 = puVar3[2];
    local_50 = puVar3[3];
    local_4c = puVar3[4];
    local_48 = puVar3[5];
    *(undefined4 *)(local_1b8 + 0x98) = local_5c;
    *(undefined4 *)(local_1b8 + 0x9c) = local_58;
    *(undefined4 *)(local_1b8 + 0xa0) = local_54;
    *(undefined4 *)(local_1b8 + 0xa4) = local_50;
    *(undefined4 *)(local_1b8 + 0xa8) = local_4c;
    *(undefined4 *)(local_1b8 + 0xac) = local_48;
    puVar3 = (undefined4 *)FUN_00609750(local_b4);
    *(undefined4 *)(local_1b8 + 0xb0) = *puVar3;
    *(undefined4 *)(local_1b8 + 0xb4) = puVar3[1];
    *(undefined4 *)(local_1b8 + 0xb8) = puVar3[2];
    *(undefined4 *)(local_1b8 + 0xbc) = puVar3[3];
    *(undefined4 *)(local_1b8 + 0xc0) = puVar3[4];
    *(undefined4 *)(local_1b8 + 0xc4) = puVar3[5];
    local_1c4 = 0.0;
    local_1bc = 0;
    local_20 = 0;
    local_1c = 0;
    local_18 = 0;
    local_14 = 0;
    local_10 = 0;
    local_c = 0;
    local_1c0 = FUN_00462610();
    if ((local_1c0 != 0) &&
       (cVar1 = FUN_00609980(&local_1c8,&local_2c,&local_38,local_1c0,local_1bc,local_1c4,
                             local_1b8 + 0xb0,local_1c0), cVar1 != '\0')) {
      local_1c4 = local_1c8 + 2.0;
      local_1bc = local_1c0;
      local_20 = local_2c;
      local_1c = local_28;
      local_18 = local_24;
      local_14 = local_38;
      local_10 = local_34;
      local_c = local_30;
    }
    if (local_1c4 == 0.0) {
      FUN_005b28e0((double)(local_84 * *(float *)(local_1b8 + 0x74) * 0.5) + local_74,
                   (double)(local_7c * *(float *)(local_1b8 + 0x74) * 0.5) + local_64,
                   (double)(*(float *)(local_1b8 + 0x74) * 0.5),local_208);
      while (cVar1 = FUN_00462710(&local_1dc), cVar1 != '\0') {
        local_1d0 = FUN_004da060(*local_1dc);
        cVar1 = FUN_00609980(&local_1c8,&local_2c,&local_38,local_1d0,local_1bc,local_1c4,
                             local_1b8 + 0xb0,local_1c0);
        if (cVar1 != '\0') {
          local_1c4 = local_1c8;
          local_1bc = local_1d0;
          local_20 = local_2c;
          local_1c = local_28;
          local_18 = local_24;
          local_14 = local_38;
          local_10 = local_34;
          local_c = local_30;
        }
      }
    }
    *(int *)(local_1b8 + 0x78) = local_1bc;
    *(undefined4 *)(local_1b8 + 0x7c) = local_20;
    *(undefined4 *)(local_1b8 + 0x80) = local_1c;
    *(undefined4 *)(local_1b8 + 0x84) = local_18;
    *(undefined4 *)(local_1b8 + 0x88) = local_14;
    *(undefined4 *)(local_1b8 + 0x8c) = local_10;
    *(undefined4 *)(local_1b8 + 0x90) = local_c;
  }
  FUN_0083e885();
  return;
}

