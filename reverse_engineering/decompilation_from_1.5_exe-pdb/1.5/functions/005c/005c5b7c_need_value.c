/*
 * Entry: 005c5b7c
 * Name: need_value
 * Namespace: Global
 * Signature: int need_value(FuncState * param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl need_value(FuncState *param_1,int param_2)

{
  int in_EAX;
  uint *puVar1;
  FuncState *unaff_ESI;
  int unaff_retaddr;
  
  while( true ) {
    if (in_EAX == -1) {
      return 0;
    }
    puVar1 = getjumpcontrol(unaff_ESI,unaff_retaddr);
    if (((byte)*puVar1 & 0x3f) != 0x1b) break;
    in_EAX = getjump(unaff_ESI,unaff_retaddr);
  }
  return 1;
}
