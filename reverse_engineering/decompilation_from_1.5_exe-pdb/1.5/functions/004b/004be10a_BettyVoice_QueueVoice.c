/*
 * Entry: 004be10a
 * Name: BettyVoice::QueueVoice
 * Namespace: BettyVoice
 * Signature: void QueueVoice(BettyVoice * this, VoiceEvent param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall BettyVoice::QueueVoice(BettyVoice *this,VoiceEvent param_1)

{
  *this->messageLast = this->VoiceSound[param_1];
  this->messageLast = this->messageLast + 1;
  if (&this->messageFirst <= this->messageLast) {
    this->messageLast = this->messageQueue;
  }
  return;
}
