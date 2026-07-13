/*
 * Entry: 00512697
 * Name: IParse_Get_Runtime_Struct_Field
 * Namespace: Global
 * Signature: char * IParse_Get_Runtime_Struct_Field(void * param_1, char * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

char * __cdecl IParse_Get_Runtime_Struct_Field(void *param_1,char *param_2)

{
  char cVar1;
  byte bVar2;
  char *pcVar3;
  int iVar4;
  byte *pbVar5;
  int iVar6;
  byte *pbVar7;
  _field_def *p_Var8;
  bool bVar9;
  double local_b50 [30];
  int local_a60 [30];
  int local_9e8 [2];
  int local_9e0;
  _variable_struct *local_970;
  char *local_96c;
  char local_968 [400];
  byte local_7d8 [2000];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  pcVar3 = param_2;
  do {
    cVar1 = *pcVar3;
    pcVar3 = pcVar3 + 1;
  } while (cVar1 != '\0');
  local_96c = calloc(1,(size_t)(pcVar3 + (1 - (int)(param_2 + 1))));
  iVar6 = (int)local_96c - (int)param_2;
  do {
    cVar1 = *param_2;
    param_2[iVar6] = cVar1;
    param_2 = param_2 + 1;
  } while (cVar1 != '\0');
  IParse_Save_Only_Alpha_Numeric(&local_96c,IParse_Is_OK_Char_Not_Float);
  IParse_Parse_New_Command
            (local_96c,(int *)&local_970,local_9e8,local_b50,(char (*) [80])local_968,local_a60);
  local_970 = IParse_Which_Variable(param_1,local_968);
  if (local_970 == (_variable_struct *)0x0) {
    free(local_96c);
  }
  else {
    iVar6 = local_970->the_struct_el->struct_length * local_9e0;
    for (p_Var8 = local_970->the_struct_el->the_definition; p_Var8 != (_field_def *)0x0;
        p_Var8 = p_Var8->next_field) {
      pbVar5 = (byte *)p_Var8->field_name;
      pbVar7 = local_7d8;
      do {
        bVar2 = *pbVar5;
        bVar9 = bVar2 < *pbVar7;
        if (bVar2 != *pbVar7) {
LAB_0051278a:
          iVar4 = (1 - (uint)bVar9) - (uint)(bVar9 != 0);
          goto LAB_0051278f;
        }
        if (bVar2 == 0) break;
        bVar2 = pbVar5[1];
        bVar9 = bVar2 < pbVar7[1];
        if (bVar2 != pbVar7[1]) goto LAB_0051278a;
        pbVar5 = pbVar5 + 2;
        pbVar7 = pbVar7 + 2;
      } while (bVar2 != 0);
      iVar4 = 0;
LAB_0051278f:
      if (iVar4 == 0) {
        free(local_96c);
        return local_970->string_value + iVar6;
      }
      iVar6 = iVar6 + p_Var8->field_length;
    }
    free(local_96c);
  }
  return (char *)0x0;
}
