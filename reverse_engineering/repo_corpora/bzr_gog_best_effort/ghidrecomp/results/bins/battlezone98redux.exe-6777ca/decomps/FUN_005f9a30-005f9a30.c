
bool __fastcall FUN_005f9a30(int param_1)

{
  char cVar1;
  undefined4 uVar2;
  
  uVar2 = FUN_004cf880(*(undefined4 *)(param_1 + 0x28));
  *(undefined4 *)(param_1 + 0x28) = uVar2;
  uVar2 = FUN_004cf880(*(undefined4 *)(param_1 + 0x3c));
  *(undefined4 *)(param_1 + 0x3c) = uVar2;
  FUN_0047b740(*(undefined4 *)(param_1 + 0x18));
  cVar1 = FUN_00435a30();
  return cVar1 != '\0';
}

