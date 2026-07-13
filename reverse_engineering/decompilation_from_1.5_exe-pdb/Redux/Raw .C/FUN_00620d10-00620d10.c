
int FUN_00620d10(int param_1)

{
  byte bVar1;
  undefined4 *puVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  float10 fVar6;
  int local_c;
  
  puVar2 = *(undefined4 **)(param_1 + 0x18);
  local_c = (int)*(char *)((int)puVar2 + 0x15);
  if ((puVar2[0xb] == 0) || (*(char *)puVar2[0xb] == '\0')) {
    if ((puVar2[0xc] != 0) && (*(char *)puVar2[0xc] != '\0')) {
      bVar1 = *(byte *)(puVar2 + 5);
      iVar3 = *(int *)*puVar2;
      iVar4 = puVar2[3];
      iVar5 = puVar2[2];
      *(undefined4 *)puVar2[1] = 0;
      puVar2[7] = (int)((((double)(iVar3 << (bVar1 & 0x1f)) - (double)iVar4) * 2.0) / (double)iVar5
                       - 65536.0);
      *(undefined1 *)puVar2[0xc] = 0;
      local_c = 1;
    }
  }
  else {
    if (*(int *)(param_1 + 0xc) != 0) {
      (**(code **)((&DAT_0091fefc)[*(int *)(param_1 + 4)] + 0x10))
                (*(undefined4 *)(&DAT_0091ff80 + *(int *)(param_1 + 4) * 0x74),
                 *(undefined4 *)(param_1 + 8));
    }
    *(undefined4 *)puVar2[1] = 0;
    puVar2[7] = puVar2[4];
    *(undefined1 *)puVar2[0xb] = 0;
    local_c = 1;
  }
  if (*(char *)((int)puVar2 + 0x15) == '\0') {
    fVar6 = (float10)FUN_00822d60();
    if ((puVar2[9] != 0) && (*(char *)puVar2[9] != '\0')) {
      if (*(int *)puVar2[1] < 0) {
        *(undefined4 *)puVar2[1] = 0;
      }
      *(int *)puVar2[1] =
           (int)((float)(3 << ((byte)puVar2[8] & 0x1f)) * (float)fVar6 * 182.0) + *(int *)puVar2[1];
      if (0x5555 < *(int *)puVar2[1]) {
        *(undefined4 *)puVar2[1] = 0x5555;
      }
      puVar2[7] = puVar2[7] + *(int *)puVar2[1];
      if (0x10000 < (int)puVar2[7]) {
        puVar2[7] = 0x10000;
      }
      local_c = 1;
      *(undefined1 *)puVar2[9] = 0;
    }
    if ((puVar2[10] != 0) && (*(char *)puVar2[10] != '\0')) {
      if (0 < *(int *)puVar2[1]) {
        *(undefined4 *)puVar2[1] = 0;
      }
      *(int *)puVar2[1] =
           *(int *)puVar2[1] - (int)((float)(3 << ((byte)puVar2[8] & 0x1f)) * (float)fVar6 * 182.0);
      if (*(int *)puVar2[1] < -0x5555) {
        *(undefined4 *)puVar2[1] = 0xffffaaab;
      }
      puVar2[7] = puVar2[7] + *(int *)puVar2[1];
      if ((int)puVar2[7] < -0x10000) {
        puVar2[7] = 0xffff0000;
      }
      local_c = 1;
      *(undefined1 *)puVar2[10] = 0;
    }
    if (local_c == 0) {
      *(undefined4 *)puVar2[1] = 0;
    }
  }
  *(undefined1 *)((int)puVar2 + 0x15) = (undefined1)local_c;
  return local_c;
}

