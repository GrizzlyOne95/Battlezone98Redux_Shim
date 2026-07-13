/*
 * Entry: 004bb425
 * Name: load_input_device
 * Namespace: Global
 * Signature: int load_input_device(char * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl load_input_device(char *param_1)

{
  char cVar1;
  _tagGIDDI_DRIVER *p_Var2;
  int iVar3;
  int iVar4;
  int iVar5;
  char *pcVar6;
  _tagGIDDI_DRIVER **pp_Var7;
  int local_c;
  int local_8;
  
  local_c = 0;
  pp_Var7 = masterGIDDIList;
  do {
    if (((*pp_Var7 != (_tagGIDDI_DRIVER *)0x0) &&
        (iVar4 = (*(*pp_Var7)->get_num_devices)(), iVar4 != 0)) && (local_8 = 0, 0 < iVar4)) {
      do {
        iVar3 = num_input_devices;
        if (4 < num_input_devices) {
          DEBUG_systemWarning("Too many input devices specified");
          return -1;
        }
        iVar5 = (*(*pp_Var7)->describe_device)(local_8,input_desc + num_input_devices);
        if (iVar5 == 0) {
          iVar5 = _stricmp(input_desc[iVar3].short_name,param_1);
          if (iVar5 == 0) {
            iVar4 = iVar3 * 0x28 - (int)param_1;
            do {
              cVar1 = *param_1;
              param_1[(int)input_names + iVar4] = cVar1;
              param_1 = param_1 + 1;
            } while (cVar1 != '\0');
            p_Var2 = masterGIDDIList[local_c];
            num_input_devices = num_input_devices + 1;
            input_funcs[iVar3] = p_Var2;
            iVar4 = (*p_Var2->open)(input_desc + iVar3);
            if (iVar4 != 0) {
              InputErrorOkOrCancel(0x70,(char *)0x0,input_desc[iVar3].long_name);
              input_enable[iVar3] = 0;
              return -1;
            }
            input_enable[iVar3] = 1;
            return iVar3;
          }
          (*(*pp_Var7)->close)(input_desc + iVar3);
        }
        local_8 = local_8 + 1;
      } while (local_8 < iVar4);
    }
    iVar4 = num_input_devices;
    local_c = local_c + 1;
    pp_Var7 = pp_Var7 + 1;
    if (0x62729b < (int)pp_Var7) {
      num_input_devices = num_input_devices + 1;
      pcVar6 = param_1;
      do {
        cVar1 = *pcVar6;
        pcVar6[(int)input_names + (iVar4 * 0x28 - (int)param_1)] = cVar1;
        pcVar6 = pcVar6 + 1;
      } while (cVar1 != '\0');
      input_enable[iVar4] = 0;
      InputErrorOkOrCancel(0x6e,(char *)0x0,param_1);
      return -1;
    }
  } while( true );
}
