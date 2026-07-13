/*
 * Entry: 004a5328
 * Name: Person::Init
 * Namespace: Person
 * Signature: void Init(Person * this, int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Person::Init(Person *this,int param_1)

{
  GameObject::Init((GameObject *)this,param_1);
  if (this == (Person *)GameObject::userObject) {
    ColorFade::ClearFade(&colorFade);
  }
  return;
}
