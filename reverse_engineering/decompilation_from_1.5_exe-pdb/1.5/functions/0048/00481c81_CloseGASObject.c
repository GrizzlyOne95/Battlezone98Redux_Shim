/*
 * Entry: 00481c81
 * Name: CloseGASObject
 * Namespace: Global
 * Signature: void CloseGASObject(_gas_object * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl CloseGASObject(_gas_object *param_1)

{
  IDirectSound3DBuffer *pIVar1;
  _gas_object *unaff_ESI;
  
  if (param_1 != (_gas_object *)0x0) {
    UnlinkCopy(unaff_ESI);
    if (param_1->dsb != (IDirectSoundBuffer *)0x0) {
      pIVar1 = param_1->dsb3d;
      if (pIVar1 != (IDirectSound3DBuffer *)0x0) {
        (**(code **)((int)*pIVar1 + 8))(pIVar1);
      }
      (**(code **)((int)*param_1->dsb + 8))(param_1->dsb);
      param_1->dsb = (IDirectSoundBuffer *)0x0;
      param_1->dsb3d = (IDirectSound3DBuffer *)0x0;
      UsedMemory = UsedMemory - param_1->SoundSize;
    }
    if (param_1->wavBuf != (uchar *)0x0) {
      if ((param_1->flags & 0x200) == 0) {
        UnlockItem((param_1->gc).name);
      }
      param_1->wavBuf = (uchar *)0x0;
      param_1->wavStart = (uchar *)0x0;
    }
  }
  return;
}
