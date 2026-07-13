/*
 * Entry: 004be155
 * Name: BettyVoice::Simulate
 * Namespace: BettyVoice
 * Signature: void Simulate(BettyVoice * this, float param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __thiscall BettyVoice::Simulate(BettyVoice *this,float param_1)

{
  char ***pppcVar1;
  char *pcVar2;
  bool bVar3;
  int iVar4;
  _gas_object *p_Var5;
  GAS_PREP_INFO local_50;
  GAS_CTRL local_34;
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  if ((((voiceReady) && (pppcVar1 = &this->messageFirst, this->messageLast != *pppcVar1)) &&
      (bVar3 = IsAudioMessagePlaying(), !bVar3)) && (iVar4 = isCineractive(), iVar4 == 0)) {
    InitGASCtrl(&local_34);
    local_34.eofCallback = BettyVoiceDone;
    local_34.flags = 5;
    InitGASPrep(&local_50);
    local_50.pri = 100;
    pcVar2 = **pppcVar1;
    *pppcVar1 = *pppcVar1 + 1;
    p_Var5 = StartGASEvent(pcVar2,(_OBJ76 *)0x0,&local_34,&local_50);
    if (p_Var5 != (_gas_object *)0x0) {
      voiceReady = false;
    }
    if (pppcVar1 <= *pppcVar1) {
      *pppcVar1 = this->messageQueue;
    }
  }
  return;
}
