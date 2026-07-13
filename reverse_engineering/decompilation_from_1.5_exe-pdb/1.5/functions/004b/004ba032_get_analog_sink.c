/*
 * Entry: 004ba032
 * Name: get_analog_sink
 * Namespace: Global
 * Signature: ANALOG_SINK * get_analog_sink(FIELD_DESC * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

ANALOG_SINK * __cdecl get_analog_sink(FIELD_DESC *param_1)

{
  char cVar1;
  int iVar2;
  undefined4 *puVar3;
  int iVar4;
  char *pcVar5;
  long *plVar6;
  FIELD_DESC *pFVar7;
  ANALOG_SINK *pAVar8;
  undefined4 *puVar9;
  char *pcVar10;
  undefined1 local_34 [4];
  char local_30 [4];
  char acStack_2c [36];
  uint local_8;
  
  iVar2 = num_analog_sinks;
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  iVar4 = 0;
  local_34 = (undefined1  [4])param_1;
  if (0 < num_analog_sinks) {
    pAVar8 = analog_sink;
    do {
      if (pAVar8->to == param_1->field) {
        return analog_sink + iVar4;
      }
      iVar4 = iVar4 + 1;
      pAVar8 = pAVar8 + 1;
    } while (iVar4 < num_analog_sinks);
  }
  num_analog_sinks = num_analog_sinks + 1;
  if (num_analog_sinks < 0x15) {
    pcVar5 = strstr(param_1->name,"_delta");
    plVar6 = (long *)(iVar2 * 0x34 + 0xb10b4c);
    if (pcVar5 == (char *)0x0) {
      plVar6 = (long *)(iVar2 * 0x34 + 0xb10b48);
    }
    analog_sink[iVar2].delta = plVar6;
    pAVar8 = analog_sink + iVar2;
    pAVar8->to = param_1->field;
    analog_sink[iVar2].range = param_1->max - param_1->min;
    analog_sink[iVar2].min = param_1->min << 0x10;
    analog_sink[iVar2].shift = (char)param_1->shift;
    analog_sink[iVar2].zero =
         ((param_1->zero * 0x10000 - analog_sink[iVar2].min) * 2) / analog_sink[iVar2].range +
         -0x10000;
    analog_sink[iVar2].tweak = param_1->tweak;
    analog_sink[iVar2].current = analog_sink[iVar2].zero;
    pcVar5 = param_1->name;
    iVar4 = -(int)pcVar5;
    do {
      cVar1 = *pcVar5;
      pcVar5[(int)(local_30 + iVar4)] = cVar1;
      pcVar5 = pcVar5 + 1;
    } while (cVar1 != '\0');
    pcVar5 = strstr(local_30,"_delta");
    if (pcVar5 != (char *)0x0) {
      *pcVar5 = '\0';
    }
    pcVar5 = local_34 + 3;
    do {
      pcVar10 = pcVar5;
      pcVar5 = pcVar10 + 1;
    } while (pcVar10[1] != '\0');
    builtin_strncpy(pcVar10 + 1,"_plus",6);
    pFVar7 = get_field_pointer(local_30);
    if (pFVar7 == (FIELD_DESC *)0x0) {
      analog_sink[iVar2].plus_discrete = (char *)0x0;
    }
    else {
      analog_sink[iVar2].plus_discrete = pFVar7->field;
    }
    pcVar5 = *(char **)local_34;
    iVar4 = -(int)pcVar5;
    do {
      cVar1 = *pcVar5;
      pcVar5[(int)(local_30 + iVar4)] = cVar1;
      pcVar5 = pcVar5 + 1;
    } while (cVar1 != '\0');
    pcVar5 = strstr(local_30,"_delta");
    if (pcVar5 != (char *)0x0) {
      *pcVar5 = '\0';
    }
    pcVar5 = local_34 + 3;
    do {
      pcVar10 = pcVar5;
      pcVar5 = pcVar10 + 1;
    } while (pcVar10[1] != '\0');
    builtin_strncpy(pcVar10 + 1,"_minus",7);
    pFVar7 = get_field_pointer(local_30);
    if (pFVar7 == (FIELD_DESC *)0x0) {
      analog_sink[iVar2].minus_discrete = (char *)0x0;
    }
    else {
      analog_sink[iVar2].minus_discrete = pFVar7->field;
    }
    pcVar5 = *(char **)local_34;
    iVar4 = -(int)pcVar5;
    do {
      cVar1 = *pcVar5;
      pcVar5[(int)(local_30 + iVar4)] = cVar1;
      pcVar5 = pcVar5 + 1;
    } while (cVar1 != '\0');
    puVar3 = (undefined4 *)(local_34 + 3);
    do {
      puVar9 = puVar3;
      puVar3 = (undefined4 *)((int)puVar9 + 1);
    } while (*(char *)((int)puVar9 + 1) != '\0');
    *(undefined4 *)((int)puVar9 + 1) = 0x7465735f;
    *(undefined1 *)((int)puVar9 + 5) = 0;
    pFVar7 = get_field_pointer(local_30);
    if (pFVar7 == (FIELD_DESC *)0x0) {
      analog_sink[iVar2].set_discrete = (char *)0x0;
    }
    else {
      analog_sink[iVar2].set_discrete = pFVar7->field;
    }
    pcVar5 = *(char **)local_34;
    iVar4 = -(int)pcVar5;
    do {
      cVar1 = *pcVar5;
      pcVar5[(int)(local_30 + iVar4)] = cVar1;
      pcVar5 = pcVar5 + 1;
    } while (cVar1 != '\0');
    pcVar5 = local_34 + 3;
    do {
      pcVar10 = pcVar5;
      pcVar5 = pcVar10 + 1;
    } while (pcVar10[1] != '\0');
    builtin_strncpy(pcVar10 + 1,"_reset",7);
    pFVar7 = get_field_pointer(local_30);
    if (pFVar7 == (FIELD_DESC *)0x0) {
      analog_sink[iVar2].reset_discrete = (char *)0x0;
    }
    else {
      analog_sink[iVar2].reset_discrete = pFVar7->field;
    }
  }
  else {
    DEBUG_systemWarning("Too many analog sinks: line %d");
    pAVar8 = (ANALOG_SINK *)0x0;
  }
  return pAVar8;
}
