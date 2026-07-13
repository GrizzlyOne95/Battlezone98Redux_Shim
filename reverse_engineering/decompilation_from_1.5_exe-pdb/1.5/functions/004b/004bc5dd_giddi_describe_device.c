/*
 * Entry: 004bc5dd
 * Name: giddi_describe_device
 * Namespace: Global
 * Signature: int giddi_describe_device(int param_1, _GIDDI_DEVDESC * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

int __cdecl giddi_describe_device(int param_1,_GIDDI_DEVDESC *param_2)

{
  MMRESULT MVar1;
  char **ppcVar2;
  char **ppcVar3;
  char **ppcVar4;
  char **ppcVar5;
  int *piVar6;
  int iVar7;
  char *pcVar8;
  code *pcVar9;
  char *pcVar10;
  bool bVar11;
  int local_1a0;
  tagJOYCAPSA local_19c;
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)(local_19c.szOEMVxD + 0x98);
  MVar1 = joyGetDevCapsA(param_1,&local_19c,0x194);
  pcVar9 = calloc_exref;
  if (MVar1 != 0) {
    return 1;
  }
  ppcVar2 = calloc(1,0x18);
  param_2->analog_desc = ppcVar2;
  ppcVar3 = calloc(1,0x18);
  param_2->analog_names = ppcVar3;
  ppcVar4 = calloc(1,0xc0);
  param_2->discrete_desc = ppcVar4;
  ppcVar5 = calloc(1,0xc0);
  param_2->discrete_names = ppcVar5;
  if ((((ppcVar2 != (char **)0x0) && (ppcVar3 != (char **)0x0)) && (ppcVar4 != (char **)0x0)) &&
     (ppcVar5 != (char **)0x0)) {
    piVar6 = calloc(1,0xec);
    if (piVar6 == (int *)0x0) {
      return 1;
    }
    *piVar6 = param_1;
    param_2->data = piVar6;
    iVar7 = GetStringFromRegistry(param_1,local_19c.szRegKey,param_2->long_name,0x40);
    if (iVar7 == 0) {
      sprintf(param_2->long_name,"Joystick %d",param_1 + 1);
    }
    sprintf(param_2->short_name,"joystick%d",param_1 + 1);
    SetJoystickClassName(param_2,(tagJOYCAPSA *)&local_19c);
    *ppcVar2 = xDesc;
    *ppcVar3 = xName;
    ppcVar2[1] = yDesc;
    ppcVar3[1] = yName;
    iVar7 = 2;
    if (((byte)local_19c.wCaps & 1) != 0) {
      iVar7 = 8;
      bVar11 = true;
      pcVar8 = param_2->class_name;
      pcVar10 = "tracker";
      do {
        if (iVar7 == 0) break;
        iVar7 = iVar7 + -1;
        bVar11 = *pcVar8 == *pcVar10;
        pcVar8 = pcVar8 + 1;
        pcVar10 = pcVar10 + 1;
      } while (bVar11);
      iVar7 = 3;
      pcVar9 = calloc_exref;
      if (bVar11) {
        ppcVar2[2] = rollDesc;
        ppcVar3[2] = rollName;
      }
      else {
        ppcVar2[2] = zDesc;
        ppcVar3[2] = zName;
      }
    }
    if (((byte)local_19c.wCaps & 2) != 0) {
      ppcVar2[iVar7] = rDesc;
      ppcVar3[iVar7] = rName;
      iVar7 = iVar7 + 1;
    }
    if (((byte)local_19c.wCaps & 4) != 0) {
      ppcVar2[iVar7] = uDesc;
      ppcVar3[iVar7] = uName;
      iVar7 = iVar7 + 1;
    }
    if (((byte)local_19c.wCaps & 8) != 0) {
      ppcVar2[iVar7] = vDesc;
      ppcVar3[iVar7] = vName;
      iVar7 = iVar7 + 1;
    }
    param_2->num_analog = iVar7;
    pcVar8 = (char *)(*pcVar9)(1,0x180);
    *ppcVar4 = pcVar8;
    pcVar8 = (char *)(*pcVar9)(1,0x180);
    *ppcVar5 = pcVar8;
    if ((*ppcVar4 != (char *)0x0) && (pcVar8 != (char *)0x0)) {
      if (0 < (int)local_19c.wNumButtons) {
        iVar7 = (int)ppcVar4 - (int)ppcVar5;
        local_1a0 = 1;
        ppcVar2 = ppcVar5;
        do {
          sprintf(*(char **)(iVar7 + (int)ppcVar2),"Button %d",local_1a0);
          sprintf(*ppcVar2,"Button%d",local_1a0);
          ppcVar3 = ppcVar2 + 1;
          *(int *)(iVar7 + (int)ppcVar3) = *(int *)(iVar7 + (int)ppcVar2) + 0xc;
          *ppcVar3 = *ppcVar2 + 0xc;
          bVar11 = local_1a0 < (int)local_19c.wNumButtons;
          ppcVar2 = ppcVar3;
          local_1a0 = local_1a0 + 1;
        } while (bVar11);
      }
      if (((byte)local_19c.wCaps & 0x10) != 0) {
        ppcVar4[local_19c.wNumButtons] = hatUpDesc;
        ppcVar5[local_19c.wNumButtons] = hatUpName;
        ppcVar4[local_19c.wNumButtons + 1] = hatRtDesc;
        ppcVar5[local_19c.wNumButtons + 1] = hatRtName;
        ppcVar4[local_19c.wNumButtons + 2] = hatDnDesc;
        ppcVar5[local_19c.wNumButtons + 2] = hatDnName;
        ppcVar4[local_19c.wNumButtons + 3] = hatLfDesc;
        ppcVar5[local_19c.wNumButtons + 3] = hatLfName;
        local_19c.wNumButtons = local_19c.wNumButtons + 4;
      }
      ppcVar4[local_19c.wNumButtons] = xNegDesc;
      ppcVar5[local_19c.wNumButtons] = xNegName;
      ppcVar4[local_19c.wNumButtons + 1] = xPosDesc;
      ppcVar5[local_19c.wNumButtons + 1] = xPosName;
      ppcVar4[local_19c.wNumButtons + 2] = yNegDesc;
      ppcVar5[local_19c.wNumButtons + 2] = yNegName;
      ppcVar4[local_19c.wNumButtons + 3] = yPosDesc;
      ppcVar5[local_19c.wNumButtons + 3] = yPosName;
      iVar7 = local_19c.wNumButtons + 4;
      if (((byte)local_19c.wCaps & 1) != 0) {
        ppcVar4[iVar7] = zNegDesc;
        ppcVar5[iVar7] = zNegName;
        ppcVar4[local_19c.wNumButtons + 5] = zPosDesc;
        ppcVar5[local_19c.wNumButtons + 5] = zPosName;
        iVar7 = local_19c.wNumButtons + 6;
      }
      if (((byte)local_19c.wCaps & 2) != 0) {
        ppcVar4[iVar7] = rNegDesc;
        ppcVar5[iVar7] = rNegName;
        ppcVar4[iVar7 + 1] = rPosDesc;
        ppcVar5[iVar7 + 1] = rPosName;
        iVar7 = iVar7 + 2;
      }
      if (((byte)local_19c.wCaps & 4) != 0) {
        ppcVar4[iVar7] = uNegDesc;
        ppcVar5[iVar7] = uNegName;
        ppcVar4[iVar7 + 1] = uPosDesc;
        ppcVar5[iVar7 + 1] = uPosName;
        iVar7 = iVar7 + 2;
      }
      if (((byte)local_19c.wCaps & 8) != 0) {
        ppcVar4[iVar7] = vNegDesc;
        ppcVar5[iVar7] = vNegName;
        ppcVar4[iVar7 + 1] = vPosDesc;
        ppcVar5[iVar7 + 1] = vPosName;
        iVar7 = iVar7 + 2;
      }
      param_2->num_discrete = iVar7;
      return 0;
    }
  }
  giddi_close(param_2);
  return 1;
}
