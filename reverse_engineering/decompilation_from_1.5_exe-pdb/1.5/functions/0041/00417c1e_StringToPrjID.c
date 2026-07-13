/*
 * Entry: 00417c1e
 * Name: StringToPrjID
 * Namespace: Global
 * Signature: long64 StringToPrjID(char * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

long64 __cdecl StringToPrjID(char *param_1)

{
  undefined4 local_c;
  undefined4 local_8;
  
  local_c = 0;
  local_8 = 0;
  strncpy((char *)&local_c,param_1,8);
  return CONCAT44(local_8,local_c);
}
