/*
 * Entry: 004be446
 * Name: BettyVoice::PilotDepleted
 * Namespace: BettyVoice
 * Signature: void PilotDepleted(BettyVoice * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall BettyVoice::PilotDepleted(BettyVoice *this)

{
  QueueVoice(this,PILOTS_DEPLETED);
  return;
}
