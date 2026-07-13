/*
 * Entry: 00482128
 * Name: ShellStartGASEvent
 * Namespace: Global
 * Signature: int ShellStartGASEvent(uchar * param_1, long param_2, long param_3, long param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

int __cdecl ShellStartGASEvent(uchar *param_1,long param_2,long param_3,long param_4)

{
  _gas_object *p_Var1;
  long lVar2;
  _gas_object *unaff_ESI;
  GAS_CTRL *pGVar3;
  GAS_CTRL local_34;
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  if (GM != (GAS_MASTER *)0x0) {
    pGVar3 = &local_34;
    InitGASCtrl(pGVar3);
    local_34.rate = (float)param_4;
    local_34.volume = (float)param_2;
    local_34.pan = (float)param_3;
    p_Var1 = NewGASObject((char *)0x0,(_OBJ76 *)0x0,pGVar3,unaff_ESI);
    if (p_Var1 != (_gas_object *)0x0) {
      sprintf((p_Var1->gc).name,"%d%s",shellSoundNum,".wav");
      shellSoundNum = shellSoundNum + 1;
      if (100 < shellSoundNum) {
        shellSoundNum = 0;
      }
      p_Var1->flags = p_Var1->flags | 0x200;
      p_Var1->wavBuf = param_1;
      lVar2 = OpenGASObject(GM,p_Var1,(GAS_PREP_INFO *)0x0);
      if (lVar2 != 0) {
        return 1;
      }
      DeleteGASObject(p_Var1);
    }
  }
  return 0;
}
