
void FUN_00765a20(undefined4 param_1)

{
  bool bVar1;
  int iVar2;
  int local_d0 [44];
  undefined1 local_20 [24];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  basic_string<>(param_1);
  FUN_004203f0(local_20,3,1);
  ~basic_string<>();
  FUN_0041f830();
  FUN_0073ba90(local_d0,&DAT_0260b460);
  bVar1 = std::ios_base::eof((ios_base *)((int)local_d0 + *(int *)(local_d0[0] + 4)));
  if (!bVar1) {
    iVar2 = std::basic_istream<char,struct_std::char_traits<char>_>::get
                      ((basic_istream<char,struct_std::char_traits<char>_> *)local_d0);
    if (iVar2 == 0x2c) {
      FUN_004272a0(local_d0,&DAT_0260b428,0);
    }
  }
  FUN_00417f10();
  FUN_0083e885();
  return;
}

