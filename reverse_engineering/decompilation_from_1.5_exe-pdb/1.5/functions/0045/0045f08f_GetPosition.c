/*
 * Entry: 0045f08f
 * Name: GetPosition
 * Namespace: Global
 * Signature: VECTOR_3D * GetPosition(VECTOR_3D * __return_storage_ptr__, char * param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

VECTOR_3D * __cdecl GetPosition(VECTOR_3D *__return_storage_ptr__,char *param_1,int param_2)

{
  bool bVar1;
  int unaff_EDI;
  float local_10;
  float local_c;
  float local_8;
  
  AiPath::Find(param_1);
  bVar1 = GetPosition((VECTOR_3D *)param_2,(AiPath *)param_1,unaff_EDI);
  if (!bVar1) {
    local_10 = 0.0;
    local_c = 0.0;
    local_8 = 0.0;
  }
  __return_storage_ptr__->x = local_10;
  __return_storage_ptr__->y = local_c;
  __return_storage_ptr__->z = local_8;
  return __return_storage_ptr__;
}
