/*
 * Entry: 004a4f67
 * Name: ParameterDB::FileData::FileData
 * Namespace: ParameterDB::FileData
 * Signature: FileData * FileData(FileData * this, char * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

FileData * __thiscall ParameterDB::FileData::FileData(FileData *this,char *param_1)

{
  char cVar1;
  bool bVar2;
  size_t _Size;
  char *_Str1;
  hash_map<unsigned_int,char_const_*,stdext::hash_compare<unsigned_int,std::less<unsigned_int>_>,std::allocator<std::pair<unsigned_int_const_,char_const_*>_>_>
  *this_00;
  uint uVar3;
  int iVar4;
  char **ppcVar5;
  char extraout_CL;
  int _C;
  int _C_00;
  char *extraout_ECX;
  char *extraout_ECX_00;
  char *extraout_ECX_01;
  char *pcVar6;
  char extraout_DL;
  char extraout_DL_00;
  char extraout_DL_01;
  char *pcVar7;
  hash_map<unsigned_int,char_const_*,stdext::hash_compare<unsigned_int,std::less<unsigned_int>_>,std::allocator<std::pair<unsigned_int_const_,char_const_*>_>_>
  *local_10;
  char *local_c;
  
  stdext::
  hash_map<unsigned_int,stdext::hash_map<unsigned_int,char_const_*,stdext::hash_compare<unsigned_int,std::less<unsigned_int>_>,std::allocator<std::pair<unsigned_int_const_,char_const_*>_>_>,stdext::hash_compare<unsigned_int,std::less<unsigned_int>_>,std::allocator<std::pair<unsigned_int_const_,stdext::hash_map<unsigned_int,char_const_*,stdext::hash_compare<unsigned_int,std::less<unsigned_int>_>,std::allocator<std::pair<unsigned_int_const_,char_const_*>_>_>_>_>_>
  ::
  hash_map<unsigned_int,stdext::hash_map<unsigned_int,char_const_*,stdext::hash_compare<unsigned_int,std::less<unsigned_int>_>,std::allocator<std::pair<unsigned_int_const_,char_const_*>_>_>,stdext::hash_compare<unsigned_int,std::less<unsigned_int>_>,std::allocator<std::pair<unsigned_int_const_,stdext::hash_map<unsigned_int,char_const_*,stdext::hash_compare<unsigned_int,std::less<unsigned_int>_>,std::allocator<std::pair<unsigned_int_const_,char_const_*>_>_>_>_>_>
            (&this->DB_map);
  this->DB_ref = 1;
  pcVar7 = this->DB_name;
  strncpy(pcVar7,param_1,0xe);
  _Size = GetItemSize(pcVar7);
  _Str1 = UseItem(pcVar7);
  pcVar7 = _Str1 + _Size;
  local_c = malloc(_Size);
  param_1 = (char *)0x0;
  this->DB_data = local_c;
  local_10 = stdext::
             hash_map<unsigned_int,stdext::hash_map<unsigned_int,char_const_*,stdext::hash_compare<unsigned_int,std::less<unsigned_int>_>,std::allocator<std::pair<unsigned_int_const_,char_const_*>_>_>,stdext::hash_compare<unsigned_int,std::less<unsigned_int>_>,std::allocator<std::pair<unsigned_int_const_,stdext::hash_map<unsigned_int,char_const_*,stdext::hash_compare<unsigned_int,std::less<unsigned_int>_>,std::allocator<std::pair<unsigned_int_const_,char_const_*>_>_>_>_>_>
             ::operator[](&this->DB_map,(uint *)&param_1);
  param_1 = (char *)0xffffffff;
  this_00 = stdext::
            hash_map<unsigned_int,stdext::hash_map<unsigned_int,char_const_*,stdext::hash_compare<unsigned_int,std::less<unsigned_int>_>,std::allocator<std::pair<unsigned_int_const_,char_const_*>_>_>,stdext::hash_compare<unsigned_int,std::less<unsigned_int>_>,std::allocator<std::pair<unsigned_int_const_,stdext::hash_map<unsigned_int,char_const_*,stdext::hash_compare<unsigned_int,std::less<unsigned_int>_>,std::allocator<std::pair<unsigned_int_const_,char_const_*>_>_>_>_>_>
            ::operator[](&this->DB_map,(uint *)&param_1);
  do {
    if (pcVar7 <= _Str1) {
      UnlockItem(this->DB_name);
      return this;
    }
    do {
      if ((' ' < *_Str1) || (bVar2 = isnewline((int)*_Str1), bVar2)) break;
      _Str1 = _Str1 + 1;
    } while (_Str1 < pcVar7);
    if (((_Str1 < pcVar7) && (*_Str1 == ';')) || ((*_Str1 == '/' && (_Str1[1] == '/')))) {
      while ((_Str1 < pcVar7 && (bVar2 = isnewline((int)*_Str1), !bVar2))) {
        _Str1 = _Str1 + 1;
      }
    }
    else if (_Str1 < pcVar7) {
      bVar2 = isnewline((int)*_Str1);
      if (!bVar2) {
        if (extraout_CL != '[') goto LAB_004a50c4;
        param_1 = (char *)0x811c9dc5;
        while (((_Str1 = _Str1 + 1, _Str1 < pcVar7 && (*_Str1 != ']')) &&
               (bVar2 = isnewline((int)*_Str1), !bVar2))) {
          uVar3 = tolower(_C);
          param_1 = (char *)((uVar3 & 0xff ^ (uint)param_1) * 0x1000193);
        }
        local_10 = stdext::
                   hash_map<unsigned_int,stdext::hash_map<unsigned_int,char_const_*,stdext::hash_compare<unsigned_int,std::less<unsigned_int>_>,std::allocator<std::pair<unsigned_int_const_,char_const_*>_>_>,stdext::hash_compare<unsigned_int,std::less<unsigned_int>_>,std::allocator<std::pair<unsigned_int_const_,stdext::hash_map<unsigned_int,char_const_*,stdext::hash_compare<unsigned_int,std::less<unsigned_int>_>,std::allocator<std::pair<unsigned_int_const_,char_const_*>_>_>_>_>_>
                   ::operator[](&this->DB_map,(uint *)&param_1);
        while ((_Str1 < pcVar7 && (bVar2 = isnewline((int)*_Str1), !bVar2))) {
          _Str1 = _Str1 + 1;
        }
      }
    }
    else {
LAB_004a50c4:
      param_1 = (char *)0x811c9dc5;
      if (_Str1 < pcVar7) {
        do {
          cVar1 = *_Str1;
          if (((cVar1 < '!') || (cVar1 == '=')) || (bVar2 = isnewline((int)cVar1), bVar2)) break;
          uVar3 = tolower(_C_00);
          param_1 = (char *)((uVar3 & 0xff ^ (uint)param_1) * 0x1000193);
          _Str1 = _Str1 + 1;
        } while (_Str1 < pcVar7);
        if (_Str1 < pcVar7) {
          do {
            if ((*_Str1 == '=') || (bVar2 = isnewline((int)*_Str1), bVar2)) break;
            _Str1 = _Str1 + 1;
          } while (_Str1 < pcVar7);
          if (_Str1 < pcVar7) {
            if (*_Str1 != '=') goto LAB_004a5158;
            bVar2 = isnewline(0x3d);
            if (bVar2) goto LAB_004a5158;
            do {
              _Str1 = _Str1 + 1;
LAB_004a5158:
            } while (((_Str1 < pcVar7) && (*_Str1 < '!')) &&
                    (bVar2 = isnewline((int)*_Str1), !bVar2));
          }
        }
      }
      iVar4 = _strnicmp(_Str1,"NULL",4);
      if (iVar4 != 0) {
        pcVar6 = local_c;
        if (*_Str1 == '\"') {
          while (((_Str1 = _Str1 + 1, _Str1 < pcVar7 && (*_Str1 != '\"')) &&
                 (bVar2 = isnewline((int)*_Str1), pcVar6 = extraout_ECX, !bVar2))) {
            *extraout_ECX = extraout_DL;
            pcVar6 = extraout_ECX + 1;
          }
        }
        else if (*_Str1 == '\'') {
          while (((_Str1 = _Str1 + 1, _Str1 < pcVar7 && (*_Str1 != '\'')) &&
                 (bVar2 = isnewline((int)*_Str1), pcVar6 = extraout_ECX_00, !bVar2))) {
            *extraout_ECX_00 = extraout_DL_00;
            pcVar6 = extraout_ECX_00 + 1;
          }
        }
        else {
          while (((_Str1 < pcVar7 && (' ' < *_Str1)) &&
                 (bVar2 = isnewline((int)*_Str1), pcVar6 = extraout_ECX_01, !bVar2))) {
            *extraout_ECX_01 = extraout_DL_01;
            pcVar6 = extraout_ECX_01 + 1;
            _Str1 = _Str1 + 1;
          }
        }
        *pcVar6 = '\0';
        ppcVar5 = stdext::
                  hash_map<unsigned_int,char_const_*,stdext::hash_compare<unsigned_int,std::less<unsigned_int>_>,std::allocator<std::pair<unsigned_int_const_,char_const_*>_>_>
                  ::operator[](local_10,(uint *)&param_1);
        *ppcVar5 = local_c;
        ppcVar5 = stdext::
                  hash_map<unsigned_int,char_const_*,stdext::hash_compare<unsigned_int,std::less<unsigned_int>_>,std::allocator<std::pair<unsigned_int_const_,char_const_*>_>_>
                  ::operator[](this_00,(uint *)&param_1);
        *ppcVar5 = local_c;
        local_c = pcVar6 + 1;
      }
      while ((_Str1 < pcVar7 && (bVar2 = isnewline((int)*_Str1), !bVar2))) {
        _Str1 = _Str1 + 1;
      }
    }
    if (*_Str1 == '\r') {
      _Str1 = _Str1 + 1;
    }
    if (*_Str1 == '\n') {
      _Str1 = _Str1 + 1;
    }
  } while( true );
}
