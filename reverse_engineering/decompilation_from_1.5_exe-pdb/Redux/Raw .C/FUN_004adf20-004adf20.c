
void __fastcall FUN_004adf20(int param_1)

{
  undefined4 *puVar1;
  int iVar2;
  undefined4 uVar3;
  float local_14;
  float local_10;
  float local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  if ((*(int *)(param_1 + 0xec) != 0) && (*(int *)(*(int *)(param_1 + 0xf4) + 0x84) != 4)) {
    uVar3 = *(undefined4 *)(param_1 + 0xec);
    *(undefined4 *)(param_1 + 0xec) = 0;
    if (*(int *)(param_1 + 0xfc) != 0) {
      puVar1 = *(undefined4 **)(param_1 + 0xfc);
      if (puVar1 != (undefined4 *)0x0) {
        (**(code **)*puVar1)(1,puVar1,uVar3);
      }
      *(undefined4 *)(param_1 + 0xfc) = 0;
    }
    memset((void *)(*(int *)(param_1 + 0x230) + 0xc4),0,0x2c);
    if (*(int *)(param_1 + 0x1a0) != 0) {
      FUN_004a7800();
    }
    *(undefined4 *)(param_1 + 0x298) = 0;
    iVar2 = *(int *)(param_1 + 0xf4);
    local_14 = *(float *)(iVar2 + 0x38) * 10.0 + *(float *)(param_1 + 300) +
               *(float *)(iVar2 + 0x2c) * 5.0;
    local_10 = *(float *)(iVar2 + 0x3c) * 10.0 + *(float *)(param_1 + 0x130) +
               *(float *)(iVar2 + 0x30) * 5.0;
    local_c = *(float *)(iVar2 + 0x40) * 10.0 + *(float *)(param_1 + 0x134) +
              *(float *)(iVar2 + 0x34) * 5.0;
    iVar2 = FUN_004adb00(uVar3,&local_14);
    uVar3 = FUN_00462380();
    *(undefined4 *)(iVar2 + 0x22c) = uVar3;
    FUN_004db4f0(0);
    uVar3 = (**(code **)(*(int *)(iVar2 + 0x18) + 0x30))(0);
    FUN_004376c0("jump.wav",uVar3);
  }
  FUN_0083e885();
  return;
}

