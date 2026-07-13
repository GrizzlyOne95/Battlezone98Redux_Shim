/*
 * Entry: 004b26bf
 * Name: TexAnim_Register
 * Namespace: Global
 * Signature: int TexAnim_Register(_OBJ76 * param_1, char * param_2, _func___cdecl_void__OBJ76_ptr_char_ptr_void_ptr * param_3, void * param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl
TexAnim_Register(_OBJ76 *param_1,char *param_2,
                _func___cdecl_void__OBJ76_ptr_char_ptr_void_ptr *param_3,void *param_4)

{
  byte bVar1;
  texanim *ptVar2;
  char *pcVar3;
  int iVar4;
  texanim *ptVar5;
  byte *pbVar6;
  texanim *unaff_EBX;
  bool bVar7;
  
  ptVar5 = texanim_list;
  do {
    do {
      ptVar2 = ptVar5;
      if (ptVar2 == (texanim *)0x0) {
        ptVar5 = operator_new(0x24);
        iVar4 = 0;
        if (ptVar5 != (texanim *)0x0) {
          i_got_dibs_on_obj(param_1,"texanim");
          ptVar5->obj = param_1;
          strncpy(ptVar5->tex_name,param_2,0xf);
          ptVar5->prev = (texanim *)0x0;
          ptVar5->callback = param_3;
          ptVar5->cb_data = param_4;
          ptVar5->next = texanim_list;
          if (texanim_list != (texanim *)0x0) {
            texanim_list->prev = ptVar5;
          }
          iVar4 = 1;
          texanim_list = ptVar5;
        }
        return iVar4;
      }
      ptVar5 = ptVar2->next;
    } while (ptVar2->obj != param_1);
    pcVar3 = ptVar2->tex_name;
    pbVar6 = (byte *)param_2;
    do {
      bVar1 = *pcVar3;
      bVar7 = bVar1 < *pbVar6;
      if (bVar1 != *pbVar6) {
LAB_004b26fd:
        iVar4 = (1 - (uint)bVar7) - (uint)(bVar7 != 0);
        goto LAB_004b2702;
      }
      if (bVar1 == 0) break;
      bVar1 = pcVar3[1];
      bVar7 = bVar1 < pbVar6[1];
      if (bVar1 != pbVar6[1]) goto LAB_004b26fd;
      pcVar3 = pcVar3 + 2;
      pbVar6 = pbVar6 + 2;
    } while (bVar1 != 0);
    iVar4 = 0;
LAB_004b2702:
    if (iVar4 == 0) {
      remove_animation(unaff_EBX);
    }
  } while( true );
}
