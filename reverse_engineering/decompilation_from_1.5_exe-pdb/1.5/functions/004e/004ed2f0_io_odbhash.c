/*
 * Entry: 004ed2f0
 * Name: io_odbhash
 * Namespace: Global
 * Signature: ulong io_odbhash(_OBJ76 * param_1, _OBJ76 * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

ulong __cdecl io_odbhash(_OBJ76 *param_1,_OBJ76 *param_2)

{
  uint in_EAX;
  
  return ((in_EAX ^ (uint)param_1) * 0x6cd + 0xaab) % 0x9c7;
}
