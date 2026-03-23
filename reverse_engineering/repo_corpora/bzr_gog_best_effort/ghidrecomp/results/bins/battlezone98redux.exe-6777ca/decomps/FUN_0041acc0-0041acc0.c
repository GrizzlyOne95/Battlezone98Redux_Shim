
undefined1 __fastcall FUN_0041acc0(int param_1)

{
  char cVar1;
  undefined1 uVar2;
  
  if ((((DAT_008eaad8 == 0) || (DAT_008eaad8 == 2)) || (DAT_008eaad8 == 1)) ||
     ((DAT_008eaad8 == 7 || ((DAT_008eaad8 == 3 && (*(char *)(param_1 + 0x70) != '\0')))))) {
    if ((*(int *)(param_1 + 0x94) != 0) && (cVar1 = FUN_00418d20(), cVar1 == '\0')) {
      return 0;
    }
    uVar2 = *(undefined1 *)(param_1 + 4);
  }
  else {
    uVar2 = 0;
  }
  return uVar2;
}

