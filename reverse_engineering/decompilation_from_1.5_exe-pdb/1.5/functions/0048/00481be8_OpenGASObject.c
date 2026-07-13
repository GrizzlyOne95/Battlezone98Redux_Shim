/*
 * Entry: 00481be8
 * Name: OpenGASObject
 * Namespace: Global
 * Signature: long OpenGASObject(GAS_MASTER * param_1, _gas_object * param_2, GAS_PREP_INFO * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

long __cdecl OpenGASObject(GAS_MASTER *param_1,_gas_object *param_2,GAS_PREP_INFO *param_3)

{
  int iVar1;
  void *pvVar2;
  _gas_object *unaff_EBX;
  _gas_object *unaff_ESI;
  GAS_PREP_INFO *unaff_retaddr;
  
  ConvertUserGPI((GAS_PREP_INFO *)unaff_EBX,unaff_retaddr);
  iVar1 = DistanceBump(unaff_EBX);
  if (iVar1 != 0) {
    return 0;
  }
  iVar1 = CheckWave(unaff_EBX);
  if (iVar1 == 0) {
    return 0;
  }
  iVar1 = VolumeBump(param_2);
  if (iVar1 != 0) {
    return 0;
  }
  SortSound(unaff_EBX);
  LinkCopy(param_2);
  if (param_2->count != -1) {
    if (((param_2->gpi).loopMode != 1) &&
       (iVar1 = CountCopies(unaff_EBX), (param_2->gpi).maxCopies < iVar1)) {
      return 0;
    }
    if ((param_2->flags & 0x200) == 0) {
      pvVar2 = UseItem((param_2->gc).name);
      if (pvVar2 == (void *)0x0) {
        return 0;
      }
      UnlockItem((param_2->gc).name);
      if (gasPaused != false) {
        param_2->flags = param_2->flags | 8;
      }
    }
    else {
      iVar1 = AllocBuffer(unaff_ESI);
      if (iVar1 == 0) {
        return 0;
      }
    }
    return 1;
  }
  return 0;
}
