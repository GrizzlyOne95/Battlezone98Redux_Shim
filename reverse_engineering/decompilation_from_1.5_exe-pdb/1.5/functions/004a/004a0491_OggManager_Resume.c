/*
 * Entry: 004a0491
 * Name: OggManager::Resume
 * Namespace: OggManager
 * Signature: bool Resume(int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __cdecl OggManager::Resume(int param_1)

{
  OggVorbis_File *pOVar1;
  OggVorbis_File *pOVar2;
  char *pcVar3;
  int iVar4;
  
  if ((uint)param_1 < 8) {
    if (gOggStreams[param_1].m_bPlaying != false) {
      EnterCriticalSection((LPCRITICAL_SECTION)&gOggStreams[param_1].m_OggMutex);
      if (gOggStreams[param_1].m_pStreamingSound == (CStreamingOggSound *)0x0) {
        pcVar3 = 
        "UHOH - OggManager::Resume index %d has NO pStreamingSound but is playing. Attempting to fix\n"
        ;
        iVar4 = param_1;
        Trace(
             "UHOH - OggManager::Resume index %d has NO pStreamingSound but is playing. Attempting to fix\n"
             );
        pOVar1 = &gOggStreams[param_1].m_vf;
        pOVar2 = pOVar1;
        ov_clear(pOVar1);
        gOggStreams[param_1].m_bPlaying = false;
        memset(pOVar1,0,0x2d0,pOVar2,pcVar3,iVar4);
      }
      else {
        CSound::Play((CSound *)gOggStreams[param_1].m_pStreamingSound,0,1);
      }
      LeaveCriticalSection((LPCRITICAL_SECTION)&gOggStreams[param_1].m_OggMutex);
      return true;
    }
    Trace("OggManager::Resume index %d is not playing");
  }
  return false;
}
