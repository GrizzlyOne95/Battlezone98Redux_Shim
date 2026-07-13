/*
 * Entry: 004bb703
 * Name: add_analog_channel
 * Namespace: Global
 * Signature: int add_analog_channel(FIELD_DESC * param_1, char * param_2, int param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl add_analog_channel(FIELD_DESC *param_1,char *param_2,int param_3)

{
  int iVar1;
  ANALOG_SINK *pAVar2;
  long *plVar3;
  ANALOG_SINK **ppAVar4;
  int iVar5;
  
  iVar1 = num_analog_controls;
  iVar5 = 0;
  if (0 < num_analog_controls) {
    ppAVar4 = &analog_map[0].sink;
    do {
      if ((*ppAVar4 != (ANALOG_SINK *)0x0) && ((*ppAVar4)->to == param_1->field)) {
        if (param_2 == (char *)0x0) {
          return iVar5;
        }
        if (ppAVar4[-3] == (ANALOG_SINK *)0x0) {
          iVar1 = get_device_num_from_name(param_2);
          analog_map[iVar5].from = invals[iVar1].analog + param_3;
          analog_map[iVar5].device = iVar1;
          analog_map[iVar5].channel = param_3;
          return iVar5;
        }
      }
      iVar5 = iVar5 + 1;
      ppAVar4 = ppAVar4 + 0x20;
    } while (iVar5 < num_analog_controls);
  }
  num_analog_controls = num_analog_controls + 1;
  if (num_analog_controls < 0x15) {
    if (param_2 == (char *)0x0) {
      iVar5 = -1;
    }
    else {
      iVar5 = get_device_num_from_name(param_2);
    }
    analog_map[iVar1].device = iVar5;
    analog_map[iVar1].channel = param_3;
    pAVar2 = get_analog_sink(param_1);
    analog_map[iVar1].sink = pAVar2;
    if (iVar5 < 0) {
      plVar3 = (long *)0x0;
    }
    else {
      plVar3 = invals[iVar5].analog + param_3;
    }
    analog_map[iVar1].from = plVar3;
    iVar5 = strncmp(param_1->name,"menu_",5);
    analog_map[iVar1].in_menu = (uint)(iVar5 == 0);
  }
  else {
    DEBUG_systemWarning("Too many analog controls: line %d");
    iVar1 = -1;
  }
  return iVar1;
}
