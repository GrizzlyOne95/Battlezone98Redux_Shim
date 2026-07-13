/*
 * Entry: 004736fc
 * Name: ClsnSounds
 * Namespace: Global
 * Signature: void ClsnSounds(CLSN_INFO * param_1, CLSN_INFO * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl ClsnSounds(CLSN_INFO *param_1,CLSN_INFO *param_2)

{
  float fVar1;
  float fVar2;
  float fVar3;
  int in_EAX;
  int iVar4;
  _OBJ76 *p_Var5;
  int unaff_EBX;
  char *pcVar6;
  
  iVar4 = is_user_vhcl(*(_OBJ76 **)(unaff_EBX + 4));
  if (iVar4 == 0) {
    iVar4 = is_user_vhcl(*(_OBJ76 **)(in_EAX + 4));
    if (iVar4 == 0) {
      return;
    }
    p_Var5 = *(_OBJ76 **)(in_EAX + 4);
    iVar4 = *(int *)(unaff_EBX + 4);
  }
  else {
    p_Var5 = *(_OBJ76 **)(unaff_EBX + 4);
    iVar4 = *(int *)(in_EAX + 4);
  }
  iVar4 = *(int *)(iVar4 + 0xac);
  fVar1 = *(float *)(unaff_EBX + 0x60) - *(float *)(in_EAX + 0x60);
  fVar2 = *(float *)(unaff_EBX + 100) - *(float *)(in_EAX + 100);
  fVar3 = *(float *)(unaff_EBX + 0x68) - *(float *)(in_EAX + 0x68);
  fVar1 = fVar2 * fVar2 + fVar3 * fVar3 + fVar1 * fVar1;
  if (iVar4 == 1) {
LAB_004737fa:
    if (1600.0 < fVar1) {
      pcVar6 = "vvch2.wav";
      goto LAB_00473830;
    }
    if (500.0 < fVar1) {
      pcVar6 = "vvcre2.wav";
      goto LAB_00473830;
    }
LAB_00473798:
    if (fVar1 <= 25.0) {
      return;
    }
    pcVar6 = "vvcbb3.wav";
  }
  else {
    if (iVar4 < 3) {
LAB_004737ca:
      if (500.0 < fVar1) {
        pcVar6 = "vnvcs3.wav";
      }
      else {
        if (fVar1 <= 25.0) {
          return;
        }
        pcVar6 = "vnvcs1.wav";
      }
      goto LAB_00473830;
    }
    if (iVar4 < 5) {
      return;
    }
    if (iVar4 != 5) {
      if (iVar4 == 6) goto LAB_004737fa;
      if (iVar4 != 7) {
        if (iVar4 != 10) goto LAB_004737ca;
        goto LAB_00473798;
      }
    }
    if (fVar1 <= 25.0) {
      return;
    }
    pcVar6 = "vnvco3.wav";
  }
LAB_00473830:
  DoAudioNew(pcVar6,p_Var5,(GAS_CTRL *)0x0);
  return;
}
