/*
 * Entry: 004a027a
 * Name: OggManager::GetDSBuffer
 * Namespace: OggManager
 * Signature: IDirectSoundBuffer * GetDSBuffer(int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

IDirectSoundBuffer * __cdecl OggManager::GetDSBuffer(int param_1)

{
  undefined4 *puVar1;
  char *pcVar2;
  
  if ((uint)param_1 < 8) {
    if (gOggStreams[param_1].m_bPlaying == false) {
      pcVar2 = "OggManager::GetDSBuffer index %d is not playing";
    }
    else {
      if (gOggStreams[param_1].m_pStreamingSound != (CStreamingOggSound *)0x0) {
        puVar1 = (undefined4 *)(gOggStreams[param_1].m_pStreamingSound)->_padding_;
        if (puVar1 == (undefined4 *)0x0) {
          return (IDirectSoundBuffer *)0x0;
        }
        return (IDirectSoundBuffer *)*puVar1;
      }
      pcVar2 = "OggManager::GetDSBuffer index %d has no pStreamingSound";
    }
    Trace(pcVar2);
  }
  return (IDirectSoundBuffer *)0x0;
}
