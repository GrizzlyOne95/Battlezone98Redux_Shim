/*
 * Entry: 004bd652
 * Name: get_key_name_from_scan_code
 * Namespace: Global
 * Signature: void get_key_name_from_scan_code(uint param_1, char * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl get_key_name_from_scan_code(uint param_1,char *param_2)

{
  char cVar1;
  char *pcVar2;
  
  pcVar2 = *(char **)(&DAT_0062909c + param_1 * 4);
  do {
    cVar1 = *pcVar2;
    pcVar2 = pcVar2 + 1;
    *param_2 = cVar1;
    param_2 = param_2 + 1;
  } while (cVar1 != '\0');
  return;
}
