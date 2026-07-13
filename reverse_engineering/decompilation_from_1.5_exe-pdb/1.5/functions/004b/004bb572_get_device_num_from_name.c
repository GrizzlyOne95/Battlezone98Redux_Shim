/*
 * Entry: 004bb572
 * Name: get_device_num_from_name
 * Namespace: Global
 * Signature: int get_device_num_from_name(char * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl get_device_num_from_name(char *param_1)

{
  int iVar1;
  int iVar2;
  char (*_Str1) [40];
  
  iVar2 = 0;
  if (0 < num_input_devices) {
    _Str1 = input_names;
    do {
      iVar1 = _stricmp(*_Str1,param_1);
      if (iVar1 == 0) {
        if (input_enable[iVar2] == 0) {
          iVar2 = -1;
        }
        return iVar2;
      }
      iVar2 = iVar2 + 1;
      _Str1 = _Str1 + 1;
    } while (iVar2 < num_input_devices);
  }
  iVar2 = load_input_device(param_1);
  return iVar2;
}
