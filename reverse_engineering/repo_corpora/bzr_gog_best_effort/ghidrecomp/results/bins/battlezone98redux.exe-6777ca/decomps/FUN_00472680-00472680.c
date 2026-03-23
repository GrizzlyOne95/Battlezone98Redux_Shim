
undefined1 __fastcall FUN_00472680(int param_1)

{
  char cVar1;
  int iVar2;
  int iVar3;
  
  iVar2 = FUN_004e1b90(*(undefined4 *)(param_1 + 0x174),*(undefined4 *)(param_1 + 0x370));
  if (((*(int *)(param_1 + 0x228) == 2) && (cVar1 = FUN_004723d0(), cVar1 == '\0')) &&
     (iVar3 = FUN_005e10b0(), iVar2 <= iVar3)) {
    return 1;
  }
  return 0;
}

