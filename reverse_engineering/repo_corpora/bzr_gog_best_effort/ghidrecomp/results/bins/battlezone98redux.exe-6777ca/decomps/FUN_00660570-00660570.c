
void __thiscall FUN_00660570(int param_1,undefined1 param_2)

{
  float fVar1;
  int iVar2;
  float10 fVar3;
  float10 fVar4;
  undefined1 local_50 [16];
  undefined4 local_40;
  undefined1 local_24 [4];
  undefined4 local_20;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  *(undefined1 *)(param_1 + 0x248) = param_2;
  if ((*(int *)(param_1 + 0x244) != 2) && (*(int *)(param_1 + 0x244) != 1)) {
    if (*(int *)(param_1 + 0x244) == 3) {
      fVar3 = (float10)FUN_00822d80();
      fVar1 = *(float *)(param_1 + 0x240);
      fVar4 = (float10)FUN_00822d80();
      *(float *)(param_1 + 0x23c) = (float)fVar4 - (fVar1 - (float)fVar3);
      *(float *)(param_1 + 0x240) = *(float *)(param_1 + 0x23c) + *(float *)(param_1 + 0x238);
      *(undefined4 *)(param_1 + 0x244) = 1;
    }
    else {
      fVar3 = (float10)FUN_00822d80();
      *(float *)(param_1 + 0x23c) = (float)fVar3;
      *(float *)(param_1 + 0x240) = *(float *)(param_1 + 0x23c) + *(float *)(param_1 + 0x238);
      *(undefined4 *)(param_1 + 0x244) = 1;
      iVar2 = *(int *)(param_1 + 0xf8);
      if (*(char *)(iVar2 + 0x164) != '\0') {
        FUN_0043a990(local_50);
        local_40 = 0x3000;
        FUN_0043a9e0(local_24);
        local_20 = 0x32;
        FUN_0043aa30(iVar2 + 0x164,*(undefined4 *)(param_1 + 0xf4),local_50,local_24);
      }
    }
  }
  FUN_0083e885();
  return;
}

