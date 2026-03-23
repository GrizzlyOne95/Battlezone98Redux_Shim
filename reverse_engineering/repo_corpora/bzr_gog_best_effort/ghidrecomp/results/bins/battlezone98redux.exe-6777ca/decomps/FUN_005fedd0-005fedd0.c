
void __fastcall FUN_005fedd0(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  uint uVar3;
  float local_14;
  uint local_10;
  float local_c;
  int local_8;
  
  *(undefined4 *)(param_1 + 0xc0) = 0;
  local_8 = param_1;
  if (*(int *)(param_1 + 0x10) != 0) {
    iVar1 = FUN_00417ca0();
    if (iVar1 != 0) {
      uVar2 = FUN_005fed30(*(undefined4 *)(local_8 + 0x10));
      *(undefined4 *)(local_8 + 0xc0) = uVar2;
      FUN_00466be0(*(undefined4 *)(local_8 + 0x10),&local_14,&local_c,local_8 + 0xa4,local_8 + 0xb4)
      ;
      uVar2 = FUN_00605270(local_8 + 0xb8);
      *(undefined4 *)(local_8 + 0xbc) = uVar2;
      local_10 = FUN_00462510();
      if (-1 < *(int *)(local_8 + 0xbc)) {
        local_10 = ~(1 << ((byte)*(undefined4 *)(local_8 + 0xbc) & 0x1f)) & local_10;
      }
      uVar3 = local_10;
      FUN_00417ca0(local_10);
      FUN_004d9880(uVar3);
      goto LAB_005feefc;
    }
  }
  local_14 = 0.0;
  local_c = 10.0;
  *(undefined4 *)(local_8 + 0xa4) = 0x3f000000;
  *(undefined4 *)(local_8 + 0xb4) = 0;
  *(undefined4 *)(local_8 + 0xb8) = 0;
  *(undefined4 *)(local_8 + 0xbc) = 0xffffffff;
LAB_005feefc:
  *(float *)(local_8 + 0xa8) = local_c / *(float *)(local_8 + 0xa4);
  *(float *)(local_8 + 0xac) = *(float *)(local_8 + 0xa4) / local_c;
  *(float *)(local_8 + 0x9c) = local_14 * local_14;
  *(float *)(local_8 + 0xa0) = local_c * local_c;
  *(undefined4 *)(local_8 + 0x10c) = 0x3f800000;
  return;
}

