/*
 * Entry: 004a792d
 * Name: PersonClass::Build
 * Namespace: PersonClass
 * Signature: GameObject * Build(PersonClass * this, _OBJ76 * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GameObject * __thiscall PersonClass::Build(PersonClass *this,_OBJ76 *param_1)

{
  Person *pPVar1;
  
  pPVar1 = GameObject::operator_new(0x278);
  if (pPVar1 == (Person *)0x0) {
    pPVar1 = (Person *)0x0;
  }
  else {
    pPVar1 = Person::Person(pPVar1,param_1,this);
  }
  return (GameObject *)pPVar1;
}
