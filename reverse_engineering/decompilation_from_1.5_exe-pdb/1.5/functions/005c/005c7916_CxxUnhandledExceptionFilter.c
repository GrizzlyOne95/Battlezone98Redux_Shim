/*
 * Entry: 005c7916
 * Name: __CxxUnhandledExceptionFilter
 * Namespace: Global
 * Signature: long __CxxUnhandledExceptionFilter(_EXCEPTION_POINTERS * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

long __cdecl __CxxUnhandledExceptionFilter(_EXCEPTION_POINTERS *param_1)

{
  _EXCEPTION_RECORD *p_Var1;
  ulong uVar2;
  long extraout_EAX;
  
  p_Var1 = param_1->ExceptionRecord;
  if (((p_Var1->ExceptionCode == 0xe06d7363) && (p_Var1->NumberParameters == 3)) &&
     ((uVar2 = p_Var1->ExceptionInformation[0], uVar2 == 0x19930520 ||
      (((uVar2 == 0x19930521 || (uVar2 == 0x19930522)) || (uVar2 == 0x1994000)))))) {
    terminate();
    return extraout_EAX;
  }
  return 0;
}
