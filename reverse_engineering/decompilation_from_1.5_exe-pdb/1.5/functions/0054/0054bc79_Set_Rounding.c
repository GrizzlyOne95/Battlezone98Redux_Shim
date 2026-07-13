/*
 * Entry: 0054bc79
 * Name: Set_Rounding
 * Namespace: Global
 * Signature: int Set_Rounding(int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl Set_Rounding(int param_1)

{
  undefined4 in_EAX;
  undefined2 in_FPUControlWord;
  undefined4 local_4;
  
  local_4 = CONCAT22((short)((uint)in_EAX >> 0x10),in_FPUControlWord);
  return local_4;
}
