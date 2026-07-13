/*
 * Entry: 004a0392
 * Name: OggManager::Stop
 * Namespace: OggManager
 * Signature: bool Stop(int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __cdecl OggManager::Stop(int param_1)

{
  OggVorbis_File *pOVar1;
  CStreamingOggSound *this;
  bool bVar2;
  OggVorbis_File *pOVar3;
  char *pcVar4;
  int iVar5;
  
  if (((uint)param_1 < 8) && (gOggStreams[param_1].m_bPlaying != false)) {
    EnterCriticalSection((LPCRITICAL_SECTION)&gOggStreams[param_1].m_OggMutex);
    this = gOggStreams[param_1].m_pStreamingSound;
    if (this == (CStreamingOggSound *)0x0) {
      pcVar4 = 
      "OggManager::Stop index %d has NO pStreamingSound but is playing. Attempting to fix\n";
      iVar5 = param_1;
      Trace("OggManager::Stop index %d has NO pStreamingSound but is playing. Attempting to fix\n");
      pOVar1 = &gOggStreams[param_1].m_vf;
      pOVar3 = pOVar1;
      ov_clear(pOVar1);
      gOggStreams[param_1].m_bPlaying = false;
      memset(pOVar1,0,0x2d0,pOVar3,pcVar4,iVar5);
    }
    else {
      CSound::Stop((CSound *)this);
      CStreamingOggSound::Reset(gOggStreams[param_1].m_pStreamingSound);
    }
    LeaveCriticalSection((LPCRITICAL_SECTION)&gOggStreams[param_1].m_OggMutex);
    bVar2 = true;
  }
  else {
    bVar2 = false;
  }
  return bVar2;
}
