/*
 * Entry: 004be436
 * Name: BettyVoice::SatelliteActivated
 * Namespace: BettyVoice
 * Signature: void SatelliteActivated(BettyVoice * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall BettyVoice::SatelliteActivated(BettyVoice *this)

{
  QueueVoice(this,SATELLITE_ACTIVATED);
  return;
}
