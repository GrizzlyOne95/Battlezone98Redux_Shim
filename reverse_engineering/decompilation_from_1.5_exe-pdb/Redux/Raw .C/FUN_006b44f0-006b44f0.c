
undefined4 __thiscall FUN_006b44f0(undefined4 param_1,int *param_2,undefined4 param_3)

{
  char cVar1;
  undefined4 uVar2;
  
  cVar1 = FUN_006acd60(param_1);
  FUN_006ac0d0();
  if ((cVar1 == '\0') || (*(char *)(*param_2 + 0x38) != '\0')) {
    if (*(char *)(*param_2 + 0x38) == '\0') {
      *(undefined1 *)(*param_2 + 0x38) = 1;
      FUN_006ac0f0();
      FUN_006c9000(param_3);
      FUN_006acd90(*param_2,0);
    }
    else {
      FUN_006c9000(param_3);
      FUN_006ac0f0();
    }
    uVar2 = 0;
  }
  else {
    *(undefined1 *)(*param_2 + 0x38) = 1;
    FUN_006ac0f0();
    uVar2 = 1;
  }
  return uVar2;
}

