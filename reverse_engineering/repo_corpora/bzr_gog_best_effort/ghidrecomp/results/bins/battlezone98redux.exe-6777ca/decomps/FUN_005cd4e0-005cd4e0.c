
undefined4 __fastcall FUN_005cd4e0(undefined4 param_1)

{
  int iVar1;
  
  if (DAT_02a13c7b == '\0') {
    FUN_00821ec0(param_1);
  }
  while (iVar1 = FUN_0061a050(), iVar1 != 0) {
    FUN_007d6a70("fsm_pop_camera called again\n");
    FUN_00821ec0();
  }
  FUN_006217a0();
  FUN_0041e660();
  DAT_02a13d64 = 0;
  DAT_009182a4 = 0;
  DAT_02a13c7b = 0;
  return 1;
}

