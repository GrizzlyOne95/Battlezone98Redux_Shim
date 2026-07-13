/*
 * Entry: 005b4e80
 * Name: floor0_look
 * Namespace: Global
 * Signature: void * floor0_look(vorbis_dsp_state * param_1, void * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __cdecl floor0_look(vorbis_dsp_state *param_1,void *param_2)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  void *pvVar3;
  
  puVar2 = calloc(1,0x20);
  uVar1 = *(undefined4 *)((int)param_2 + 8);
  puVar2[1] = *(undefined4 *)param_2;
  *puVar2 = uVar1;
  puVar2[5] = param_2;
  pvVar3 = calloc(2,4);
  puVar2[2] = pvVar3;
  return puVar2;
}
