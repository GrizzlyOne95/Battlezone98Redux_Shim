
int FUN_00684ce0(int param_1)

{
  char cVar1;
  int iVar2;
  int iStack_20;
  int local_1c;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084f900;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  if ((DAT_02b79b34 == 0) || (cVar1 = FUN_0048efc0(), cVar1 == '\0')) {
    local_1c = 0;
  }
  else {
    local_1c = 1;
  }
  if (param_1 == 0) {
    ExceptionList = local_10;
    return local_1c;
  }
  if (local_1c != 0) {
    ExceptionList = local_10;
    return local_1c;
  }
  cVar1 = (**(code **)(**(int **)(DAT_00920ea0 + 0xc) + 0x88))();
  if ((cVar1 != '\0') && (iVar2 = FUN_004346a0(), iVar2 == 0)) {
    local_8 = 0;
    Ogre::Root::renderOneFrame(*(Root **)(DAT_00920ea0 + 4));
    iVar2 = FUN_00684ddf();
    return iVar2;
  }
  if ((DAT_02b79b34 == 0) || (cVar1 = FUN_0048efc0(), cVar1 == '\0')) {
    iStack_20 = 0;
  }
  else {
    iStack_20 = 1;
  }
  if (iStack_20 != 0) {
    FUN_00663aa0();
  }
  ExceptionList = local_10;
  return iStack_20;
}

