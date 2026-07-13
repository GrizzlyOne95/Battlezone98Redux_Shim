
void __thiscall FUN_008084c0(undefined4 *param_1,undefined4 param_2,undefined4 param_3)

{
  char cVar1;
  undefined4 uVar2;
  undefined1 local_48 [52];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00864953;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  if (*(char *)(param_1 + 4) == '\0') {
    std::_Destroy_range<struct_std::_Wrap_alloc<class_std::allocator<unsigned_char>_>_>
              (*param_1,0,local_14);
  }
  cVar1 = FUN_00808e30(*param_1,param_1[1],param_1[2],param_1[3],param_3);
  if (cVar1 == '\0') {
    if (*(char *)(param_1 + 4) != '\0') {
      *(undefined1 *)(param_1 + 4) = 0;
      goto LAB_00808613;
    }
    uVar2 = FUN_00808e80(local_48,param_1[2]);
    local_8 = 0;
    uVar2 = FUN_008089b0(*(undefined4 *)*param_1,*(undefined4 *)param_1[1],uVar2);
    local_8._0_1_ = 1;
    FUN_008011e0(uVar2);
    local_8 = (uint)local_8._1_3_ << 8;
    FUN_008000b0();
    local_8 = 0xffffffff;
    FUN_00800170();
  }
  *(undefined1 *)(param_1 + 4) = 0;
LAB_00808613:
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

