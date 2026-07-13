/*
 * Entry: 00480aed
 * Name: StartGAS
 * Namespace: Global
 * Signature: int StartGAS(HWND__ * param_1, GAS_MASTER * param_2, int param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

int __cdecl StartGAS(HWND__ *param_1,GAS_MASTER *param_2,int param_3)

{
  IDirectSoundBuffer **ppIVar1;
  IDirectSoundBuffer *pIVar2;
  GAS_MASTER *in_ECX;
  int iVar3;
  HWND__ *in_EDX;
  int *unaff_ESI;
  IDirectSound **unaff_EDI;
  GAS_MASTER *pGVar4;
  undefined4 *puVar5;
  char *pcVar6;
  undefined4 local_8c [18];
  int local_44;
  long local_40;
  undefined4 local_2c [9];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  if (in_ECX == (GAS_MASTER *)0x0) {
    return 0;
  }
  pGVar4 = in_ECX;
  for (iVar3 = 9; iVar3 != 0; iVar3 = iVar3 + -1) {
    pGVar4->DSHandle = (IDirectSound *)0x0;
    pGVar4 = (GAS_MASTER *)&pGVar4->primaryBuffer;
  }
  iVar3 = DSEnable(in_EDX,unaff_EDI,unaff_ESI);
  if (iVar3 == 0) {
    return 0;
  }
  if (param_1 == (HWND__ *)0x0) {
LAB_00480bfa:
    (**(code **)((int)*in_ECX->primaryBuffer + 0x30))(in_ECX->primaryBuffer,0,0,1);
    OggManager::Init();
  }
  else {
    puVar5 = local_2c;
    for (iVar3 = 9; iVar3 != 0; iVar3 = iVar3 + -1) {
      *puVar5 = 0;
      puVar5 = puVar5 + 1;
    }
    ppIVar1 = &in_ECX->primaryBuffer;
    local_2c[0] = 0x24;
    local_2c[1] = 0x11;
    iVar3 = (**(code **)((int)*in_ECX->DSHandle + 0xc))(in_ECX->DSHandle,local_2c,ppIVar1,0);
    if (iVar3 == 0) {
      memset(local_8c,0,0x60);
      local_8c[0] = 0x60;
      (**(code **)((int)*in_ECX->DSHandle + 0x10))(in_ECX->DSHandle,local_8c);
      DSHwFreeMemory = local_44;
      if (local_44 == 0) {
        DSHwFreeMemory = 500000;
      }
      DSHwMaxContigFreeMem = local_40;
      iVar3 = SetDSoundRate(in_ECX,audioMixRate);
      pIVar2 = *ppIVar1;
      if (iVar3 == 0) {
        (**(code **)((int)*pIVar2 + 8))(pIVar2);
        *ppIVar1 = (IDirectSoundBuffer *)0x0;
        return 1;
      }
      iVar3 = (**(code **)*pIVar2)(pIVar2,&IID_IDirectSound3DListener,&in_ECX->listener);
      if (iVar3 == 0) goto LAB_00480bfa;
      (**(code **)((int)**ppIVar1 + 8))(*ppIVar1);
      *ppIVar1 = (IDirectSoundBuffer *)0x0;
      pcVar6 = "Can\'t create DS3D listener. 3D sound disabled";
    }
    else {
      pcVar6 = "Can\'t create DS3D primary buffer. 3D sound disabled";
    }
    DEBUG_systemWarning(pcVar6);
  }
  return 1;
}
