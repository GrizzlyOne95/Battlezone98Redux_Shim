/*
 * Entry: 005451d6
 * Name: Set_Primitive_Type
 * Namespace: Global
 * Signature: void Set_Primitive_Type(_D3DPRIMITIVETYPE param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Set_Primitive_Type(_D3DPRIMITIVETYPE param_1)

{
  _D3DPRIMITIVETYPE unaff_ESI;
  
  if (gD3DEB.ePrimitiveType != unaff_ESI) {
    Flush_Vertex_Buffer();
    gD3DEB.ePrimitiveType = unaff_ESI;
  }
  return;
}
