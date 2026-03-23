
void __fastcall FUN_005b6ee0(int param_1)

{
  char cVar1;
  int iVar2;
  float10 fVar3;
  
  iVar2 = FUN_00463120(*(undefined4 *)(param_1 + 0x2c));
  if ((iVar2 != 0) && (cVar1 = FUN_005b5100(), cVar1 != '\0')) {
    *(undefined4 *)(param_1 + 0x4c) = 3;
    return;
  }
  fVar3 = (float10)FUN_00822da0();
  if (*(float *)(param_1 + 0x5c) <= (float)fVar3 && (float)fVar3 != *(float *)(param_1 + 0x5c)) {
    *(undefined4 *)(param_1 + 0x4c) = 1;
  }
  *(undefined4 *)(*(int *)(*(int *)(param_1 + 0x2c) + 0x230) + 0xc4) = 0;
  *(undefined4 *)(*(int *)(*(int *)(param_1 + 0x2c) + 0x230) + 0xd4) = 0;
  *(undefined4 *)(*(int *)(*(int *)(param_1 + 0x2c) + 0x230) + 0xd0) = 0;
  return;
}

