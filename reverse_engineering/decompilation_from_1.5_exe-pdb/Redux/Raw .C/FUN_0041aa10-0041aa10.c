
void __fastcall FUN_0041aa10(int *param_1)

{
  char cVar1;
  int iVar2;
  
  cVar1 = FUN_004187f0();
  if (cVar1 == '\0') {
    param_1[0x15] = 0;
  }
  cVar1 = FUN_004187f0();
  if (cVar1 == '\0') {
    param_1[0x16] = 0;
  }
  if (*(char *)((int)param_1 + 0x5d) != '\0') {
    cVar1 = (**(code **)(*param_1 + 0x14))();
    if (cVar1 != '\0') {
      if ((char)param_1[0xf] == '\0') {
        *(undefined1 *)((int)param_1 + 0x5d) = 0;
      }
      iVar2 = FUN_004187d0();
      if (iVar2 != 0) {
        iVar2 = FUN_00418c30(param_1[0x13]);
        param_1[0x15] = iVar2;
      }
      iVar2 = FUN_004187d0();
      if (iVar2 != 0) {
        iVar2 = FUN_00418c30(param_1[0x14]);
        param_1[0x16] = iVar2;
      }
    }
  }
  FUN_00418c80(param_1[0x15]);
  FUN_00418c80(param_1[0x16]);
  return;
}

