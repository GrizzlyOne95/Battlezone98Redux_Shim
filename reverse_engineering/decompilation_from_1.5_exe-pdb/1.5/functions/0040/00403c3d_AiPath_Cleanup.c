/*
 * Entry: 00403c3d
 * Name: AiPath::Cleanup
 * Namespace: AiPath
 * Signature: void Cleanup(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl AiPath::Cleanup(void)

{
  AiPath *this;
  AiPath **ppAVar1;
  
  while (pathList._Mysize != 0) {
    ppAVar1 = std::list<AiPath_*,std::allocator<AiPath_*>_>::back(&pathList);
    this = *ppAVar1;
    if (this != (AiPath *)0x0) {
      ~AiPath(this);
      operator_delete(this);
    }
  }
  return;
}
