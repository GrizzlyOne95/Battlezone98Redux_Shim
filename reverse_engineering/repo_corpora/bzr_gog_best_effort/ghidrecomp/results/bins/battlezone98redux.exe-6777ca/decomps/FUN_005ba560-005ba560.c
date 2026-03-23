
void FUN_005ba560(void)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  float10 fVar5;
  undefined1 local_334 [64];
  undefined1 local_2f4 [64];
  undefined1 local_2b4 [64];
  undefined1 local_274 [64];
  uint local_234;
  undefined4 local_230;
  undefined4 *local_22c;
  float local_228;
  float local_224;
  undefined4 *local_220;
  int local_21c;
  int local_218;
  int local_214;
  int local_210;
  int local_20c;
  undefined4 local_208 [16];
  undefined4 local_1c8 [16];
  undefined4 local_188 [16];
  undefined4 local_148 [16];
  undefined4 local_108 [16];
  undefined4 local_c8 [16];
  undefined4 local_88 [16];
  undefined4 local_48 [10];
  undefined8 local_20;
  undefined8 local_18;
  undefined8 local_10;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_210 = FUN_00417c70();
  if ((local_210 != 0) &&
     (iVar1 = (**(code **)(*(int *)(local_210 + 0x18) + 0x30))(),
     (*(uint *)(iVar1 + 0x14) & 0x200) == 0)) {
    iVar1 = (**(code **)(*(int *)(local_210 + 0x18) + 0x2c))();
    if (*(int *)(iVar1 + 0xe0) == 0) {
      puVar3 = (undefined4 *)
               FUN_0062e070(local_2f4,*(undefined4 *)(*(int *)(local_210 + 0x230) + 0xfc),0);
      puVar4 = local_88;
      for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
        *puVar4 = *puVar3;
        puVar3 = puVar3 + 1;
        puVar4 = puVar4 + 1;
      }
      puVar3 = local_88;
      puVar4 = local_108;
      for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
        *puVar4 = *puVar3;
        puVar3 = puVar3 + 1;
        puVar4 = puVar4 + 1;
      }
      local_220 = local_108;
    }
    else {
      uVar2 = (**(code **)(*(int *)(local_210 + 0x18) + 0x2c))();
      puVar3 = (undefined4 *)FUN_0067dac0(local_274,uVar2);
      puVar4 = local_1c8;
      for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
        *puVar4 = *puVar3;
        puVar3 = puVar3 + 1;
        puVar4 = puVar4 + 1;
      }
      puVar3 = local_1c8;
      puVar4 = local_148;
      for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
        *puVar4 = *puVar3;
        puVar3 = puVar3 + 1;
        puVar4 = puVar4 + 1;
      }
      local_220 = local_148;
    }
    local_22c = local_220;
    puVar3 = local_220;
    puVar4 = local_48;
    for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
      *puVar4 = *puVar3;
      puVar3 = puVar3 + 1;
      puVar4 = puVar4 + 1;
    }
    puVar3 = (undefined4 *)FUN_0045c4d0();
    puVar4 = (undefined4 *)(local_20c + 0x28);
    for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
      *puVar4 = *puVar3;
      puVar3 = puVar3 + 1;
      puVar4 = puVar4 + 1;
    }
    *(undefined8 *)(local_20c + 0x50) = local_20;
    *(undefined8 *)(local_20c + 0x58) = local_18;
    *(undefined8 *)(local_20c + 0x60) = local_10;
    fVar5 = (float10)FUN_00820570((double)(*(float *)(local_20c + 0x40) *
                                           *(float *)(local_20c + 0x40) +
                                           *(float *)(local_20c + 0x48) *
                                           *(float *)(local_20c + 0x48) + 1.1754944e-38));
    local_224 = (float)fVar5;
    *(undefined4 *)(local_20c + 0x74) = 0;
    *(undefined4 *)(local_20c + 0x78) = 0x3f800000;
    *(undefined4 *)(local_20c + 0x7c) = 0;
    *(float *)(local_20c + 0x80) = local_224 * *(float *)(local_20c + 0x40);
    *(undefined4 *)(local_20c + 0x84) = 0;
    *(float *)(local_20c + 0x88) = local_224 * *(float *)(local_20c + 0x48);
    *(undefined4 *)(local_20c + 0x68) = *(undefined4 *)(local_20c + 0x88);
    *(undefined4 *)(local_20c + 0x6c) = 0;
    *(uint *)(local_20c + 0x70) = *(uint *)(local_20c + 0x80) ^ 0x80000000;
    *(undefined8 *)(local_20c + 0x90) = *(undefined8 *)(local_20c + 0x50);
    *(undefined8 *)(local_20c + 0x98) = *(undefined8 *)(local_20c + 0x58);
    *(undefined8 *)(local_20c + 0xa0) = *(undefined8 *)(local_20c + 0x60);
    if ((((DAT_008eaad8 == 0) || (DAT_008eaad8 == 2)) || (DAT_008eaad8 == 1)) || (DAT_008eaad8 == 7)
       ) {
      fVar5 = (float10)FUN_005ba130();
      local_228 = (float)fVar5;
      puVar3 = (undefined4 *)FUN_0081ec40(local_2b4,-local_228);
      puVar4 = local_188;
      for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
        *puVar4 = *puVar3;
        puVar3 = puVar3 + 1;
        puVar4 = puVar4 + 1;
      }
      puVar3 = local_188;
      puVar4 = local_208;
      for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
        *puVar4 = *puVar3;
        puVar3 = puVar3 + 1;
        puVar4 = puVar4 + 1;
      }
      puVar3 = (undefined4 *)FUN_0081fe60(local_334,local_208,local_20c + 0x28);
      puVar4 = local_c8;
      for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
        *puVar4 = *puVar3;
        puVar3 = puVar3 + 1;
        puVar4 = puVar4 + 1;
      }
      puVar3 = local_c8;
      puVar4 = (undefined4 *)(local_20c + 0x28);
      for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
        *puVar4 = *puVar3;
        puVar3 = puVar3 + 1;
        puVar4 = puVar4 + 1;
      }
      *(undefined4 *)(local_20c + 0xb0) = 0;
      if ((DAT_00978fa8 == 0) || (DAT_00919875 != '\0')) {
        uVar2 = FUN_005bc640();
        *(undefined4 *)(local_20c + 0xac) = uVar2;
      }
      else {
        local_230 = FUN_004da060();
        uVar2 = FUN_005bc640();
        *(undefined4 *)(local_20c + 0xac) = uVar2;
      }
      if (*(int *)(local_20c + 0xac) == 0) {
        uVar2 = FUN_005bcca0();
        *(undefined4 *)(local_20c + 0xa8) = uVar2;
        if (*(int *)(local_20c + 0xa8) != 0) {
          uVar2 = FUN_0045bd80();
          *(undefined4 *)(local_20c + 0xb0) = uVar2;
        }
      }
      else {
        *(undefined4 *)(local_20c + 0xa8) = 0;
        uVar2 = FUN_0045bbe0();
        *(undefined4 *)(local_20c + 0xb0) = uVar2;
      }
      if (*(int *)(local_20c + 0xac) == 0) {
        FUN_004a71e0(*(undefined4 *)(local_20c + 0xb0),*(undefined4 *)(local_20c + 0xa8));
      }
      else {
        FUN_004a7230(*(undefined4 *)(local_20c + 0xb0),*(undefined4 *)(local_20c + 0xac));
      }
    }
    else {
      *(undefined4 *)(local_20c + 0xac) = 0;
      *(undefined4 *)(local_20c + 0xa8) = 0;
    }
    *(undefined4 *)(local_20c + 0xc4) = *(undefined4 *)(local_20c + 0xb4);
    *(undefined4 *)(local_20c + 200) = 0;
    local_21c = FUN_00417ca0();
    if (local_21c != 0) {
      local_234 = FUN_00417f90();
      for (local_214 = 0; local_214 < 5; local_214 = local_214 + 1) {
        if (((1 << ((byte)local_214 & 0x1f) & local_234) != 0) &&
           (local_218 = FUN_00417f60(), *(int *)(local_218 + 0xa8) != 0)) {
          *(undefined4 *)(local_20c + 0xc4) = *(undefined4 *)(local_218 + 0xa8);
          *(undefined4 *)(local_20c + 200) = *(undefined4 *)(*(int *)(local_218 + 8) + 0x6c);
          break;
        }
      }
    }
  }
  FUN_0083e885();
  return;
}

