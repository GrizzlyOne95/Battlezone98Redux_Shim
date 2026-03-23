
void FUN_00707ce0(undefined4 param_1,int param_2,
                 basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                 *param_3,undefined4 param_4)

{
  void *_Dst;
  undefined4 uVar1;
  void *_Src;
  size_t _Size;
  undefined1 local_ac [12];
  void *local_a0;
  undefined4 local_9c;
  uint local_98;
  undefined1 local_48 [28];
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  uint local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0085725d;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_98 = 0;
  _String_const_iterator<>(local_14);
  local_8 = 0;
  if (param_2 == 0) {
    FUN_006d4f40(local_ac);
    local_98 = local_98 | 1;
    local_8 = 0xffffffff;
    FUN_006cd590();
  }
  else {
    std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
    basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>(local_2c,param_3);
    local_8._0_1_ = 1;
    if (*(int *)(param_2 + 0x14) != 0) {
      std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::operator=
                (local_2c,*(char **)(param_2 + 0x14));
    }
    local_a0 = operator_new(0xc);
    local_8._0_1_ = 2;
    if (local_a0 == (void *)0x0) {
      local_9c = 0;
    }
    else {
      local_9c = vector<>();
    }
    local_8 = CONCAT31(local_8._1_3_,1);
    FUN_0070fb90(local_9c);
    for (; param_2 != 0; param_2 = *(int *)(param_2 + 0x1c)) {
      if ((*(int *)(param_2 + 4) == 2) || (*(int *)(param_2 + 4) == 0x17)) {
        FUN_006cb470();
        FUN_006d57f0(*(undefined4 *)(param_2 + 0x10));
        _Size = *(size_t *)(param_2 + 0x10);
        _Src = *(void **)(param_2 + 0x18);
        _Dst = (void *)FUN_006d0d10();
        memcpy(_Dst,_Src,_Size);
        uVar1 = FUN_00708530(local_48,local_2c,param_4);
        local_8._0_1_ = 3;
        FUN_00421ec0(uVar1);
        FUN_007085b0(uVar1);
        local_8 = CONCAT31(local_8._1_3_,1);
        FUN_00708210();
      }
    }
    FUN_006d4f40(local_ac);
    local_98 = local_98 | 1;
    local_8 = local_8 & 0xffffff00;
    ~basic_string<>();
    local_8 = 0xffffffff;
    FUN_006cd590();
  }
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

