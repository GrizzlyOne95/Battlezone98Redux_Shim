/*
 * Entry: 004c7a1f
 * Name: TestInterface::Render
 * Namespace: TestInterface
 * Signature: void Render(TestInterface * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall TestInterface::Render(TestInterface *this)

{
  DisplayInterface::PrintClear((DisplayInterface *)this);
  DisplayInterface::PrintValue((DisplayInterface *)this,"Hello",x);
  return;
}
