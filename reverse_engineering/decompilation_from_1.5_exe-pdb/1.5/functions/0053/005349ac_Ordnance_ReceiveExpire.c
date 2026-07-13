/*
 * Entry: 005349ac
 * Name: Ordnance_ReceiveExpire
 * Namespace: Global
 * Signature: void Ordnance_ReceiveExpire(char * param_1, uint param_2, ushort param_3, float param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Ordnance_ReceiveExpire(char *param_1,uint param_2,ushort param_3,float param_4)

{
  ulong *puVar1;
  _OBJ76 *p_Var2;
  bool bVar3;
  pair<std::pair<unsigned_short,unsigned_short>_const_,Ordnance_*> *ppVar4;
  pair<std::pair<unsigned_short,unsigned_short>_const_,Ordnance_*> *ppVar5;
  float *pfVar6;
  const_iterator local_18;
  const_iterator local_10;
  char *local_8;
  
  local_8 = param_1 + param_2;
  if (param_1 < local_8) {
    do {
      param_1 = param_1 + 4;
      std::
      _Tree<std::_Tmap_traits<std::pair<unsigned_short,unsigned_short>,Ordnance_*,std::less<std::pair<unsigned_short,unsigned_short>_>,std::allocator<std::pair<std::pair<unsigned_short,unsigned_short>_const_,Ordnance_*>_>,0>_>
      ::find((_Tree<std::_Tmap_traits<std::pair<unsigned_short,unsigned_short>,Ordnance_*,std::less<std::pair<unsigned_short,unsigned_short>_>,std::allocator<std::pair<std::pair<unsigned_short,unsigned_short>_const_,Ordnance_*>_>,0>_>
              *)&netOrdnanceMap,(pair<unsigned_short,unsigned_short> *)&local_10);
      std::
      _Tree<std::_Tmap_traits<std::pair<unsigned_short,unsigned_short>,Ordnance_*,std::less<std::pair<unsigned_short,unsigned_short>_>,std::allocator<std::pair<std::pair<unsigned_short,unsigned_short>_const_,Ordnance_*>_>,0>_>
      ::const_iterator::const_iterator
                (&local_18,(_Node *)netOrdnanceMap._24_4_,
                 (_Tree<std::_Tmap_traits<std::pair<unsigned_short,unsigned_short>,Ordnance_*,std::less<std::pair<unsigned_short,unsigned_short>_>,std::allocator<std::pair<std::pair<unsigned_short,unsigned_short>_const_,Ordnance_*>_>,0>_>
                  *)&netOrdnanceMap);
      bVar3 = std::
              _Tree<std::_Tmap_traits<std::pair<unsigned_short,unsigned_short>,Ordnance_*,std::less<std::pair<unsigned_short,unsigned_short>_>,std::allocator<std::pair<std::pair<unsigned_short,unsigned_short>_const_,Ordnance_*>_>,0>_>
              ::const_iterator::operator==(&local_10,&local_18);
      if (!bVar3) {
        ppVar4 = std::
                 _Tree<std::_Tmap_traits<std::pair<unsigned_short,unsigned_short>,Ordnance_*,std::less<std::pair<unsigned_short,unsigned_short>_>,std::allocator<std::pair<std::pair<unsigned_short,unsigned_short>_const_,Ordnance_*>_>,0>_>
                 ::const_iterator::operator*(&local_10);
        ppVar5 = std::
                 _Tree<std::_Tmap_traits<std::pair<unsigned_short,unsigned_short>,Ordnance_*,std::less<std::pair<unsigned_short,unsigned_short>_>,std::allocator<std::pair<std::pair<unsigned_short,unsigned_short>_const_,Ordnance_*>_>,0>_>
                 ::const_iterator::operator*(&local_10);
        pfVar6 = std::min<float>(&ppVar4->second->lifeTimer,&param_4);
        ppVar5->second->lifeTimer = *pfVar6;
        if (param_4 <= 0.0) {
          ppVar4 = std::
                   _Tree<std::_Tmap_traits<std::pair<unsigned_short,unsigned_short>,Ordnance_*,std::less<std::pair<unsigned_short,unsigned_short>_>,std::allocator<std::pair<std::pair<unsigned_short,unsigned_short>_const_,Ordnance_*>_>,0>_>
                   ::const_iterator::operator*(&local_10);
          p_Var2 = ppVar4->second->obj;
          if (p_Var2 != (_OBJ76 *)0x0) {
            puVar1 = &p_Var2->flags;
            *puVar1 = *puVar1 | 0x200;
          }
        }
      }
    } while (param_1 < local_8);
  }
  return;
}
