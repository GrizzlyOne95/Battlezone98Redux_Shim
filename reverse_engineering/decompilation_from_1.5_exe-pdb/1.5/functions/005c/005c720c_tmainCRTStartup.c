/*
 * Entry: 005c720c
 * Name: __tmainCRTStartup
 * Namespace: Global
 * Signature: int __tmainCRTStartup(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __SEH_prolog4 replaced with injection: SEH_prolog4 */
/* WARNING: Function: __SEH_epilog4 replaced with injection: EH_epilog3 */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int __cdecl __tmainCRTStartup(void)

{
  byte bVar1;
  void *Exchange;
  void *pvVar2;
  int iVar3;
  uint uVar4;
  bool bVar5;
  byte *pbVar6;
  _STARTUPINFOA local_6c;
  byte *local_24;
  uint local_20;
  undefined4 uStack_c;
  undefined4 local_8;
  
  uStack_c = 0x5c7218;
  bVar5 = false;
  local_20 = 0;
  local_8 = 0;
  GetStartupInfoA(&local_6c);
  Exchange = StackBase;
  local_8 = 1;
  do {
    pvVar2 = (void *)InterlockedCompareExchange((LONG *)&__native_startup_lock,(LONG)Exchange,0);
    if (pvVar2 == (void *)0x0) {
LAB_005c726f:
      if (__native_startup_state == __initializing) {
        amsg_exit(0x1f);
      }
      else if (__native_startup_state == __uninitialized) {
        __native_startup_state = __initializing;
        iVar3 = initterm_e(__xi_a,__xi_z);
        if (iVar3 != 0) {
          return 0xff;
        }
      }
      else {
        has_cctor = 1;
      }
      if (__native_startup_state == __initializing) {
        initterm(__xc_a,__xc_z);
        __native_startup_state = __initialized;
      }
      if (!bVar5) {
        InterlockedExchange((LONG *)&__native_startup_lock,0);
      }
      pbVar6 = _DAT_00225b22;
      if ((__dyn_tls_init_callback != (_func___cdecl_void_void_ptr_ulong_void_ptr *)0x0) &&
         (iVar3 = _IsNonwritableInCurrentImage((uchar *)&__dyn_tls_init_callback),
         pbVar6 = _DAT_00225b22, iVar3 != 0)) {
        (*__dyn_tls_init_callback)((void *)0x0,2,(void *)0x0);
        pbVar6 = _DAT_00225b22;
      }
      while ((bVar1 = *pbVar6, local_24 = pbVar6, 0x20 < bVar1 || ((bVar1 != 0 && (local_20 != 0))))
            ) {
        if (bVar1 == 0x22) {
          local_20 = (uint)(local_20 == 0);
        }
        iVar3 = (*(code *)0x22591e)(bVar1);
        if (iVar3 != 0) {
          pbVar6 = pbVar6 + 1;
        }
        pbVar6 = pbVar6 + 1;
      }
      for (; (*local_24 != 0 && (*local_24 < 0x21)); local_24 = local_24 + 1) {
      }
      if (((byte)local_6c.dwFlags & 1) == 0) {
        uVar4 = 10;
      }
      else {
        uVar4 = (uint)local_6c.wShowWindow;
      }
      mainret = WinMain((HINSTANCE__ *)&IMAGE_DOS_HEADER_00400000,(HINSTANCE__ *)0x0,
                        (char *)local_24,uVar4);
      if (managedapp != 0) {
        if (has_cctor == 0) {
          _cexit();
        }
        return mainret;
      }
                    /* WARNING: Subroutine does not return */
      exit(mainret);
    }
    if (pvVar2 == Exchange) {
      bVar5 = true;
      goto LAB_005c726f;
    }
    Sleep(1000);
  } while( true );
}
