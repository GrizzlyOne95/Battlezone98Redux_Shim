/*
 * Entry: 004d32a2
 * Name: PointsToRect
 * Namespace: Global
 * Signature: tagRECT * PointsToRect(tagRECT * __return_storage_ptr__, tagPOINT param_1, tagPOINT param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

tagRECT * __cdecl PointsToRect(tagRECT *__return_storage_ptr__,tagPOINT param_1,tagPOINT param_2)

{
  if (param_2.x < param_1.x) {
    __return_storage_ptr__->left = param_2.x;
    __return_storage_ptr__->right = param_1.x;
  }
  else {
    __return_storage_ptr__->left = param_1.x;
    __return_storage_ptr__->right = param_2.x;
  }
  if (param_2.y < param_1.y) {
    __return_storage_ptr__->top = param_2.y;
    __return_storage_ptr__->bottom = param_1.y;
    return __return_storage_ptr__;
  }
  __return_storage_ptr__->top = param_1.y;
  __return_storage_ptr__->bottom = param_2.y;
  return __return_storage_ptr__;
}
