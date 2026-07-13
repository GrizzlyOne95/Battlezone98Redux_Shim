/*
 * Entry: 005c468a
 * Name: getunopr
 * Namespace: Global
 * Signature: UnOpr getunopr(int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

UnOpr __cdecl getunopr(int param_1)

{
  int in_EAX;
  
  if (in_EAX == 0x23) {
    return OPR_LEN;
  }
  if (in_EAX != 0x2d) {
    return (uint)(in_EAX != 0x10e) * 2 + OPR_NOT;
  }
  return OPR_MINUS;
}
