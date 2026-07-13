
uint __fastcall FUN_00528ea0(int param_1)

{
  char cVar1;
  uint uVar2;
  undefined4 uVar3;
  int local_10;
  
  if (DAT_009173b7 == '\0') {
    for (local_10 = 0; local_10 < 200; local_10 = local_10 + 1) {
      uVar3 = FUN_004cf880(*(undefined4 *)(param_1 + 0x1f8 + local_10 * 4));
      *(undefined4 *)(param_1 + 0x1f8 + local_10 * 4) = uVar3;
    }
    cVar1 = FUN_0045d720();
    uVar2 = (uint)(cVar1 != '\0');
  }
  else {
    uVar2 = FUN_0045d720();
  }
  return uVar2;
}

