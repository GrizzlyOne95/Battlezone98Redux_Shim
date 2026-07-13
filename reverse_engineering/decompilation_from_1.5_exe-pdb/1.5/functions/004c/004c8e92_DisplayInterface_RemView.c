/*
 * Entry: 004c8e92
 * Name: DisplayInterface::RemView
 * Namespace: DisplayInterface
 * Signature: void RemView(DisplayInterface * this, int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall DisplayInterface::RemView(DisplayInterface *this,int param_1)

{
  RemViewSimulate(this,param_1);
  RemViewRender(this,param_1);
  return;
}
