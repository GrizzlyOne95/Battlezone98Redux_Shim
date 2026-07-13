/*
 * Entry: 0048198d
 * Name: AllocBuffer
 * Namespace: Global
 * Signature: int AllocBuffer(_gas_object * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

int __cdecl AllocBuffer(_gas_object *param_1)

{
  undefined4 *puVar1;
  uint uVar2;
  float fVar3;
  bool bVar4;
  int *piVar5;
  int in_ECX;
  int iVar6;
  ulong *unaff_ESI;
  uchar **unaff_EDI;
  uint *puVar7;
  uint local_2c [2];
  tWAVEFORMATEX *local_24 [2];
  int local_1c;
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  puVar7 = local_2c;
  for (iVar6 = 9; iVar6 != 0; iVar6 = iVar6 + -1) {
    *puVar7 = 0;
    puVar7 = puVar7 + 1;
  }
  iVar6 = 0;
  local_2c[0] = 0x24;
  if (((*(int *)(in_ECX + 0x5c) == 0) || (GM->listener == (IDirectSound3DListener *)0x0)) ||
     ((*(uint *)(in_ECX + 0x14) & 0x400) != 0)) {
    local_2c[1] = (((*(uint *)(in_ECX + 0x14) >> 0xb & 0xf) != 4) - 1 & 0x20) + 0xc2;
  }
  else {
    local_2c[1] = 0x20092;
  }
  if (*(int *)(in_ECX + 0x44) != -1) {
    local_2c[1] = local_2c[1] | 0x20;
  }
  local_2c[1] = local_2c[1] | 0x40000;
  *(uint *)(in_ECX + 0x60) = local_2c[1];
  bVar4 = false;
  if ((*(uint *)(in_ECX + 0x78) & 0x200) == 0) {
    piVar5 = UseItem((char *)(in_ECX + 4));
    *(undefined4 *)(in_ECX + 0x50) = piVar5;
    *(int **)(in_ECX + 0x4c) = piVar5;
    if (piVar5 == (int *)0x0) goto LAB_00481b29;
    bVar4 = true;
    if (*piVar5 == 0x30534147) {
      *(undefined4 *)(in_ECX + 0x50) = piVar5 + 7;
    }
  }
  iVar6 = DSParseWaveResource((undefined4 *)(in_ECX + 0x50),local_24,unaff_EDI,unaff_ESI);
  if ((iVar6 != 0) && (local_24[0] != (tWAVEFORMATEX *)0x0)) {
    iVar6 = (**(code **)((int)*GM->DSHandle + 0xc))
                      (GM->DSHandle,local_2c,(undefined4 *)(in_ECX + 0x54),0);
    uVar2 = (uint)(iVar6 == 0);
    iVar6 = FillDSBuffer((IDirectSoundBuffer *)local_24[0],(uchar *)unaff_EDI,(ulong)unaff_ESI);
    if (iVar6 == 0) {
      return uVar2;
    }
    if (uVar2 == 0) {
      return 0;
    }
    UsedMemory = (int)&local_24[0]->wFormatTag + UsedMemory;
    *(tWAVEFORMATEX **)(in_ECX + 0x70) = local_24[0];
    *(int *)(in_ECX + 0x48) = *(int *)(local_1c + 4);
    iVar6 = *(int *)(local_1c + 4);
    fVar3 = (float)iVar6;
    if (iVar6 < 0) {
      fVar3 = fVar3 + 4.2949673e+09;
    }
    *(float *)(in_ECX + 0x18) = fVar3;
    if ((*(int *)(in_ECX + 0x5c) != 0) && (GM->listener != (IDirectSound3DListener *)0x0)) {
      puVar1 = *(undefined4 **)(in_ECX + 0x54);
      (**(code **)*puVar1)(puVar1,&IID_IDirectSound3DBuffer,in_ECX + 0x58);
    }
    if ((*(uint *)(in_ECX + 0x78) & 0x200) != 0) {
      return uVar2;
    }
    UnlockItem((char *)(in_ECX + 4));
    *(undefined4 *)(in_ECX + 0x4c) = 0;
    *(undefined4 *)(in_ECX + 0x50) = 0;
    return uVar2;
  }
LAB_00481b29:
  if ((((*(uint *)(in_ECX + 0x78) & 0x200) == 0) && (bVar4)) && (iVar6 != 0)) {
    UnlockItem((char *)(in_ECX + 4));
    *(undefined4 *)(in_ECX + 0x4c) = 0;
    *(undefined4 *)(in_ECX + 0x50) = 0;
  }
  return iVar6;
}
