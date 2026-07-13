
bool __fastcall FUN_00478140(int param_1)

{
  char cVar1;
  undefined4 uVar2;
  
  uVar2 = FUN_004cf880(*(undefined4 *)(param_1 + 0x13c));
  *(undefined4 *)(param_1 + 0x13c) = uVar2;
  cVar1 = FUN_005ff8a0();
  if (*(int *)(param_1 + 0x104) == 0) {
    *(undefined4 *)(param_1 + 8) = 0xd;
    *(undefined4 *)(param_1 + 0xc) = 0xd;
  }
  return cVar1 != '\0';
}

