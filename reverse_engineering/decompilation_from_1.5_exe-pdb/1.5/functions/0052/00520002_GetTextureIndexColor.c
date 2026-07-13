/*
 * Entry: 00520002
 * Name: GetTextureIndexColor
 * Namespace: Global
 * Signature: RGB GetTextureIndexColor(int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

RGB __cdecl GetTextureIndexColor(int param_1)

{
  int in_stack_00000008;
  
  *(undefined2 *)param_1 = *(undefined2 *)(TileColors + in_stack_00000008);
  *(uchar *)(param_1 + 2) = TileColors[in_stack_00000008].b;
  return SUB43(param_1,0);
}
