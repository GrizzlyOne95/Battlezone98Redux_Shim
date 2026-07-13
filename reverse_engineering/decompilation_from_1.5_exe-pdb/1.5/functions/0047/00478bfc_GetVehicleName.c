/*
 * Entry: 00478bfc
 * Name: GetVehicleName
 * Namespace: Global
 * Signature: void GetVehicleName(char * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl GetVehicleName(char *param_1)

{
  char cVar1;
  char *pcVar2;
  
  pcVar2 = vehicle_name;
  do {
    cVar1 = *pcVar2;
    (param_1 + -0xa0f1b0)[(int)pcVar2] = cVar1;
    pcVar2 = pcVar2 + 1;
  } while (cVar1 != '\0');
  return;
}
