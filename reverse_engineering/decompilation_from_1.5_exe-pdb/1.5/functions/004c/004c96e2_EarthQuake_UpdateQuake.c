/*
 * Entry: 004c96e2
 * Name: EarthQuake::UpdateQuake
 * Namespace: EarthQuake
 * Signature: void UpdateQuake(EarthQuake * this, float param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall EarthQuake::UpdateQuake(EarthQuake *this,float param_1)

{
  ulong *puVar1;
  _gas_object *p_Var2;
  long extraout_EAX;
  
  this->scale = param_1;
  p_Var2 = FindGASObject("gquak01.wav",(_OBJ76 *)0x0);
  if (p_Var2 != (_gas_object *)0x0) {
    _ftol2_sse();
    puVar1 = &(p_Var2->gc).flags;
    *puVar1 = *puVar1 | 0x40;
    (p_Var2->gpi).volume = extraout_EAX;
  }
  return;
}
