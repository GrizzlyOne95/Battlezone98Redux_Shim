/*
 * Entry: 004be394
 * Name: BettyVoice::HullWarning
 * Namespace: BettyVoice
 * Signature: void HullWarning(BettyVoice * this, GameObject * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall BettyVoice::HullWarning(BettyVoice *this,GameObject *param_1)

{
  VoiceEvent VVar1;
  
  if (param_1 == GameObject::userObject) {
    VVar1 = USER_HULL_CRITICAL;
  }
  else {
    VVar1 = UNIT_HULL_CRITICAL;
  }
  QueueVoice(this,VVar1);
  return;
}
