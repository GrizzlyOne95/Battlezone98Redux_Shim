/*
 * Entry: 0058583a
 * Name: copy2
 * Namespace: Global
 * Signature: void copy2(uchar * param_1, uchar * param_2, ulong param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl copy2(uchar *param_1,uchar *param_2,ulong param_3)

{
  undefined1 uVar1;
  undefined1 *in_EAX;
  undefined1 *in_ECX;
  
  *in_ECX = *in_EAX;
  if (param_1 == (uchar *)0x1) {
    uVar1 = *in_EAX;
  }
  else {
    uVar1 = in_EAX[1];
  }
  in_ECX[1] = uVar1;
  return;
}
