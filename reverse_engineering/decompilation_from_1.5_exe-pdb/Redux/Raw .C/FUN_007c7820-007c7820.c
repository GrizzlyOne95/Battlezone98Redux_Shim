
undefined1 __fastcall FUN_007c7820(int *param_1)

{
  char cVar1;
  undefined1 uVar2;
  int iVar3;
  
  if (*(char *)((int)param_1 + 0x26) == '\0') {
    *(undefined1 *)((int)param_1 + 0x26) = 1;
    *(undefined1 *)((int)param_1 + 0x25) = 0;
    if ((char)param_1[9] == '\0') {
      iVar3 = size();
      if (((iVar3 != 0) && (DAT_009455de == '\0')) && (DAT_009455df == '\0')) {
        (**(code **)(*param_1 + 0x2c))();
      }
    }
    iVar3 = FUN_00684ce0(0);
    if (iVar3 != 0) {
      FUN_0067ca70(0x3dcccccd,0x3dcccccd,0x3dcccccd);
      if (((char)param_1[10] == '\0') && (*(char *)((int)param_1 + 0x27) != '\0')) {
        cVar1 = FUN_0041fc90();
        if (cVar1 == '\0') {
          FUN_007c7070(param_1,0);
        }
      }
    }
    *(undefined1 *)((int)param_1 + 0x25) = 1;
    FUN_00822ed0(1);
    FUN_00681dd0(1);
    FUN_00685580(0x32);
    *(undefined1 *)((int)param_1 + 0x26) = 0;
    uVar2 = (undefined1)param_1[10];
  }
  else {
    uVar2 = 0;
  }
  return uVar2;
}

