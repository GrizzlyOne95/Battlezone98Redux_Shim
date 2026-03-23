
void __fastcall FUN_007a27a0(int param_1)

{
  char cVar1;
  int iVar2;
  
  FUN_007d37f0();
  *(int *)(param_1 + 0x380) = *(int *)(param_1 + 0x380) + 1;
  if ((*(int *)(param_1 + 0x380) == 3) && (*(char *)(param_1 + 0x1ff) == '\x01')) {
    if (*(char *)(param_1 + 0x1fd) == '\0') {
      iVar2 = FUN_006cc050();
      if (iVar2 == 4) {
        FUN_00740a90(0);
      }
      FUN_00741990(param_1 + 0x230,param_1 + 0x218);
      FUN_007c7930(0xf);
    }
    else {
      cVar1 = FUN_007d05f0();
      (**(code **)(**(int **)(param_1 + 0x1c4) + 0x18))
                (cVar1 == '\0',param_1 + 0x218,param_1 + 0x200);
      FUN_007d04a0();
      FUN_007c7930(0xf);
    }
  }
  iVar2 = FUN_00764870();
  if (iVar2 == 0) {
    FUN_0079dd60();
  }
  return;
}

