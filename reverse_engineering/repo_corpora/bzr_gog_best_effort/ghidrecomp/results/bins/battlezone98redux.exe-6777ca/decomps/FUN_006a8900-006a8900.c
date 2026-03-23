
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_006a8900(undefined4 *param_1)

{
  if (param_1 == (undefined4 *)0x0) {
    _DAT_009310bc = "Schedule\\Squad.cpp";
    _DAT_009310c0 = 0xa7;
    FUN_006a5f50(2,"AI  Squad_Delete tried to free a NULL squad");
  }
  else {
    FUN_006a5fd0("Freeing Squad #%d  @%d\n",*param_1,param_1);
    FUN_0069d280(param_1 + 3);
    FUN_006a89e0(param_1);
    free(param_1);
    FUN_006a5fd0("Freed Squad \n");
  }
  return;
}

