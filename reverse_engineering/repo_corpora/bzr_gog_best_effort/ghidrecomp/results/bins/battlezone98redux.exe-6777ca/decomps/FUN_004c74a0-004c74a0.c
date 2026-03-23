
void __fastcall FUN_004c74a0(int param_1)

{
  int iVar1;
  undefined2 *puVar2;
  undefined4 local_c;
  
  iVar1 = *(int *)(param_1 + 0x415c);
  while ((local_c = iVar1 + 0x3fffU & 0x3fff, *(int *)(param_1 + 0x4154) != 0 &&
         (((int)*(short *)(param_1 + 0x4460 + local_c * 6) & 0x8000U) == 0))) {
    *(uint *)(param_1 + 0x415c) = local_c;
    *(int *)(param_1 + 0x4154) = *(int *)(param_1 + 0x4154) + -1;
    if (((int)*(short *)(param_1 + 0x4462 + *(int *)(param_1 + 0x415c) * 6) & 0x8000U) == 0) {
      iVar1 = *(int *)(param_1 + 0x415c);
      puVar2 = (undefined2 *)
               FUN_00492d60(*(ushort *)(param_1 + 0x4460 + *(int *)(param_1 + 0x415c) * 6) & 0x7fff,
                            *(ushort *)(param_1 + 0x4462 + *(int *)(param_1 + 0x415c) * 6) & 0x7fff)
      ;
      *puVar2 = *(undefined2 *)(param_1 + 0x4464 + iVar1 * 6);
    }
    else {
      iVar1 = *(int *)(param_1 + 0x415c);
      puVar2 = (undefined2 *)
               FUN_004c0fe0(*(ushort *)(param_1 + 0x4460 + *(int *)(param_1 + 0x415c) * 6) & 0x7fff,
                            *(ushort *)(param_1 + 0x4462 + *(int *)(param_1 + 0x415c) * 6) & 0x7fff)
      ;
      *puVar2 = *(undefined2 *)(param_1 + 0x4464 + iVar1 * 6);
    }
    iVar1 = *(int *)(param_1 + 0x415c);
  }
  if (*(int *)(param_1 + 0x4154) != 0) {
    *(uint *)(param_1 + 0x415c) = local_c;
    *(int *)(param_1 + 0x4154) = *(int *)(param_1 + 0x4154) + -1;
    if (((int)*(short *)(param_1 + 0x4462 + *(int *)(param_1 + 0x415c) * 6) & 0x8000U) == 0) {
      iVar1 = *(int *)(param_1 + 0x415c);
      puVar2 = (undefined2 *)
               FUN_00492d60(*(ushort *)(param_1 + 0x4460 + *(int *)(param_1 + 0x415c) * 6) & 0x7fff,
                            *(ushort *)(param_1 + 0x4462 + *(int *)(param_1 + 0x415c) * 6) & 0x7fff)
      ;
      *puVar2 = *(undefined2 *)(param_1 + 0x4464 + iVar1 * 6);
    }
    else {
      iVar1 = *(int *)(param_1 + 0x415c);
      puVar2 = (undefined2 *)
               FUN_004c0fe0(*(ushort *)(param_1 + 0x4460 + *(int *)(param_1 + 0x415c) * 6) & 0x7fff,
                            *(ushort *)(param_1 + 0x4462 + *(int *)(param_1 + 0x415c) * 6) & 0x7fff)
      ;
      *puVar2 = *(undefined2 *)(param_1 + 0x4464 + iVar1 * 6);
    }
  }
  return;
}

