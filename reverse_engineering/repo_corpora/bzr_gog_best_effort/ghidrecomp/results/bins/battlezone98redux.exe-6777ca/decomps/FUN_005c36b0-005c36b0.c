
bool __fastcall FUN_005c36b0(int param_1)

{
  char cVar1;
  undefined4 uVar2;
  float10 fVar3;
  
  uVar2 = FUN_004cf880(*(undefined4 *)(param_1 + 0x24));
  *(undefined4 *)(param_1 + 0x24) = uVar2;
  cVar1 = FUN_00435a30();
  FUN_005c3fd0();
  if (*(int *)(param_1 + 0x1c) == 4) {
    fVar3 = (float10)FUN_00822d80();
    *(float *)(param_1 + 0x44) = (float)fVar3 + 10.0;
  }
  return cVar1 != '\0';
}

