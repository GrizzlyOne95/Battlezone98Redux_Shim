/*
 * Entry: 004904ed
 * Name: CSound::RestoreBuffer
 * Namespace: CSound
 * Signature: T_HRESULT RestoreBuffer(CSound * this, IDirectSoundBuffer * param_1, bool * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

undefined4 __thiscall CSound::RestoreBuffer(CSound *this,IDirectSoundBuffer *param_1,bool *param_2)

{
  IDirectSoundBuffer *pIVar1;
  bool *pbVar2;
  undefined4 uVar3;
  int iVar4;
  
  pbVar2 = param_2;
  pIVar1 = param_1;
  if (param_1 == (IDirectSoundBuffer *)0x0) {
    uVar3 = 0x800401f0;
  }
  else {
    if (param_2 != (bool *)0x0) {
      *param_2 = false;
    }
    iVar4 = (**(code **)((int)*param_1 + 0x24))(param_1,&param_1);
    if (iVar4 < 0) {
      uVar3 = 0x80004005;
    }
    else if (((uint)param_1 & 2) == 0) {
      uVar3 = 1;
    }
    else {
      do {
        iVar4 = (**(code **)((int)*pIVar1 + 0x50))(pIVar1);
        if (iVar4 == -0x7787ff6a) {
          Sleep(10);
        }
        iVar4 = (**(code **)((int)*pIVar1 + 0x50))(pIVar1);
      } while (iVar4 != 0);
      if (pbVar2 != (bool *)0x0) {
        *pbVar2 = true;
      }
      uVar3 = 0;
    }
  }
  return uVar3;
}
