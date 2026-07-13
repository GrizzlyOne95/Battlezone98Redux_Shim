/*
 * Entry: 00452350
 * Name: AllocStrip
 * Namespace: Global
 * Signature: Strip * AllocStrip(bool param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Strip * __cdecl AllocStrip(bool param_1)

{
  Strip **ppSVar1;
  Strip *pSVar2;
  
  if (((int)freeStrips->_Mylast - (int)freeStrips->_Myfirst & 0xfffffffcU) == 0) {
    if (0xffff < StripCount) {
                    /* WARNING: Subroutine does not return */
      exit(1);
    }
    pSVar2 = AllStrips + StripCount;
    StripCount = StripCount + 1;
  }
  else {
    ppSVar1 = std::vector<Strip_*,std::allocator<Strip_*>_>::back(freeStrips);
    pSVar2 = *ppSVar1;
    if (((int)freeStrips->_Mylast - (int)freeStrips->_Myfirst & 0xfffffffcU) != 0) {
      freeStrips->_Mylast = freeStrips->_Mylast + -1;
    }
  }
  pSVar2->g = 0.0;
  pSVar2->link = false;
  pSVar2->open = false;
  pSVar2->backward = false;
  pSVar2->detour = false;
  pSVar2->visited = false;
  pSVar2->prev = (Strip *)0x0;
  pSVar2->next = (Strip *)0x0;
  if (param_1) {
    stripSeqNo = stripSeqNo + 1;
    pSVar2->seqNo = stripSeqNo;
  }
  return pSVar2;
}
