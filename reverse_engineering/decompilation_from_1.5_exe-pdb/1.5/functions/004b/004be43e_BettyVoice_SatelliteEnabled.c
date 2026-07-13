/*
 * Entry: 004be43e
 * Name: BettyVoice::SatelliteEnabled
 * Namespace: BettyVoice
 * Signature: void SatelliteEnabled(BettyVoice * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall BettyVoice::SatelliteEnabled(BettyVoice *this)

{
  QueueVoice(this,SATELLITE_ENABLED);
  return;
}
