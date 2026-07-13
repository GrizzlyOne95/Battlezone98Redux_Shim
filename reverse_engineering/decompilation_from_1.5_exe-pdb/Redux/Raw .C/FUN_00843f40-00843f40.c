
/* WARNING: Removing unreachable block (ram,0x00843faa) */

void __fastcall FUN_00843f40(undefined4 *param_1)

{
  undefined4 uVar1;
  bool bVar2;
  undefined4 local_30;
  void *local_2c;
  void *local_28 [4];
  undefined4 local_18;
  uint local_14;
  uint local_10;
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_00865ea4;
  local_c = ExceptionList;
  local_10 = DAT_008e7000 ^ (uint)&local_30;
  ExceptionList = &local_c;
  local_30 = 0;
  local_2c = operator_new(0x1c);
  local_4 = 0;
  bVar2 = local_2c == (void *)0x0;
  if (bVar2) {
    uVar1 = 0;
  }
  else {
    local_14 = 0xf;
    local_18 = 0;
    local_28[0] = (void *)((uint)local_28[0] & 0xffffff00);
    std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::assign
              ((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
               local_28,"Microsoft Base Cryptographic Provider v1.0",0x2a);
    local_4 = CONCAT31(local_4._1_3_,1);
    local_30 = 1;
    uVar1 = FUN_00843d90(local_28);
  }
  *param_1 = uVar1;
  if ((!bVar2) && (0xf < local_14)) {
    operator_delete(local_28[0]);
  }
  ExceptionList = local_c;
  FUN_0083e885();
  return;
}

