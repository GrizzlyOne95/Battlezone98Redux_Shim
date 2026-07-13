/*
 * Entry: 0053db63
 * Name: TracerClass::Build
 * Namespace: TracerClass
 * Signature: Ordnance * Build(TracerClass * this, _OBJ76 * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Ordnance * __thiscall TracerClass::Build(TracerClass *this,_OBJ76 *param_1)

{
  Tracer *pTVar1;
  
  pTVar1 = operator_new(0x100);
  if (pTVar1 == (Tracer *)0x0) {
    pTVar1 = (Tracer *)0x0;
  }
  else {
    pTVar1 = Tracer::Tracer(pTVar1,param_1,this);
  }
  return (Ordnance *)pTVar1;
}
