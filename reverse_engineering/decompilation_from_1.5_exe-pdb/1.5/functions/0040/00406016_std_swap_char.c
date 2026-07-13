/*
 * Entry: 00406016
 * Name: std::swap<char>
 * Namespace: std
 * Signature: void swap<char>(char * param_1, char * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl std::swap<char>(char *param_1,char *param_2)

{
  char cVar1;
  
  if (param_1 != param_2) {
    cVar1 = *param_1;
    *param_1 = *param_2;
    *param_2 = cVar1;
  }
  return;
}
