/*
 * Entry: 005c744a
 * Name: pre_c_init
 * Namespace: Global
 * Signature: int pre_c_init(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Removing unreachable block (ram,0x005c747b) */
/* WARNING: Removing unreachable block (ram,0x005c7458) */
/* WARNING: Removing unreachable block (ram,0x005c7483) */
/* WARNING: Removing unreachable block (ram,0x005c748c) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Enum "SectionFlags": Some values do not have unique names */

int __cdecl pre_c_init(void)

{
  int *piVar1;
  
  managedapp = 0;
  __set_app_type(2);
  __onexitend = (_func___cdecl_void **)encode_pointer(0xffffffff);
  __onexitbegin = __onexitend;
  piVar1 = (int *)__p__fmode();
  *piVar1 = _fmode;
  piVar1 = (int *)__p__commode();
  *piVar1 = _commode;
  _adjust_fdiv = _DAT_00225b70;
  _RTC_Initialize();
  _setargv();
  if (__defaultmatherr == 0) {
    __setusermatherr(_matherr);
  }
  _setdefaultprecision();
  if (__globallocalestatus == -1) {
    _configthreadlocale(-1);
  }
  return 0;
}
