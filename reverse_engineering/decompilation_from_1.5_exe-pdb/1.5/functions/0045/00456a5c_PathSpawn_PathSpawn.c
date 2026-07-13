/*
 * Entry: 00456a5c
 * Name: PathSpawn::PathSpawn
 * Namespace: PathSpawn
 * Signature: PathSpawn * PathSpawn(PathSpawn * this, AiMission * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

PathSpawn * __thiscall PathSpawn::PathSpawn(PathSpawn *this,AiMission *param_1)

{
  char cVar1;
  uint uVar2;
  AiPath *pAVar3;
  float fVar4;
  bool bVar5;
  AiPath **ppAVar6;
  int iVar7;
  char *pcVar8;
  char *pcVar9;
  char *pcVar10;
  _Const_iterator<1> local_44;
  _Const_iterator<1> local_3c;
  _Const_iterator<1> local_34;
  ParameterDB local_2c;
  char local_28 [16];
  char local_18 [16];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  AiProcess::AiProcess((AiProcess *)this,param_1,(GameObject *)0x0);
  this->_padding_ = (int)&_vftable_;
  this->state = INIT;
  memset(this->pup,0,0x1130);
  this->number = 0;
  std::list<AiPath_*,std::allocator<AiPath_*>_>::_Const_iterator<1>::_Const_iterator<1>
            (&local_3c,(AiPath::pathList._Myhead)->_Next,&AiPath::pathList);
  uVar2 = this->number;
  while( true ) {
    if (99 < uVar2) {
      return this;
    }
    std::list<AiPath_*,std::allocator<AiPath_*>_>::_Const_iterator<1>::_Const_iterator<1>
              (&local_44,AiPath::pathList._Myhead,&AiPath::pathList);
    bVar5 = std::list<AiPath_*,std::allocator<AiPath_*>_>::_Const_iterator<1>::operator==
                      (&local_34,&local_44);
    if (bVar5) break;
    ppAVar6 = std::list<AiPath_*,std::allocator<AiPath_*>_>::_Const_iterator<1>::operator*
                        (&local_34);
    pAVar3 = *ppAVar6;
    if (((pAVar3->label != (char *)0x0) && (iVar7 = _stricmp(pAVar3->label,"edge_path"), iVar7 != 0)
        ) && (iVar7 = _strnicmp(pAVar3->label,"path_",5), iVar7 != 0)) {
      pcVar10 = pAVar3->label;
      for (pcVar8 = this->pup[this->number].odf;
          ((cVar1 = *pcVar10, cVar1 != '_' && (cVar1 != '\0')) &&
          (pcVar8 < this->pup[this->number].odf + 9)); pcVar8 = pcVar8 + 1) {
        *pcVar8 = cVar1;
        pcVar10 = pcVar10 + 1;
      }
      *pcVar8 = '\0';
      sprintf(local_18,"%s.odf",this->pup[this->number].odf);
      iVar7 = ItemExists(local_18);
      if (iVar7 != 0) {
        ParameterDB::ParameterDB(&local_2c,local_18);
        ParameterDB::Get(&local_2c,0xd3dd9cec,0x92d04727,local_28,0x10,(char *)0x0);
        if (local_28[0] != '\0') {
          pcVar9 = pAVar3->label;
          pcVar8 = this->pup[this->number].str;
          do {
            cVar1 = *pcVar9;
            pcVar9 = pcVar9 + 1;
            *pcVar8 = cVar1;
            pcVar8 = pcVar8 + 1;
          } while (cVar1 != '\0');
          if (*pcVar10 == '_') {
            local_3c._Ptr = (_Node *)atoi(pcVar10 + 1);
            if ((int)local_3c._Ptr < 1) {
              fVar4 = 10.0;
            }
            else {
              fVar4 = (float)(int)local_3c._Ptr;
            }
            this->pup[this->number].respawn = fVar4;
          }
          this->number = this->number + 1;
        }
        ParameterDB::~ParameterDB(&local_2c);
      }
    }
    std::list<AiPath_*,std::allocator<AiPath_*>_>::_Const_iterator<1>::operator++(&local_34);
    uVar2 = this->number;
  }
  return this;
}
