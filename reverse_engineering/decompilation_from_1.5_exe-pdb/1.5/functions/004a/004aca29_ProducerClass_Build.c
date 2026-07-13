/*
 * Entry: 004aca29
 * Name: ProducerClass::Build
 * Namespace: ProducerClass
 * Signature: GameObject * Build(ProducerClass * this, _OBJ76 * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GameObject * __thiscall ProducerClass::Build(ProducerClass *this,_OBJ76 *param_1)

{
  Producer *pPVar1;
  
  pPVar1 = GameObject::operator_new(0x318);
  if (pPVar1 == (Producer *)0x0) {
    pPVar1 = (Producer *)0x0;
  }
  else {
    pPVar1 = Producer::Producer(pPVar1,param_1,this);
  }
  return (GameObject *)pPVar1;
}
