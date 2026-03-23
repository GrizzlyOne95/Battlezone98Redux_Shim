
void __thiscall FUN_00660080(int param_1,undefined4 param_2)

{
  bool bVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  float10 fVar4;
  float local_24;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  bVar1 = false;
  local_24 = 1.0;
  switch(*(undefined4 *)(param_1 + 0x244)) {
  case 0:
    break;
  case 1:
    bVar1 = true;
    fVar4 = (float10)FUN_00822d80();
    if ((float)fVar4 < *(float *)(param_1 + 0x240) || (float)fVar4 == *(float *)(param_1 + 0x240)) {
      fVar4 = (float10)FUN_00822d80();
      local_24 = (*(float *)(param_1 + 0x240) - (float)fVar4) / *(float *)(param_1 + 0x238);
    }
    else {
      *(undefined4 *)(param_1 + 0x244) = 2;
      local_24 = 0.0;
    }
    break;
  case 2:
    bVar1 = true;
    local_24 = 0.0;
    break;
  case 3:
    fVar4 = (float10)FUN_00822d80();
    bVar1 = (float)fVar4 < *(float *)(param_1 + 0x240) ||
            (float)fVar4 == *(float *)(param_1 + 0x240);
    if (bVar1) {
      fVar4 = (float10)FUN_00822d80();
      local_24 = ((float)fVar4 - *(float *)(param_1 + 0x23c)) / *(float *)(param_1 + 0x238);
    }
    else {
      *(undefined4 *)(param_1 + 0x244) = 0;
    }
    break;
  default:
    FUN_007d6a70("Invalid portalState");
  }
  if (bVar1) {
    puVar2 = (undefined4 *)FUN_00462400();
    local_18 = *puVar2;
    local_14 = puVar2[1];
    local_10 = puVar2[2];
    local_c = puVar2[3];
    uVar3 = FUN_0045c4d0();
    FUN_00820180(&local_18,&local_18,1,uVar3);
    fVar4 = (float10)FUN_0044fb20(local_24,0);
    fVar4 = (float10)FUN_0047b6f0((float)fVar4,0x3f800000);
    FUN_00660960(&local_18,(float)fVar4,*(undefined1 *)(param_1 + 0x248));
  }
  FUN_0047fcb0(param_2);
  FUN_0083e885();
  return;
}

