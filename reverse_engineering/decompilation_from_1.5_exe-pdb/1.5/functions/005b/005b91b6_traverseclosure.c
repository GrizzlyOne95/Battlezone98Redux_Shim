/*
 * Entry: 005b91b6
 * Name: traverseclosure
 * Namespace: Global
 * Signature: void traverseclosure(global_State * param_1, Closure * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl traverseclosure(global_State *param_1,Closure *param_2)

{
  int in_EDX;
  int extraout_EDX;
  int extraout_EDX_00;
  int extraout_EDX_01;
  int extraout_EDX_02;
  undefined4 *puVar1;
  int iVar2;
  
  if ((((*(GCObject **)(in_EDX + 0xc))->gch).marked & 3) != 0) {
    reallymarkobject(param_1,*(GCObject **)(in_EDX + 0xc));
    in_EDX = extraout_EDX;
  }
  if (*(char *)(in_EDX + 6) == '\0') {
    if ((((*(GCObject **)(in_EDX + 0x10))->gch).marked & 3) != 0) {
      reallymarkobject(param_1,*(GCObject **)(in_EDX + 0x10));
      in_EDX = extraout_EDX_01;
    }
    iVar2 = 0;
    if (*(char *)(in_EDX + 7) != '\0') {
      puVar1 = (undefined4 *)(in_EDX + 0x14);
      do {
        if (((((GCObject *)*puVar1)->gch).marked & 3) != 0) {
          reallymarkobject(param_1,(GCObject *)*puVar1);
          in_EDX = extraout_EDX_02;
        }
        iVar2 = iVar2 + 1;
        puVar1 = puVar1 + 1;
      } while (iVar2 < (int)(uint)*(byte *)(in_EDX + 7));
    }
  }
  else {
    iVar2 = 0;
    if (*(char *)(in_EDX + 7) != '\0') {
      puVar1 = (undefined4 *)(in_EDX + 0x18);
      do {
        if ((3 < (int)puVar1[2]) && (((((GCObject *)*puVar1)->gch).marked & 3) != 0)) {
          reallymarkobject(param_1,(GCObject *)*puVar1);
          in_EDX = extraout_EDX_00;
        }
        iVar2 = iVar2 + 1;
        puVar1 = puVar1 + 4;
      } while (iVar2 < (int)(uint)*(byte *)(in_EDX + 7));
    }
  }
  return;
}
