
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00690630(int param_1)

{
  int iVar1;
  void *pvVar2;
  size_t _Size;
  
  if (*(int *)(&DAT_00930f80 + param_1 * 4) == 0) {
    _Size = 4;
    iVar1 = FUN_006a4030();
    pvVar2 = calloc(DAT_009310c4 + 1 + iVar1,_Size);
    *(void **)(&DAT_00930fc0 + param_1 * 4) = pvVar2;
    *(undefined4 *)(&DAT_02bfdfb0 + param_1 * 4) = 0;
    *(undefined4 *)(&DAT_00930f80 + param_1 * 4) = 1;
  }
  else {
    _DAT_009310bc = "Schedule\\Aibuild.cpp";
    _DAT_009310c0 = 0x1d1;
    FUN_006a5f50(1,"AIBuild_ConstructionNew called twice with no delete\n");
  }
  return;
}

