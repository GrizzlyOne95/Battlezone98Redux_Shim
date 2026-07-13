/*
 * Entry: 004bcea2
 * Name: giddi_read_channels
 * Namespace: Global
 * Signature: int giddi_read_channels(JOYSTICK_DATA * param_1, long * param_2, long * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl giddi_read_channels(JOYSTICK_DATA *param_1,long *param_2,long *param_3)

{
  long *plVar1;
  HWND pHVar2;
  MMRESULT MVar3;
  ulong uVar4;
  long lVar5;
  int iVar6;
  uint uVar7;
  long unaff_ESI;
  long unaff_EDI;
  long *plVar8;
  char *pcVar9;
  joyinfoex_tag local_38;
  
  plVar1 = param_3;
  if ((param_3 == (long *)0x0) || (param_2 == (long *)0x0)) {
    return 1;
  }
  plVar8 = param_2;
  for (iVar6 = 6; iVar6 != 0; iVar6 = iVar6 + -1) {
    *plVar8 = 0;
    plVar8 = plVar8 + 1;
  }
  param_3[1] = 0;
  *param_3 = 0;
  pHVar2 = GetFocus();
  if (pHVar2 != (HWND)Device.hwndApp) {
    return 0;
  }
  memset(&local_38,0,0x34);
  local_38.dwFlags = param_1->flags;
  local_38.dwSize = 0x34;
  MVar3 = joyGetPosEx(param_1->id,&local_38);
  if (MVar3 != 0) {
    if (MVar3 == 2) {
      pcVar9 = "Bad Joystick Device ID";
    }
    else if (MVar3 == 6) {
      pcVar9 = "No Joystick Driver";
    }
    else if (MVar3 == 0xb) {
      pcVar9 = "Invalid parameter to Joystick driver";
    }
    else if (MVar3 == 0xa7) {
      pcVar9 = "Joystick may be unplugged";
    }
    else {
      pcVar9 = "Unkown joystick error";
    }
    DEBUG_systemError(pcVar9);
    return 0;
  }
  *param_3 = local_38.dwButtons;
  if ((param_1->flags & 0x40) == 0) goto LAB_004bcfea;
  if (local_38.dwPOV < 0x4651) {
    if (local_38.dwPOV == 18000) {
LAB_004bcfdf:
      uVar7 = param_1->hatDnMask;
      uVar4 = param_1->hatDnIndex;
    }
    else {
      if (local_38.dwPOV != 0) {
        if (local_38.dwPOV == 0x1194) {
          uVar4 = param_1->hatRtIndex;
          uVar7 = param_1->hatRtMask;
          goto LAB_004bcf9f;
        }
        if (local_38.dwPOV == 9000) {
          uVar4 = param_1->hatRtIndex;
          uVar7 = param_1->hatRtMask;
          goto LAB_004bcfe5;
        }
        if (local_38.dwPOV != 0x34bc) goto LAB_004bcfea;
        uVar4 = param_1->hatRtIndex;
        uVar7 = param_1->hatRtMask;
        goto LAB_004bcfda;
      }
LAB_004bcfa4:
      uVar4 = param_1->hatUpIndex;
      uVar7 = param_1->hatUpMask;
    }
  }
  else {
    if (local_38.dwPOV == 0x57e4) {
      uVar4 = param_1->hatLfIndex;
      uVar7 = param_1->hatLfMask;
LAB_004bcfda:
      param_3[uVar4] = param_3[uVar4] | uVar7;
      goto LAB_004bcfdf;
    }
    if (local_38.dwPOV != 27000) {
      if (local_38.dwPOV != 0x7b0c) goto LAB_004bcfea;
      uVar4 = param_1->hatLfIndex;
      uVar7 = param_1->hatLfMask;
LAB_004bcf9f:
      param_3[uVar4] = param_3[uVar4] | uVar7;
      goto LAB_004bcfa4;
    }
    uVar4 = param_1->hatLfIndex;
    uVar7 = param_1->hatLfMask;
  }
LAB_004bcfe5:
  param_3[uVar4] = param_3[uVar4] | uVar7;
LAB_004bcfea:
  lVar5 = joystick_scale(param_1->xMin,unaff_EDI,unaff_ESI);
  *param_2 = lVar5;
  if (local_38.dwXpos < param_1->xNegThresh) {
    param_3[param_1->xNegIndex] = param_3[param_1->xNegIndex] | param_1->xNegMask;
  }
  if (param_1->xPosThresh < local_38.dwXpos) {
    param_3[param_1->xPosIndex] = param_3[param_1->xPosIndex] | param_1->xPosMask;
  }
  lVar5 = joystick_scale(param_1->yMin,unaff_EDI,unaff_ESI);
  param_2[1] = lVar5;
  if (local_38.dwYpos < param_1->yNegThresh) {
    param_3[param_1->yNegIndex] = param_3[param_1->yNegIndex] | param_1->yNegMask;
  }
  if (param_1->yPosThresh < local_38.dwYpos) {
    param_3[param_1->yPosIndex] = param_3[param_1->yPosIndex] | param_1->yPosMask;
  }
  Joy_DebugUpdate(local_38.dwXpos,local_38.dwYpos,*param_2,param_2[1]);
  param_3 = (long *)0x2;
  if ((param_1->flags & 4) != 0) {
    lVar5 = joystick_scale(param_1->zMin,unaff_EDI,unaff_ESI);
    param_2[2] = lVar5;
    param_3 = (long *)0x3;
    if (local_38.dwZpos < param_1->zNegThresh) {
      plVar1[param_1->zNegIndex] = plVar1[param_1->zNegIndex] | param_1->zNegMask;
    }
    if (param_1->zPosThresh < local_38.dwZpos) {
      plVar1[param_1->zPosIndex] = plVar1[param_1->zPosIndex] | param_1->zPosMask;
    }
  }
  if ((param_1->flags & 8) != 0) {
    lVar5 = joystick_scale(param_1->rMin,unaff_EDI,unaff_ESI);
    plVar8 = (long *)((int)param_3 + 1);
    param_2[(int)param_3] = lVar5;
    if (local_38.dwRpos < param_1->rNegThresh) {
      plVar1[param_1->rNegIndex] = plVar1[param_1->rNegIndex] | param_1->rNegMask;
    }
    param_3 = plVar8;
    if (param_1->rPosThresh < local_38.dwRpos) {
      plVar1[param_1->rPosIndex] = plVar1[param_1->rPosIndex] | param_1->rPosMask;
    }
  }
  if ((param_1->flags & 0x10) != 0) {
    lVar5 = joystick_scale(param_1->uMin,unaff_EDI,unaff_ESI);
    plVar8 = (long *)((int)param_3 + 1);
    param_2[(int)param_3] = lVar5;
    if (local_38.dwUpos < param_1->uNegThresh) {
      plVar1[param_1->uNegIndex] = plVar1[param_1->uNegIndex] | param_1->uNegMask;
    }
    param_3 = plVar8;
    if (param_1->uPosThresh < local_38.dwUpos) {
      plVar1[param_1->uPosIndex] = plVar1[param_1->uPosIndex] | param_1->uPosMask;
    }
  }
  if ((param_1->flags & 0x20) != 0) {
    lVar5 = joystick_scale(param_1->vMin,unaff_EDI,unaff_ESI);
    param_2[(int)param_3] = lVar5;
    if (local_38.dwVpos < param_1->vNegThresh) {
      plVar1[param_1->vNegIndex] = plVar1[param_1->vNegIndex] | param_1->vNegMask;
    }
    if (param_1->vPosThresh < local_38.dwVpos) {
      plVar1[param_1->vPosIndex] = plVar1[param_1->vPosIndex] | param_1->vPosMask;
    }
  }
  return 0;
}
