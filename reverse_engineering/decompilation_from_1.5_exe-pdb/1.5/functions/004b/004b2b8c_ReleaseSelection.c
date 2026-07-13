/*
 * Entry: 004b2b8c
 * Name: ReleaseSelection
 * Namespace: Global
 * Signature: void ReleaseSelection(TEX_INFO * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __cdecl ReleaseSelection(TEX_INFO *param_1)

{
  int unaff_ESI;
  long in_stack_ffffffe8;
  
  MakePrjFile(&stack0xffffffe8,CONCAT44(0x50414d2e,*(undefined4 *)(unaff_ESI + 0x1c)),
              in_stack_ffffffe8);
  TexCache_UnlockTexture(&stack0xffffffe8);
  *(undefined4 *)(unaff_ESI + 0x20) = 0;
  *(undefined4 *)(unaff_ESI + 0x18) = 0;
  *(undefined4 *)(unaff_ESI + 0x1c) = 0;
  return;
}
