/*
 * Entry: 004b14f5
 * Name: CStreamingOggSound::DecodeToBuffer
 * Namespace: CStreamingOggSound
 * Signature: void DecodeToBuffer(CStreamingOggSound * this, void * param_1, ulong param_2, int param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
CStreamingOggSound::DecodeToBuffer(CStreamingOggSound *this,void *param_1,ulong param_2,int param_3)

{
  long lVar1;
  uint uVar2;
  uint unaff_EDI;
  int iVar3;
  
  uVar2 = 0;
  do {
    iVar3 = param_2 - uVar2;
    if ((this->m_bValid == 0) || (this->m_bFillWithSilence != 0)) {
      memset((int)param_1 + uVar2,0,iVar3);
      uVar2 = uVar2 + iVar3;
    }
    else {
      lVar1 = ov_read(this->m_vf,(char *)((int)param_1 + uVar2),iVar3,0,2,1,&this->m_bitstream);
      if (lVar1 < 1) {
        if (lVar1 == 0) {
          if (param_3 != 0) {
            iVar3 = ov_raw_seek(this->m_vf,(ulonglong)unaff_EDI << 0x20);
            if (iVar3 == 0) goto LAB_004b1585;
            Trace("  ::Reset() got error %d\n");
          }
        }
        else {
          ov_clear(this->m_vf);
          this->m_bValid = 0;
        }
        this->m_bFillWithSilence = 1;
      }
      else {
        uVar2 = uVar2 + lVar1;
        this->m_UnpackedSize = this->m_UnpackedSize + lVar1;
      }
    }
LAB_004b1585:
    if (param_2 <= uVar2) {
      return;
    }
  } while( true );
}
