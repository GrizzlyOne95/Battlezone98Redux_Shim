
void __fastcall FUN_004db800(int param_1)

{
  char cVar1;
  
  if ((*(int *)(param_1 + 0x178) < 0) && (*(int *)(*(int *)(param_1 + 0xf4) + 0x84) == 3)) {
    *(undefined4 *)(param_1 + 0x16c) = DAT_00917560;
    *(undefined4 *)(param_1 + 0x170) = DAT_0091759c;
  }
  else if (*(int *)(param_1 + 0x174) == 0) {
    *(undefined4 *)(param_1 + 0x16c) = DAT_0091755c;
    *(undefined4 *)(param_1 + 0x170) = DAT_00917588;
  }
  else if (DAT_00917b00 == *(int *)(param_1 + 0x174)) {
    *(undefined4 *)(param_1 + 0x16c) = DAT_009175b0;
    *(undefined4 *)(param_1 + 0x170) = DAT_00917598;
  }
  else {
    if ((DAT_00917a70 != 0) &&
       (cVar1 = FUN_005e1310(*(undefined4 *)(param_1 + 0x174)), cVar1 != '\0')) {
      *(undefined4 *)(param_1 + 0x16c) = DAT_00917578;
      *(undefined4 *)(param_1 + 0x170) = DAT_009175a8;
      return;
    }
    *(undefined4 *)(param_1 + 0x16c) = DAT_0091757c;
    *(undefined4 *)(param_1 + 0x170) = DAT_00917590;
  }
  return;
}

