/*
 * Entry: 0058291a
 * Name: TextInput_CreateRegion
 * Namespace: Global
 * Signature: void * TextInput_CreateRegion(TEXTINPUT_DEF * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __cdecl TextInput_CreateRegion(TEXTINPUT_DEF *param_1)

{
  ulong uVar1;
  ulong *puVar2;
  
  puVar2 = malloc(0x130);
  *puVar2 = param_1->x;
  puVar2[1] = param_1->y;
  puVar2[2] = param_1->dx;
  puVar2[0x49] = param_1->flags | 0x200;
  uVar1 = param_1->color;
  puVar2[0x48] = 0xffffffff;
  puVar2[0x47] = uVar1;
  puVar2[0x4a] = (ulong)param_1->callback;
  puVar2[0x4b] = (ulong)param_1->updown_callback;
  uVar1 = Default_Font->char_height;
  puVar2[3] = uVar1;
  GetCharacterAddress(Default_Font,0x57);
  puVar2[0x40] = uVar1;
  puVar2[0x41] = 0xef;
  memset(puVar2 + 4,0,0xf0);
  puVar2[0x46] = 0;
  puVar2[0x45] = 0;
  puVar2[0x44] = 0;
  puVar2[0x43] = 0;
  puVar2[0x42] = 0;
  region_list = NewWrapper(region_list,(wrap_struct *)0x0,puVar2);
  return region_list;
}
