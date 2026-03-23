
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0043c2a0(undefined4 param_1)

{
  int iVar1;
  
  memset(&DAT_00915600,0,0x40);
  memset(&DAT_009155c0,0,0x40);
  iVar1 = ___scrt_is_ucrt_dll_in_use(param_1);
  if (iVar1 != 0) {
    _DAT_00915600 = 0x40;
    _DAT_00915634 = DAT_008e762c;
    _DAT_00915638 = DAT_008e7630;
    _DAT_0091563c = DAT_008e7654;
    _DAT_009155c0 = 0x40;
    _DAT_009155dc = 0x168;
    _DAT_009155e0 = 0x168;
    _DAT_009155e4 = 0;
    _DAT_009155e8 = 0;
    _DAT_009155ec = 0x3f800000;
    _DAT_009155f0 = 0;
    _DAT_009155f4 = 0x41c80000;
    _DAT_009155f8 = 0x43c80000;
    _DAT_009155fc = 0;
  }
  return;
}

