
void FUN_00813fc0(longlong *param_1,undefined1 param_2)

{
  int iVar1;
  longlong lVar2;
  
  iVar1 = FUN_00814580(param_2);
  lVar2 = __allmul((int)*param_1,*(undefined4 *)((int)param_1 + 4),10,0);
  *param_1 = lVar2 + iVar1;
  return;
}

