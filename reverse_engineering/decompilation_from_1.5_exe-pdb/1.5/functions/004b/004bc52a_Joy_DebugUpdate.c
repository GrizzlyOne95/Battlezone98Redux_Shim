/*
 * Entry: 004bc52a
 * Name: Joy_DebugUpdate
 * Namespace: Global
 * Signature: void Joy_DebugUpdate(ulong param_1, ulong param_2, long param_3, long param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __cdecl Joy_DebugUpdate(ulong param_1,ulong param_2,long param_3,long param_4)

{
  int iVar1;
  char local_88 [128];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  iVar1 = Mono_IsActive(mHdl);
  if (iVar1 != 0) {
    sprintf(local_88,"  X   |   %8d   |  %8d   |  %6.3f  |",param_1,param_3,
            (double)((float)param_3 * 1.5258789e-05));
    Mono_Line(mHdl,0,0x11,7,local_88);
    sprintf(local_88,"  Y   |   %8d   |  %8d   |  %6.3f  |",param_2,param_4,
            (double)((float)param_4 * 1.5258789e-05));
    Mono_Line(mHdl,0,0x12,7,local_88);
  }
  return;
}
