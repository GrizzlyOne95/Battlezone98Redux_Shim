/*
 * Entry: 00485e1b
 * Name: Craft::Init
 * Namespace: Craft
 * Signature: void Init(Craft * this, int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Craft::Init(Craft *this,int param_1)

{
  GameObject::Init((GameObject *)this,param_1);
  if (this == (Craft *)GameObject::userObject) {
    ColorFade::ClearFade(&colorFade);
  }
  return;
}
