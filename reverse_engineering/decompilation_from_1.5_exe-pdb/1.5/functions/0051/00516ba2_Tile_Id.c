/*
 * Entry: 00516ba2
 * Name: Tile_Id
 * Namespace: Global
 * Signature: tileid * Tile_Id(tileid * __return_storage_ptr__, tileid param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

tileid * __cdecl Tile_Id(tileid *__return_storage_ptr__,tileid param_1)

{
  __return_storage_ptr__->id = param_1.id;
  __return_storage_ptr__->texture0 = param_1.texture0;
  __return_storage_ptr__->texturevariation = param_1.texturevariation;
  return __return_storage_ptr__;
}
