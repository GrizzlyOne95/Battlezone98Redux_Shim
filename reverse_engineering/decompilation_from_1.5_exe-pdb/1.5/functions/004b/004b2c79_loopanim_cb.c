/*
 * Entry: 004b2c79
 * Name: loopanim_cb
 * Namespace: Global
 * Signature: void loopanim_cb(_OBJ76 * param_1, char * param_2, void * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl loopanim_cb(_OBJ76 *param_1,char *param_2,void *param_3)

{
  int iVar1;
  float fVar2;
  
  fVar2 = Get_TimeLocal();
  if (*(float *)param_3 < fVar2) {
    while (fVar2 = Get_TimeLocal(), *(float *)param_3 < fVar2) {
      *(float *)param_3 = *(float *)param_3 + *(float *)((int)param_3 + 4);
      if (*(int *)((int)param_3 + 0x14) == 2) {
        iVar1 = *(int *)((int)param_3 + 0xc);
        if (*(int *)((int)param_3 + 8) + -1 <= iVar1) {
          if (*(code **)((int)param_3 + 0x18) == (code *)0x0) {
            return;
          }
          (**(code **)((int)param_3 + 0x18))(param_1);
          TexAnim_Unregister(param_1,param_2);
          return;
        }
LAB_004b2ce0:
        iVar1 = iVar1 + 1;
      }
      else {
        iVar1 = *(int *)((int)param_3 + 0xc);
        if (*(int *)((int)param_3 + 0x14) == 1) {
          if (iVar1 == 0) {
            iVar1 = *(int *)((int)param_3 + 8);
          }
          iVar1 = iVar1 + -1;
        }
        else {
          if (iVar1 < *(int *)((int)param_3 + 8) + -1) goto LAB_004b2ce0;
          iVar1 = 0;
        }
      }
      *(int *)((int)param_3 + 0xc) = iVar1;
    }
    Texture_Select(param_1,param_2,0,*(long *)((int)param_3 + 0xc),1);
  }
  return;
}
