
void __fastcall FUN_0078e410(int param_1)

{
  void *pvVar1;
  undefined4 uVar2;
  undefined4 local_1c;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_008477bc;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_0078c4a0(DAT_008e7000 ^ (uint)&stack0xfffffffc);
  pvVar1 = operator_new(0x144);
  local_8 = 0;
  if (pvVar1 == (void *)0x0) {
    local_1c = 0;
  }
  else {
    local_1c = FUN_007d1cc0("Splash_Overlay2",0,0,0,0,0x201,0,0);
  }
  local_8 = 0xffffffff;
  *(undefined4 *)(param_1 + 0x154) = local_1c;
  FUN_007d3f20(2);
  FUN_007d2870("blackui2.png");
  FUN_007d2110();
  *(undefined4 *)(param_1 + 0x148) = 1;
  uVar2 = FUN_00822e60();
  *(undefined4 *)(param_1 + 0x14c) = uVar2;
  FUN_0078c4b0(0x4097700000000000,FUN_0078e020);
  ExceptionList = local_10;
  return;
}

