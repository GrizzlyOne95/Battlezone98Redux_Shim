/*
 * Entry: 0048220e
 * Name: StartGASObject
 * Namespace: Global
 * Signature: int StartGASObject(_gas_object * param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl StartGASObject(_gas_object *param_1,int param_2)

{
  ulong *puVar1;
  _func___cdecl_int__gas_object_ptr_long *p_Var2;
  int iVar3;
  undefined4 uVar4;
  _gas_object *unaff_ESI;
  int local_8;
  
  local_8 = 0;
  if (GASActive == 0) {
    local_8 = 1;
  }
  else {
    if (param_1->dsb == (IDirectSoundBuffer *)0x0) {
      AllocBuffer(unaff_ESI);
    }
    iVar3 = (param_1->gpi).loopMode;
    if (iVar3 == 0) {
      uVar4 = 0;
    }
    else {
      if (iVar3 == 2) {
        (param_1->storage).gsBytes.gsChar1 = '\x01';
      }
      uVar4 = 1;
    }
    (param_1->gc).volume = (float)(param_1->gpi).volume;
    (param_1->gc).rate = (float)(param_1->gpi).sampleRate;
    if ((param_1->gpi).random != 0) {
      iVar3 = rand();
      (param_1->gc).rate = SampleMods[iVar3 % 10] * (param_1->gc).rate;
    }
    p_Var2 = (param_1->gc).bofCallback;
    if ((p_Var2 == (_func___cdecl_int__gas_object_ptr_long *)0x0) ||
       (iVar3 = (*p_Var2)(param_1,1), iVar3 != 0)) {
      puVar1 = &(param_1->gc).flags;
      *puVar1 = *puVar1 | 0x1e0;
      SetGASAudioProperties((_gas_object *)param_2,(int)unaff_ESI);
      (**(code **)((int)*param_1->dsb + 0x30))(param_1->dsb,0,0,uVar4);
      param_1->flags = param_1->flags | 4;
      local_8 = 1;
    }
  }
  return local_8;
}
