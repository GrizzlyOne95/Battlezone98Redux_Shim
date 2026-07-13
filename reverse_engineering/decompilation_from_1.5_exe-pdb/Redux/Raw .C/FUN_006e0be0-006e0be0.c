
undefined4 FUN_006e0be0(int *param_1)

{
  uint uVar1;
  char *pcVar2;
  _Locinfo local_5c [52];
  int local_28;
  undefined4 local_24;
  undefined4 local_20;
  int local_1c;
  void *local_18;
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00853e66;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_14 = 0;
  if ((param_1 != (int *)0x0) && (*param_1 == 0)) {
    local_18 = operator_new(0x18);
    local_8 = 0;
    if (local_18 == (void *)0x0) {
      local_1c = 0;
    }
    else {
      pcVar2 = (char *)FUN_006ab6d0(uVar1);
      local_24 = std::_Locinfo::_Locinfo(local_5c,pcVar2);
      local_8 = CONCAT31(local_8._1_3_,1);
      local_14 = local_14 | 1;
      local_20 = local_24;
      local_1c = FUN_006e46f0(local_24,0,1);
    }
    local_28 = local_1c;
    *param_1 = local_1c;
    local_8 = 0xffffffff;
    if ((local_14 & 1) != 0) {
      local_14 = local_14 & 0xfffffffe;
      std::_Locinfo::~_Locinfo(local_5c);
    }
  }
  ExceptionList = local_10;
  return 4;
}

