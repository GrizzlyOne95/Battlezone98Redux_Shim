
undefined1 __fastcall FUN_00418f50(int param_1)

{
  undefined1 uVar1;
  
  if ((DAT_008eaad8 == 3) && (*(char *)(param_1 + 0x70) != '\0')) {
    uVar1 = *(undefined1 *)(param_1 + 4);
  }
  else if ((DAT_008eaad8 == 0) ||
          (((DAT_008eaad8 == 2 || (DAT_008eaad8 == 1)) || (DAT_008eaad8 == 7)))) {
    uVar1 = *(undefined1 *)(param_1 + 4);
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}

