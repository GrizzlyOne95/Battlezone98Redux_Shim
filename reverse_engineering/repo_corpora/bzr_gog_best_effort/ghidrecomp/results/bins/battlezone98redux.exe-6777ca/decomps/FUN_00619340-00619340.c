
/* WARNING: Function: __alloca_probe_16 replaced with injection: alloca_probe */
/* WARNING (jumptable): Unable to track spacebase fully for stack */
/* WARNING: Unable to track spacebase fully for stack */

void FUN_00619340(HWND param_1,uint param_2,WPARAM param_3,HRAWINPUT param_4)

{
  UINT UVar1;
  int iVar2;
  undefined4 *puVar3;
  HANDLE pvVar4;
  undefined1 *puVar5;
  undefined1 *puVar6;
  undefined4 *puVar7;
  undefined8 uVar8;
  undefined4 uStackY_ac;
  DWORD dwPriorityClass;
  tagPOINT local_4c;
  undefined1 *local_44;
  undefined4 local_40;
  undefined4 local_3c;
  BOOL local_38;
  int local_34;
  uint local_30;
  uint local_2c;
  HRAWINPUT local_28;
  int local_24;
  int *local_20;
  UINT local_1c;
  int local_18;
  uint local_14;
  uint local_10;
  uint local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  if (param_2 != 0x104) goto switchD_0061937d_caseD_e;
  local_18 = param_3 - 0xd;
  switch(param_3) {
  case 0xd:
    if (DAT_009183b0 == 0) {
      DAT_00920ed0 = 1;
    }
    else {
      uStackY_ac = 0x6193c3;
      CallWindowProcA(DAT_00918400,param_1,0x104,param_3,(LPARAM)param_4);
    }
    goto LAB_00619b42;
  case 0x12:
    if (DAT_008fe240 != 1) goto LAB_00619b42;
    break;
  case 0x1b:
  case 0x20:
    goto LAB_00619b42;
  }
switchD_0061937d_caseD_e:
  if (DAT_009183b0 == 0) {
    if ((param_2 == 0x100) || (param_2 == 0x101)) {
      local_30 = (uint)(param_2 == 0x100);
      local_2c = (uint)(((int)param_4 >> 0x1e & 1U) != 0);
      local_14 = (int)param_4 >> 0x10 & 0xff;
      if ((local_14 != 0) && (((uint)param_4 >> 0x10 & 0x100) != 0)) {
        local_14 = FUN_00434bd0();
      }
      FUN_005d4f10();
    }
    if (param_2 == 0x102) {
      FUN_005d5080();
    }
  }
  if (param_2 == 0xff) {
    if (DAT_009183b0 == 0) {
      uStackY_ac = 0x619508;
      GetRawInputData(param_4,0x10000003,(LPVOID)0x0,&local_1c,0x10);
      iVar2 = -local_1c;
      local_44 = &stack0xffffff6c + iVar2;
      local_20 = (int *)(&stack0xffffff6c + iVar2);
      *(undefined4 *)(&stack0xffffff68 + iVar2) = 0x10;
      *(UINT **)(&stack0xffffff64 + iVar2) = &local_1c;
      *(int **)(&stack0xffffff60 + iVar2) = local_20;
      *(undefined4 *)(&stack0xffffff5c + iVar2) = 0x10000003;
      *(HRAWINPUT *)(&stack0xffffff58 + iVar2) = param_4;
      puVar5 = (undefined1 *)((int)&uStackY_ac + iVar2);
      *(undefined4 *)((int)&uStackY_ac + iVar2) = 0x619532;
      UVar1 = GetRawInputData(*(HRAWINPUT *)(&stack0xffffff58 + iVar2),
                              *(UINT *)(&stack0xffffff5c + iVar2),
                              *(LPVOID *)(&stack0xffffff60 + iVar2),
                              *(PUINT *)(&stack0xffffff64 + iVar2),
                              *(UINT *)(&stack0xffffff68 + iVar2));
      puVar6 = puVar5;
      if (UVar1 != local_1c) {
        *(char **)(puVar5 + -4) = "GetRawInputData does not return correct size !\n";
        puVar6 = puVar5 + -8;
        *(undefined4 *)(puVar5 + -8) = 0x619542;
        OutputDebugStringA(*(LPCSTR *)(puVar5 + -4));
      }
      if ((*local_20 == 0) && ((DAT_008fe240 == 1 || (DAT_008fe240 == 2)))) {
        *(int **)(puVar6 + -4) = local_20 + 4;
        *(undefined4 *)(puVar6 + -8) = 0x619568;
        FUN_004357d0();
      }
    }
    else {
      uStackY_ac = 0x6194ec;
      CallWindowProcA(DAT_00918400,param_1,0xff,param_3,(LPARAM)param_4);
    }
    goto LAB_00619b42;
  }
  if ((0xff < param_2) && (param_2 < 0x10a)) {
    if (DAT_009183b0 == 0) {
      if (DAT_008fe240 == 2) {
        FUN_00619be0();
      }
      else if (DAT_008fe240 == 1) {
        if ((param_3 == 0x20) && (iVar2 = FUN_005d5270(), iVar2 != 0)) {
          FUN_0081e0c0();
          FUN_005d52b0();
        }
        local_24 = FUN_00823ce0();
        if (local_24 == 0) {
          FUN_00619be0();
        }
        else {
          local_34 = FUN_00823700();
          if (local_34 == 2) {
            FUN_00823390();
          }
        }
      }
      else {
        if ((param_3 == 0x20) && (iVar2 = FUN_005d5270(), iVar2 != 0)) {
          FUN_0081e0c0();
          FUN_005d52b0();
        }
        uStackY_ac = 0x619626;
        CallWindowProcA(DAT_00918400,param_1,param_2,param_3,(LPARAM)param_4);
      }
    }
    else {
      uStackY_ac = 0x6195b1;
      CallWindowProcA(DAT_00918400,param_1,param_2,param_3,(LPARAM)param_4);
    }
    goto LAB_00619b42;
  }
  if ((0x1ff < param_2) && (param_2 < 0x20f)) {
    if (DAT_009183b0 == 0) {
      if ((DAT_008fe240 == 1) || (DAT_008fe240 == 2)) {
        if (DAT_00918424 == 0) {
          FUN_00435400();
        }
      }
      else {
        FUN_00435240();
      }
    }
    else {
      uStackY_ac = 0x6196e5;
      CallWindowProcA(DAT_00918400,param_1,param_2,param_3,(LPARAM)param_4);
    }
    goto LAB_00619b42;
  }
  local_c = param_2;
  if (0x10 < param_2) {
    if (param_2 < 0x2e1) {
      if (param_2 == 0x2e0) {
        FUN_006835e0();
      }
      else {
        if (param_2 == 0x1c) {
          if (param_3 == 0) {
            if (DAT_008eaaa4 != 0) {
              DAT_008eaaa4 = 0;
              if (DAT_009183b8 != 0) {
                ShowWindow(param_1,6);
              }
              if ((DAT_008fe240 == 1) || (DAT_008fe240 == 2)) {
                iVar2 = FUN_00572a70();
                if (iVar2 == 0) {
                  FUN_00437bc0();
                  FUN_00822a70();
                }
                dwPriorityClass = 0x20;
                pvVar4 = GetCurrentProcess();
                SetPriorityClass(pvVar4,dwPriorityClass);
                iVar2 = 0;
                pvVar4 = GetCurrentThread();
                SetThreadPriority(pvVar4,iVar2);
                FUN_00624110();
              }
            }
          }
          else if (DAT_008eaaa4 == 0) {
            DAT_008eaaa4 = 1;
            if (DAT_009183b8 != 0) {
              ShowWindow(param_1,9);
            }
            if ((DAT_008fe240 == 1) || (DAT_008fe240 == 2)) {
              iVar2 = FUN_00572a70();
              if ((iVar2 == 0) && (DAT_008fe240 != 2)) {
                FUN_00437bd0();
                FUN_00822ab0();
              }
              FUN_00434f20();
            }
            FUN_00624110();
          }
          uStackY_ac = 0x619a1a;
          CallWindowProcA(DAT_00918400,param_1,0x1c,param_3,(LPARAM)param_4);
          goto LAB_00619b42;
        }
        if (param_2 == 0x24) {
          local_28 = param_4;
          param_4[6].unused = 0x400;
          param_4[7].unused = 0x2d0;
          goto LAB_00619b42;
        }
      }
    }
    else if (param_2 == 0x401) {
      FUN_007c69c0();
      goto LAB_00619b42;
    }
    goto switchD_00619767_caseD_2;
  }
  if (param_2 == 0x10) {
    iVar2 = FUN_00434160();
    if (iVar2 != 9) {
      FUN_0081e1e0();
      FUN_00434170();
    }
    FUN_005d4ee0();
    goto switchD_00619767_caseD_2;
  }
  local_c = param_2 - 1;
  switch(local_c) {
  case 0:
    DAT_02cf44a0 = param_1;
    break;
  case 1:
    iVar2 = FUN_00434160();
    if (iVar2 != 9) {
      FUN_0081e1e0();
      FUN_00434170();
    }
    break;
  case 4:
    FUN_006835e0();
    uVar8 = FUN_00437330();
    DAT_02cecf04 = (undefined4)((ulonglong)uVar8 >> 0x20);
    DAT_02cecf00 = (undefined4)uVar8;
    local_40 = DAT_02cecf00;
    local_3c = DAT_02cecf04;
    puVar3 = (undefined4 *)FUN_00689f10();
    puVar7 = &DAT_02cecee0;
    for (iVar2 = 7; iVar2 != 0; iVar2 = iVar2 + -1) {
      *puVar7 = *puVar3;
      puVar3 = puVar3 + 1;
      puVar7 = puVar7 + 1;
    }
    uStackY_ac = 0x619856;
    FUN_00689fa0();
    FUN_005d4900();
    FUN_00624110();
    break;
  case 5:
    local_38 = GetCursorPos(&local_4c);
    if ((local_38 != 0) && (DAT_02cecefc != (WPARAM *)0x0)) {
      ScreenToClient((HWND)*DAT_02cecefc,&local_4c);
      FUN_005d4950();
    }
    uStackY_ac = 0x619921;
    CallWindowProcA(DAT_00918400,param_1,param_2,param_3,(LPARAM)param_4);
    goto LAB_00619b42;
  case 6:
    FUN_007c6910();
    FUN_00434f20();
    uStackY_ac = 0x619a46;
    CallWindowProcA(DAT_00918400,param_1,param_2,param_3,(LPARAM)param_4);
    goto LAB_00619b42;
  }
switchD_00619767_caseD_2:
  if (DAT_009183b0 == 0) {
    local_10 = param_2;
    if (param_2 < 0x310) {
      if (param_2 == 0x30f) goto LAB_00619b42;
      if (param_2 == 0xf) {
        if ((DAT_00915550 != 0) || ((DAT_008fe240 != 1 && (DAT_008fe240 != 2)))) {
          uStackY_ac = 0x619ae8;
          CallWindowProcA(DAT_00918400,param_1,0xf,param_3,(LPARAM)param_4);
          goto LAB_00619b42;
        }
      }
      else if (param_2 == 0x20) {
        FUN_00437620();
        goto LAB_00619b42;
      }
    }
    else if ((param_2 == 0x311) && ((DAT_02cecefc == (WPARAM *)0x0 || (param_3 != *DAT_02cecefc))))
    goto LAB_00619b42;
    uStackY_ac = 0x619b42;
    CallWindowProcA(DAT_00918400,param_1,param_2,param_3,(LPARAM)param_4);
  }
  else {
    uStackY_ac = 0x619a73;
    CallWindowProcA(DAT_00918400,param_1,param_2,param_3,(LPARAM)param_4);
  }
LAB_00619b42:
  FUN_0083e885();
  return;
}

