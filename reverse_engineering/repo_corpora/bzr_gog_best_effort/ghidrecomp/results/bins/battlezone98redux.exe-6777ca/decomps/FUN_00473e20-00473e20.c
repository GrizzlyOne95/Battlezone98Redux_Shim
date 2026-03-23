
bool __fastcall FUN_00473e20(int param_1)

{
  char cVar1;
  undefined4 uVar2;
  
  uVar2 = FUN_004cf880(*(undefined4 *)(param_1 + 0x24));
  *(undefined4 *)(param_1 + 0x24) = uVar2;
  cVar1 = FUN_00435a30();
  return cVar1 != '\0';
}

