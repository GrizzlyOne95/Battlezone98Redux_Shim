
/* Library Function - Single Match
    unsigned int __cdecl std::_Hash_seq(unsigned char const *,unsigned int)
   
   Libraries: Visual Studio 2015 Debug, Visual Studio 2015 Release */

uint __cdecl std::_Hash_seq(uchar *param_1,uint param_2)

{
  uint local_c;
  uint local_8;
  
  local_8 = 0x811c9dc5;
  for (local_c = 0; local_c < param_2; local_c = local_c + 1) {
    local_8 = (param_1[local_c] ^ local_8) * 0x1000193;
  }
  return local_8;
}

