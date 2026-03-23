
undefined4 __fastcall FUN_007c75e0(int param_1)

{
  char cVar1;
  int iVar2;
  undefined1 local_6;
  char local_5;
  
  FUN_0061a000();
  local_5 = '\0';
  while( true ) {
    if (local_5 == '\0') {
      local_5 = FUN_007c7450();
    }
    cVar1 = FUN_007c7570();
    if ((*(char *)(param_1 + 0x18) == '\0') && (cVar1 == '\0')) {
      local_6 = 1;
    }
    else {
      local_6 = 0;
    }
    cVar1 = FUN_007c7070(param_1,local_6);
    if (cVar1 != '\0') break;
    if ((((*(char *)(param_1 + 0x24) != '\0') || (iVar2 = size(), iVar2 == 0)) ||
        (DAT_009455de != '\0')) ||
       (((DAT_009455df != '\0' || (DAT_02cecf4c != 0)) || (iVar2 = FUN_00434160(), iVar2 == 9)))) {
      Ogre::Viewport::setVisibilityMask(*(Viewport **)(DAT_00920ea0 + 0x1c),1);
      FUN_0061a080();
      return 0;
    }
  }
  *(undefined1 *)(param_1 + 0x26) = 0;
  Ogre::Viewport::setVisibilityMask(*(Viewport **)(DAT_00920ea0 + 0x1c),1);
  FUN_0061a080();
  return 1;
}

