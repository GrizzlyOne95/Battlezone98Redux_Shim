/*
 * Entry: 00583d4f
 * Name: code_run
 * Namespace: Global
 * Signature: uchar * code_run(lzo1x_999_t * param_1, uchar * param_2, uchar * param_3, ulong param_4, ulong param_5)
 * Symbol source: IMPORTED
 * Export status: ok
 */

uchar * __cdecl
code_run(lzo1x_999_t *param_1,uchar *param_2,uchar *param_3,ulong param_4,ulong param_5)

{
  uchar *in_EAX;
  uchar *puVar1;
  int in_ECX;
  uchar *unaff_ESI;
  uchar *unaff_EDI;
  ulong unaff_retaddr;
  
  if (unaff_ESI != (uchar *)0x0) {
    puVar1 = STORE_RUN(param_1,unaff_ESI,unaff_EDI,unaff_retaddr);
    *(uchar **)(in_ECX + 0x50) = param_2;
    *(uchar **)(in_ECX + 0x4c) = unaff_ESI;
    return puVar1;
  }
  *(undefined4 *)(in_ECX + 0x50) = 0;
  *(undefined4 *)(in_ECX + 0x4c) = 0;
  return in_EAX;
}
