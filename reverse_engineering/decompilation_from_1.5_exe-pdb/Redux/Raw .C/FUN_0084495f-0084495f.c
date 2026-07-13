
uint __fastcall FUN_0084495f(int param_1,uint param_2)

{
  int iVar1;
  uint uVar2;
  
  uVar2 = param_1 >> 0x1f;
  if (uVar2 == param_2) {
    return uVar2;
  }
  if ((int)param_2 < 0) {
    uVar2 = FUN_008448ce();
    return uVar2;
  }
  if (param_2 == 0) {
    return uVar2;
  }
  iVar1 = 0x1f;
  if (param_2 != 0) {
    for (; param_2 >> iVar1 == 0; iVar1 = iVar1 + -1) {
    }
  }
  return 0x20 - iVar1;
}

