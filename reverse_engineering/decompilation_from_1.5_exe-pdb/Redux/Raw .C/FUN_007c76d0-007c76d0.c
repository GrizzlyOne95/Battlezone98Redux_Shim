
undefined1 __fastcall FUN_007c76d0(int *param_1)

{
  undefined1 uVar1;
  int iVar2;
  
  if ((param_1[5] == 0) && (iVar2 = size(), iVar2 == 0)) {
    return (char)param_1[10];
  }
  if (*(char *)((int)param_1 + 0x26) == '\0') {
    *(undefined1 *)((int)param_1 + 0x26) = 1;
    *(undefined1 *)(param_1 + 9) = 0;
    *(undefined1 *)((int)param_1 + 0x25) = 0;
    if (((((char)param_1[9] == '\0') && (iVar2 = size(), iVar2 != 0)) && (DAT_009455de == '\0')) &&
       (DAT_009455df == '\0')) {
      *(undefined1 *)((int)param_1 + 0x27) = 1;
      *(undefined1 *)((int)param_1 + 0x19) = 0;
      FUN_00685580(100);
      iVar2 = FUN_00684ce0(0);
      if ((iVar2 != 0) && (iVar2 = FUN_00685520(), iVar2 == 0)) {
        FUN_006854b0();
        FUN_006854d0();
      }
      (**(code **)(*param_1 + 0x2c))();
    }
    *(undefined1 *)((int)param_1 + 0x25) = 1;
    FUN_0067ca70(0x3dcccccd,0x3dcccccd,0x3dcccccd);
    FUN_00822ed0(1);
    FUN_00681dd0(1);
    FUN_00685580(0x32);
    FUN_007c7070(param_1,0);
    *(undefined1 *)((int)param_1 + 0x26) = 0;
    uVar1 = (undefined1)param_1[10];
  }
  else {
    uVar1 = (undefined1)param_1[10];
  }
  return uVar1;
}

