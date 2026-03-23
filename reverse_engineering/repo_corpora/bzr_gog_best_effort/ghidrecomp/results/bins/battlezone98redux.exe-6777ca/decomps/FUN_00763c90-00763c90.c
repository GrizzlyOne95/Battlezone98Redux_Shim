
/* WARNING: Removing unreachable block (ram,0x00763cf2) */

void __fastcall FUN_00763c90(undefined4 param_1)

{
  uint uVar1;
  undefined4 uVar2;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00845608;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  FUN_007d6a70("p2p connection problem\n",uVar1,param_1);
  basic_string<>("unknown error");
  local_8 = 0;
  uVar2 = FUN_0041f870();
  FUN_007d6a70(uVar2,uVar1,param_1);
  FUN_007d6a70(&DAT_0087a44c);
  local_8 = 0xffffffff;
  ~basic_string<>();
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

