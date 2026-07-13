/*
 * Entry: 004c8b61
 * Name: DisplayInterface::AddView
 * Namespace: DisplayInterface
 * Signature: void AddView(DisplayInterface * this, int param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall DisplayInterface::AddView(DisplayInterface *this,int param_1,int param_2)

{
  AddViewSimulate(this,param_1,param_2);
  AddViewRender(this,param_1,param_2);
  return;
}
