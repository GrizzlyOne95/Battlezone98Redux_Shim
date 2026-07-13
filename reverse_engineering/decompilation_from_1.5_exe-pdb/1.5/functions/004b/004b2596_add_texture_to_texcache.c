/*
 * Entry: 004b2596
 * Name: add_texture_to_texcache
 * Namespace: Global
 * Signature: _texcache * add_texture_to_texcache(char * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_texcache * __cdecl add_texture_to_texcache(char *param_1)

{
  _texcache *_Dest;
  ulong uVar1;
  char *unaff_ESI;
  
  _Dest = malloc(0x24);
  if (_Dest == (_texcache *)0x0) {
    return (_texcache *)0x0;
  }
  _Dest->next = (_texcache *)0x0;
  _Dest->next_purge = (_texcache *)0x0;
  _Dest->last_purge = (_texcache *)0x0;
  strncpy(_Dest->name,param_1,0x10);
  uVar1 = thash(unaff_ESI);
  _Dest->next = texcache[uVar1];
  texcache[uVar1] = _Dest;
  return _Dest;
}
