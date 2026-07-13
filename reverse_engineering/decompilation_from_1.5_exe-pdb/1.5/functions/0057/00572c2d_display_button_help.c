/*
 * Entry: 00572c2d
 * Name: display_button_help
 * Namespace: Global
 * Signature: int display_button_help(ShellButton * param_1, TextLabel * param_2, char * param_3, char * param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

int __cdecl display_button_help(ShellButton *param_1,TextLabel *param_2,char *param_3,char *param_4)

{
  byte bVar1;
  int iVar2;
  char *pcVar3;
  byte *pbVar4;
  bool bVar5;
  byte local_108 [256];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  if (((param_1 != (ShellButton *)0x0) && (param_2 != (TextLabel *)0x0)) && (param_3 != (char *)0x0)
     ) {
    iVar2 = read_text_label("multi_help",param_4,(char *)local_108);
    if (iVar2 == 0) {
      strncpy((char *)local_108,param_3,0x100);
    }
    if (param_1->nButtonMode == 1) {
      pbVar4 = local_108;
      pcVar3 = param_2->textData;
      do {
        bVar1 = *pcVar3;
        bVar5 = bVar1 < *pbVar4;
        if (bVar1 != *pbVar4) {
LAB_00572cc7:
          iVar2 = (1 - (uint)bVar5) - (uint)(bVar5 != 0);
          goto LAB_00572ccc;
        }
        if (bVar1 == 0) break;
        bVar1 = pcVar3[1];
        bVar5 = bVar1 < pbVar4[1];
        if (bVar1 != pbVar4[1]) goto LAB_00572cc7;
        pcVar3 = pcVar3 + 2;
        pbVar4 = pbVar4 + 2;
      } while (bVar1 != 0);
      iVar2 = 0;
LAB_00572ccc:
      if ((iVar2 == 0) && (param_2->nTextVisible != 0)) {
        return 1;
      }
      TextLabel::SetLabelText(param_2,(char *)local_108);
      TextLabel::ShowLabelText(param_2,1);
      return 1;
    }
    if (param_1->nButtonMode == 0) {
      pbVar4 = local_108;
      pcVar3 = param_2->textData;
      do {
        bVar1 = *pcVar3;
        bVar5 = bVar1 < *pbVar4;
        if (bVar1 != *pbVar4) {
LAB_00572d1f:
          iVar2 = (1 - (uint)bVar5) - (uint)(bVar5 != 0);
          goto LAB_00572d24;
        }
        if (bVar1 == 0) break;
        bVar1 = pcVar3[1];
        bVar5 = bVar1 < pbVar4[1];
        if (bVar1 != pbVar4[1]) goto LAB_00572d1f;
        pcVar3 = pcVar3 + 2;
        pbVar4 = pbVar4 + 2;
      } while (bVar1 != 0);
      iVar2 = 0;
LAB_00572d24:
      if ((iVar2 == 0) && (param_2->nTextVisible != 0)) {
        TextLabel::SetLabelText(param_2,"NULL");
      }
    }
  }
  return 0;
}
