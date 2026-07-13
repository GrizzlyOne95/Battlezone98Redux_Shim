/*
 * Entry: 004baf9e
 * Name: NextInputs
 * Namespace: Global
 * Signature: void NextInputs(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl NextInputs(void)

{
  ANALOG_SINK *pAVar1;
  int *piVar2;
  long extraout_EAX;
  uint uVar3;
  void *pvVar4;
  int iVar5;
  void **ppvVar6;
  ANALOG_SINK **ppAVar7;
  GIDDI_VALS *pGVar8;
  DISCRETE_STATE *pDVar9;
  long **pplVar10;
  int iVar11;
  short local_c [2];
  int local_8;
  
  local_8 = 0;
  if (0 < num_analog_controls) {
    pplVar10 = &analog_map[0].from;
    do {
      pAVar1 = (ANALOG_SINK *)pplVar10[3];
      if ((pAVar1->reset_discrete == (char *)0x0) || (*pAVar1->reset_discrete == '\0')) {
        if ((pAVar1->set_discrete != (char *)0x0) && (*pAVar1->set_discrete != '\0')) {
          *pAVar1->delta = 0;
          _ftol2_sse();
          pAVar1->current = extraout_EAX;
        }
      }
      else {
        if ((*pplVar10 != (long *)0x0) &&
           (iVar11 = ((ANALOG_SOURCE *)(pplVar10 + -2))->device, input_enable[iVar11] != 0)) {
          (*input_funcs[iVar11]->reset)(input_desc[iVar11].data,(int)pplVar10[-1]);
        }
        pAVar1->current = pAVar1->zero;
        *pAVar1->delta = 0;
        pplVar10[1] = (long *)0x0;
      }
      iVar11 = num_analog_controls;
      local_8 = local_8 + 1;
      pplVar10 = pplVar10 + 0x20;
      pAVar1->simulated = '\0';
    } while (local_8 < iVar11);
  }
  uVar3 = 0;
  do {
    if (*(int *)((int)&control_name[0].type + uVar3) != 0) {
      **(undefined1 **)((int)&control_name[0].field + uVar3) = 0;
    }
    uVar3 = uVar3 + 0x20;
  } while (uVar3 < 0xd40);
  if ((inputCalled == 0) && (pvVar4 = TextInput_IsActive(), pvVar4 == (void *)0x0)) {
    iVar11 = 0;
    if (0 < num_input_devices) {
      ppvVar6 = &input_desc[0].data;
      pGVar8 = invals;
      do {
        if ((input_enable[iVar11] != 0) &&
           ((iVar11 != kbd_num || (pvVar4 = TextInput_IsActive(), pvVar4 == (void *)0x0)))) {
          (*input_funcs[iVar11]->read_channels)(*ppvVar6,pGVar8->analog,pGVar8->discrete);
        }
        iVar11 = iVar11 + 1;
        pGVar8 = pGVar8 + 1;
        ppvVar6 = ppvVar6 + 0x1d;
      } while (iVar11 < num_input_devices);
    }
    if (0 < num_discrete_controls) {
      pDVar9 = discrete_map[0].chord;
      iVar11 = num_discrete_controls;
      do {
        if ((inputs_enabled != 0) || (pDVar9[-1].type != 0)) {
          iVar5 = test_chord(pDVar9[-1].mask,pDVar9);
          if ((*(char *)&pDVar9[-1].from == '\0') || (*(char *)((int)&pDVar9[-1].from + 1) == '\0'))
          {
            *(byte *)pDVar9[-2].type = *(byte *)pDVar9[-2].type | (byte)iVar5;
          }
          *(byte *)((int)&pDVar9[-1].from + 1) = (byte)iVar5;
        }
        pDVar9 = (DISCRETE_STATE *)&pDVar9[9].mask;
        iVar11 = iVar11 + -1;
      } while (iVar11 != 0);
    }
    local_8 = 0;
    if (0 < num_analog_controls) {
      ppAVar7 = &analog_map[0].sink;
      do {
        if ((inputs_enabled != 0) || (ppAVar7[0x1a] != (ANALOG_SINK *)0x0)) {
          iVar11 = simulate_analog((ANALOG_SOURCE *)(ppAVar7 + -5));
          if ((iVar11 == 0) && (piVar2 = (int *)ppAVar7[-3], piVar2 != (int *)0x0)) {
            iVar11 = test_chord((int)ppAVar7[1],(DISCRETE_STATE *)(ppAVar7 + 2));
            if (iVar11 == 0) {
              iVar11 = 0;
            }
            else {
              iVar11 = (int)ppAVar7[-1] * *piVar2;
            }
            pAVar1 = *ppAVar7;
            if (ppAVar7[-2] == (ANALOG_SINK *)iVar11) {
              if (&pAVar1->current == pAVar1->delta) {
                pAVar1->current = iVar11;
              }
            }
            else {
              pAVar1->current = iVar11;
            }
            ppAVar7[-2] = (ANALOG_SINK *)iVar11;
          }
          pAVar1 = *ppAVar7;
          iVar11 = pAVar1->current;
          if (0x10000 < iVar11) {
            iVar11 = 0x10000;
          }
          if (iVar11 < -0x10000) {
            iVar11 = -0x10000;
          }
          *pAVar1->to = ((iVar11 + 0x10000) * pAVar1->range) / 2 + pAVar1->min >>
                        (pAVar1->shift & 0x1fU);
        }
        local_8 = local_8 + 1;
        ppAVar7 = ppAVar7 + 0x20;
      } while (local_8 < num_analog_controls);
    }
  }
  else {
    ClearKeyboardState();
  }
  if (input_enable[kbd_num] == 0) {
    local_c[0] = 0;
    local_c[1] = 0;
  }
  else {
    (*input_funcs[kbd_num]->read_key)(local_c);
  }
  user_controls.key = local_c[0];
  InputDebugDisplay();
  return;
}
