/*
 * Entry: 004c971b
 * Name: EarthQuake::StopQuake
 * Namespace: EarthQuake
 * Signature: void StopQuake(EarthQuake * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall EarthQuake::StopQuake(EarthQuake *this)

{
  _gas_object *p_Var1;
  
  this->scale = 0.0;
  p_Var1 = FindGASObject("gquak01.wav",(_OBJ76 *)0x0);
  if (p_Var1 != (_gas_object *)0x0) {
    StopGASEvent(p_Var1);
  }
  return;
}
