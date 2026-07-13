/*
 * Entry: 005c706d
 * Name: __SEH_epilog4
 * Namespace: Global
 * Signature: void __SEH_epilog4(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: This is an inlined function */

void __cdecl __SEH_epilog4(void)

{
  undefined4 *unaff_EBP;
  undefined4 unaff_retaddr;
  
  ExceptionList = (void *)unaff_EBP[-4];
  *unaff_EBP = unaff_retaddr;
  return;
}
