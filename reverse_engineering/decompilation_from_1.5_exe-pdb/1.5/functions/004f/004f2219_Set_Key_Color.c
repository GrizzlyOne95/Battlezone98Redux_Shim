/*
 * Entry: 004f2219
 * Name: Set_Key_Color
 * Namespace: Global
 * Signature: void Set_Key_Color(long param_1, long param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Set_Key_Color(long param_1,long param_2)

{
  memset(Chrome_Key_Table + (param_1 & 0xff),param_2 & 0xff,0x100);
  return;
}
