
void FUN_0043c880(undefined4 param_1,int param_2)

{
  int iVar1;
  undefined4 local_18;
  int local_14;
  int local_10;
  undefined4 local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  iVar1 = ___scrt_is_ucrt_dll_in_use(param_1);
  if (iVar1 != 0) {
    local_18 = 0x20001;
    local_14 = param_2;
    local_10 = param_2 << 2;
    local_c = 0x100004;
    (**(code **)(*DAT_009155bc + 0x38))(DAT_009155bc,&local_18);
  }
  FUN_0083e885();
  return;
}

