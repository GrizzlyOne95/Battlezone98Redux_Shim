/*
 * Entry: 005c7028
 * Name: __SEH_prolog4
 * Namespace: Global
 * Signature: void __SEH_prolog4(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: This is an inlined function */
/* WARNING: Unable to track spacebase fully for stack */

void __cdecl __SEH_prolog4(void)

{
  int iVar1;
  undefined4 unaff_EBX;
  undefined4 unaff_ESI;
  undefined4 unaff_EDI;
  undefined4 unaff_retaddr;
  int in_stack_00000008;
  uint auStack_1c [5];
  undefined1 local_8 [8];
  
  iVar1 = -in_stack_00000008;
  *(undefined4 *)((int)auStack_1c + iVar1 + 0x10) = unaff_EBX;
  *(undefined4 *)((int)auStack_1c + iVar1 + 0xc) = unaff_ESI;
  *(undefined4 *)((int)auStack_1c + iVar1 + 8) = unaff_EDI;
  *(uint *)((int)auStack_1c + iVar1 + 4) = __security_cookie ^ (uint)&stack0x00000008;
  *(undefined4 *)((int)auStack_1c + iVar1) = unaff_retaddr;
  ExceptionList = local_8;
  return;
}
