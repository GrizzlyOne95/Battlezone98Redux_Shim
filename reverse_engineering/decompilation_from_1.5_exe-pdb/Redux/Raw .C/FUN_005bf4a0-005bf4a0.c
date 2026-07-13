
undefined1 __fastcall FUN_005bf4a0(int param_1)

{
  undefined1 uVar1;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  
  uVar1 = FUN_004a82e0();
  if ((*(int *)(param_1 + 0x228) == 1) || (*(int *)(param_1 + 0x228) == 2)) {
    local_10 = *(undefined4 *)(*(int *)(param_1 + 0xf8) + 0x5f0);
  }
  else {
    local_10 = *(undefined4 *)(*(int *)(param_1 + 0xf8) + 0x34c);
  }
  *(undefined4 *)(param_1 + 0x300) = local_10;
  if (*(int *)(param_1 + 0x228) == 2) {
    local_14 = 3;
  }
  else {
    local_14 = 0;
  }
  *(undefined4 *)(param_1 + 0x234) = local_14;
  if (*(int *)(param_1 + 0x228) == 2) {
    local_18 = *(uint *)(*(int *)(param_1 + 0xf4) + 0x14) | 1;
  }
  else {
    local_18 = *(uint *)(*(int *)(param_1 + 0xf4) + 0x14) & 0xfffffffe;
  }
  *(uint *)(*(int *)(param_1 + 0xf4) + 0x14) = local_18;
  if (*(int *)(param_1 + 0x228) == 2) {
    local_1c = *(uint *)(*(int *)(param_1 + 0x230) + 0x114) | 4;
  }
  else {
    local_1c = *(uint *)(*(int *)(param_1 + 0x230) + 0x114) & 0xfffffffb;
  }
  *(uint *)(*(int *)(param_1 + 0x230) + 0x114) = local_1c;
  return uVar1;
}

