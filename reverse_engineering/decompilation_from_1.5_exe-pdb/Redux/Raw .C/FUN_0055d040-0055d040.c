
void __thiscall FUN_0055d040(int param_1,undefined4 param_2)

{
  char cVar1;
  int iVar2;
  
  iVar2 = FUN_005c8800(param_2);
  if (iVar2 == 2) {
    cVar1 = FUN_005c8410(param_2,"avwalk");
    if (cVar1 != '\0') {
      *(undefined4 *)(param_1 + 0xac) = param_2;
    }
    cVar1 = FUN_005c8410(param_2,"bvltnk");
    if (((cVar1 == '\0') && (cVar1 = FUN_005c8410(param_2,"bvhraz"), cVar1 == '\0')) &&
       (cVar1 = FUN_005c8410(param_2,"avfigh"), cVar1 == '\0')) {
      return;
    }
    FUN_005cb9d0(param_2,*(undefined4 *)(param_1 + 0xa4),1);
  }
  return;
}

