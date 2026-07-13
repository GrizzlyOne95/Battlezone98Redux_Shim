/*
 * Entry: 00471582
 * Name: DoAudio
 * Namespace: Global
 * Signature: _gas_object * DoAudio(AUDIOTYPES param_1, _OBJ76 * param_2, GAS_CTRL * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_gas_object * __cdecl DoAudio(AUDIOTYPES param_1,_OBJ76 *param_2,GAS_CTRL *param_3)

{
  tagENTITY *ptVar1;
  int iVar2;
  _gas_object *p_Var3;
  GAS_PREP_INFO *pGVar4;
  char *pcVar5;
  GAS_PREP_INFO local_24;
  _gas_object *local_8;
  
  pGVar4 = (GAS_PREP_INFO *)0x0;
  local_8 = (_gas_object *)0x0;
  if ((param_2 == (_OBJ76 *)0x0) &&
     ((ptVar1 = get_user_entity(), ptVar1 == (tagENTITY *)0x0 ||
      (param_2 = ptVar1->obj76, param_2 == (_OBJ76 *)0x0)))) {
    return (_gas_object *)0x0;
  }
  if ((int)param_1 < 9) {
    if (param_1 == AUDIO_VHCL_FIRE_MACHINE_GUN) {
      pcVar5 = "vmgun.wav";
    }
    else {
      if (param_1 != AUDIO_VHCL_LANDING) {
        if (param_1 == AUDIO_VHCL_VHCL_COLLISION) {
          pcVar5 = "vvcoll.wav";
        }
        else if (param_1 == AUDIO_VHCL_BULLET_COLLISION) {
          pcVar5 = "vbcoll.wav";
        }
        else {
          if (param_1 != AUDIO_VHCL_EXPLOSION) {
            return local_8;
          }
          pcVar5 = "vexplode.wav";
        }
        DoAudioFixedLoc(pcVar5,param_2,param_3);
        return local_8;
      }
      iVar2 = is_user_vhcl(param_2);
      if (iVar2 == 0) {
        return local_8;
      }
      pcVar5 = "vland.wav";
    }
  }
  else if (param_1 == AUDIO_VHCL_FIRE_MISSLE) {
    pcVar5 = "vmissile.wav";
  }
  else if (param_1 == AUDIO_VHCL_SKID_START) {
    iVar2 = is_user_vhcl(param_2);
    if (iVar2 == 0) {
      return local_8;
    }
    pcVar5 = "vskid.wav";
    p_Var3 = FindGASObject("vskid.wav",param_2);
    if (p_Var3 != (_gas_object *)0x0) {
      return local_8;
    }
    pGVar4 = &local_24;
    InitGASPrep(pGVar4);
    local_24.loopMode = 1;
  }
  else {
    if (param_1 == AUDIO_VHCL_SKID_STOP) {
      iVar2 = is_user_vhcl(param_2);
      if (iVar2 == 0) {
        return local_8;
      }
      local_8 = FindGASObject("vskid.wav",param_2);
      if (local_8 == (_gas_object *)0x0) {
        return (_gas_object *)0x0;
      }
      StopGASEvent(local_8);
      return local_8;
    }
    if (param_1 != AUDIO_SIGN_EXPLOSION) {
      return local_8;
    }
    pcVar5 = "vcsign.wav";
  }
  p_Var3 = StartGASEvent(pcVar5,param_2,param_3,pGVar4);
  return p_Var3;
}
