/*
 * Entry: 00585850
 * Name: copy3
 * Namespace: Global
 * Signature: void copy3(uchar * param_1, uchar * param_2, ulong param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl copy3(uchar *param_1,uchar *param_2,ulong param_3)

{
  undefined1 *in_EAX;
  undefined1 uVar1;
  undefined1 *in_ECX;
  
  *in_EAX = *in_ECX;
  if (param_1 == (uchar *)0x1) {
    uVar1 = *in_ECX;
    in_EAX[1] = uVar1;
  }
  else {
    in_EAX[1] = in_ECX[1];
    if (param_1 == (uchar *)0x2) {
      uVar1 = *in_ECX;
    }
    else {
      uVar1 = in_ECX[2];
    }
  }
  in_EAX[2] = uVar1;
  return;
}
