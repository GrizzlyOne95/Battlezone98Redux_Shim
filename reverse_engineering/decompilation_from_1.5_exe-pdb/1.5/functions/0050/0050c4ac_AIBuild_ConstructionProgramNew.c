/*
 * Entry: 0050c4ac
 * Name: AIBuild_ConstructionProgramNew
 * Namespace: Global
 * Signature: tagCONSTRUCTION_PROGRAM * AIBuild_ConstructionProgramNew(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

tagCONSTRUCTION_PROGRAM * __cdecl AIBuild_ConstructionProgramNew(void)

{
  tagCP_ACCOUNT **pptVar1;
  int iVar2;
  tagCP_ACCOUNT **pptVar3;
  
  pptVar1 = calloc(1,0x80);
  Debug_Assert((int)pptVar1,0xdcc,".\\Schedule\\Aibuild.cpp","construction_program");
  pptVar3 = pptVar1;
  for (iVar2 = 0x20; iVar2 != 0; iVar2 = iVar2 + -1) {
    *pptVar3 = (tagCP_ACCOUNT *)0x0;
    pptVar3 = pptVar3 + 1;
  }
  return (tagCONSTRUCTION_PROGRAM *)pptVar1;
}
