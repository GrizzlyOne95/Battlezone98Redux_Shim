
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 * __thiscall FUN_0083d0c0(undefined4 *param_1,char *param_2,int param_3)

{
  char cVar1;
  uint uVar2;
  char *pcVar3;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_00865326;
  local_10 = ExceptionList;
  uVar2 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  *param_1 = 0;
  param_1[1] = 0;
  param_1[2] = 0;
  param_1[3] = 0;
  param_1[9] = 0xf;
  param_1[8] = 0;
  *(undefined1 *)(param_1 + 4) = 0;
  param_1[0x12] = 0;
  param_1[0x13] = 0;
  param_1[0x14] = 0;
  local_8 = 1;
  *(undefined1 *)(param_1 + 0x10) = 1;
  param_1[10] = param_3 + 3U & 0xfffffffc;
  param_1[0xc] = 8;
  FUN_0083d6a0(uVar2);
  if (*param_2 == '\0') {
    uVar2 = 0;
  }
  else {
    pcVar3 = param_2;
    do {
      cVar1 = *pcVar3;
      pcVar3 = pcVar3 + 1;
    } while (cVar1 != '\0');
    uVar2 = (int)pcVar3 - (int)(param_2 + 1);
  }
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::assign
            ((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
             (param_1 + 4),param_2,uVar2);
  if ((DAT_00914cd8 & 1) == 0) {
    DAT_00914cd8 = DAT_00914cd8 | 1;
    _DAT_00914cc4 = &DAT_00914cc4;
    DAT_00914cd4 = 0;
    DAT_00914ccc = (undefined4 *)&DAT_00914cc4;
    DAT_00914cc8 = &DAT_00914cc4;
    _DAT_00914cd0 = 0;
  }
  DAT_00914cd4 = DAT_00914cd4 + 1;
  param_1[3] = param_1;
  *param_1 = &DAT_00914cc4;
  param_1[1] = &DAT_00914cc4;
  param_1[2] = DAT_00914ccc;
  DAT_00914ccc = param_1;
  *(undefined4 **)(param_1[2] + 4) = param_1;
  if ((uint)((int)(param_1[0x14] - param_1[0x12]) >> 2) < 0x10) {
    FUN_0083d730(0x10);
  }
  ExceptionList = local_10;
  return param_1;
}

