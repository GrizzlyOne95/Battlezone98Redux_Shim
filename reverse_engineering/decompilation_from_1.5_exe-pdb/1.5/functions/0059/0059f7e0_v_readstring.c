/*
 * Entry: 0059f7e0
 * Name: _v_readstring
 * Namespace: Global
 * Signature: void _v_readstring(oggpack_buffer * param_1, char * param_2, int param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl _v_readstring(oggpack_buffer *param_1,char *param_2,int param_3)

{
  undefined1 uVar1;
  int in_EAX;
  undefined1 *in_ECX;
  
  for (; in_EAX != 0; in_EAX = in_EAX + -1) {
    uVar1 = oggpack_read();
    *in_ECX = uVar1;
    in_ECX = in_ECX + 1;
  }
  return;
}
