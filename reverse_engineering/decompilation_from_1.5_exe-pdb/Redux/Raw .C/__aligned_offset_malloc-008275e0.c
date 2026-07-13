
/* Library Function - Single Match
    __aligned_offset_malloc
   
   Library: Visual Studio */

void * __cdecl __aligned_offset_malloc(size_t _Size,size_t _Alignment,size_t _Offset)

{
  void *pvVar1;
  
  pvVar1 = (void *)FUN_008273e0(_Size,_Alignment,_Offset,0,0);
  return pvVar1;
}

