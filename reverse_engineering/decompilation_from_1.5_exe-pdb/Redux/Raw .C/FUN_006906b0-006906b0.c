
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_006906b0(int param_1)

{
  if (*(int *)(&DAT_00930f80 + param_1 * 4) == 1) {
    free(*(void **)(&DAT_00930fc0 + param_1 * 4));
    *(undefined4 *)(&DAT_00930f80 + param_1 * 4) = 0;
  }
  else {
    _DAT_009310bc = "Schedule\\Aibuild.cpp";
    _DAT_009310c0 = 0x1dd;
    FUN_006a5f50(1,"AIBuild_ConstructionDelete called without New\n");
  }
  return;
}

