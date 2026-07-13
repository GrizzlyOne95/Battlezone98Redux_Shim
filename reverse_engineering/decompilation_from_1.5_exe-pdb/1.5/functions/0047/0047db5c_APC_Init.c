/*
 * Entry: 0047db5c
 * Name: APC::Init
 * Namespace: APC
 * Signature: void Init(APC * this, int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall APC::Init(APC *this,int param_1)

{
  GameObject::Init((GameObject *)this,param_1);
  if (this == (APC *)GameObject::userObject) {
    ColorFade::ClearFade(&colorFade);
  }
  return;
}
