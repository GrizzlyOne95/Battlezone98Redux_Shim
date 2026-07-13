/*
 * Entry: 0054fac1
 * Name: Scroll_CreateRegion
 * Namespace: Global
 * Signature: void * Scroll_CreateRegion(REGION_DEF * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __cdecl Scroll_CreateRegion(REGION_DEF *param_1)

{
  ulong uVar1;
  uint uVar2;
  ulong uVar3;
  ulong *puVar4;
  void *pvVar5;
  
  puVar4 = malloc(100);
  *puVar4 = param_1->x;
  puVar4[1] = param_1->y;
  puVar4[2] = param_1->dx;
  uVar3 = fHeight;
  if ((param_1->flags & 0x10) == 0) {
    puVar4[3] = param_1->dy;
  }
  else {
    puVar4[3] = fHeight;
  }
  uVar1 = param_1->color;
  puVar4[0xd] = 0xffffffff;
  puVar4[0xb] = uVar1;
  puVar4[0x16] = (ulong)param_1->duration;
  puVar4[0x17] = 0xbf800000;
  uVar2 = param_1->flags;
  puVar4[0x18] = uVar2;
  uVar1 = param_1->color;
  puVar4[0xc] = 0xffffffff;
  puVar4[0xb] = uVar1;
  puVar4[5] = 0x4f;
  if ((uVar2 & 0x10) == 0) {
    puVar4[4] = puVar4[3] / uVar3;
  }
  else {
    puVar4[4] = 1;
  }
  puVar4[6] = uVar3;
  puVar4[7] = 0;
  if ((uVar2 & 8) == 0) {
    puVar4[8] = puVar4[4];
  }
  else {
    puVar4[8] = 0;
  }
  puVar4[9] = 0;
  pvVar5 = malloc((puVar4[4] + 5) * 0x58);
  puVar4[10] = (ulong)pvVar5;
  memset(pvVar5,0,(puVar4[4] + 5) * 0x58);
  region_list = NewWrapper(region_list,(wrap_struct *)0x0,puVar4);
  return region_list;
}
