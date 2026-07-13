/*
 * Entry: 0045ec02
 * Name: GetPosition
 * Namespace: Global
 * Signature: bool GetPosition(VECTOR_3D * param_1, char * param_2, int param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __cdecl GetPosition(VECTOR_3D *param_1,char *param_2,int param_3)

{
  bool bVar1;
  int unaff_retaddr;
  
  AiPath::Find((char *)param_1);
  bVar1 = GetPosition((VECTOR_3D *)param_2,(AiPath *)param_1,unaff_retaddr);
  return bVar1;
}
