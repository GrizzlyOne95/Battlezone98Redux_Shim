
void __fastcall FUN_00793070(int param_1)

{
  int iVar1;
  int *piVar2;
  void *pvVar3;
  undefined4 local_24;
  int local_18;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0085eb5c;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  iVar1 = FUN_007d2250(DAT_008e7000 ^ (uint)&stack0xfffffffc);
  for (local_18 = 0; local_18 < iVar1; local_18 = local_18 + 1) {
    piVar2 = (int *)FUN_007d2270(local_18);
    (**(code **)(*piVar2 + 0x24))(0);
  }
  if (*(int *)(param_1 + 0x154) != 0) {
    FUN_007cc5c0(0);
  }
  if (*(int *)(param_1 + 0x158) != 0) {
    (**(code **)(**(int **)(param_1 + 0x158) + 0x24))(0);
  }
  pvVar3 = operator_new(0x144);
  local_8 = 0;
  if (pvVar3 == (void *)0x0) {
    local_24 = 0;
  }
  else {
    local_24 = FUN_007d1cc0("movie_overlay_success",0,0,0,0,1,param_1,0);
  }
  local_8 = 0xffffffff;
  *(undefined4 *)(param_1 + 0x148) = local_24;
  FUN_007d3f20(9);
  FUN_007d2870("blackui.png");
  FUN_00623eb0();
  FUN_0078c480(1);
  FUN_007d2110(*(undefined4 *)(param_1 + 0x148),0);
  ExceptionList = local_10;
  return;
}

