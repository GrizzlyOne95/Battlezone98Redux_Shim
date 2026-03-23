
void __fastcall FUN_00435bc0(int param_1)

{
  uint uVar1;
  HWND pHVar2;
  BOOL BVar3;
  undefined4 local_30;
  undefined1 local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00845608;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_14 = uVar1;
  basic_string<>("WINDOW");
  local_8 = 0;
  (**(code **)(**(int **)(param_1 + 0xc) + 0x6c))(local_2c,&DAT_009183fc,uVar1);
  local_8 = 0xffffffff;
  ~basic_string<>();
  *DAT_02cecefc = DAT_009183fc;
  DAT_02cf44a0 = DAT_009183fc;
  pHVar2 = GetActiveWindow();
  if (pHVar2 == DAT_009183fc) {
    BVar3 = IsIconic(DAT_009183fc);
    if (BVar3 == 0) {
      local_30 = 1;
      goto LAB_00435c71;
    }
  }
  local_30 = 0;
LAB_00435c71:
  DAT_008eaaa4 = local_30;
  FUN_00624110();
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

