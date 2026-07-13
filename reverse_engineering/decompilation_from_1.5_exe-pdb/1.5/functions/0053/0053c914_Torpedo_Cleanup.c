/*
 * Entry: 0053c914
 * Name: Torpedo::Cleanup
 * Namespace: Torpedo
 * Signature: void Cleanup(Torpedo * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Torpedo::Cleanup(Torpedo *this)

{
  CleanupSound(this);
  PowerUp::Cleanup((PowerUp *)this);
  return;
}
