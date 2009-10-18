/*
** Lua binding: CLuaInterface
** Generated automatically by tolua++-1.0.92 on Sun Oct 18 13:55:51 2009.
*/

#ifndef __cplusplus
#include "stdlib.h"
#endif
#include "string.h"

#include "tolua++.h"

/* Exported function */
TOLUA_API int  tolua_CLuaInterface_open (lua_State* tolua_S);

#include "CLuaInterface.h"

/* function to release collected object via destructor */
#ifdef __cplusplus

static int tolua_collect_uint8_t (lua_State* tolua_S)
{
 uint8_t* self = (uint8_t*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_uint16_t (lua_State* tolua_S)
{
 uint16_t* self = (uint16_t*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}
#endif


/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"CZone");
 tolua_usertype(tolua_S,"CCharacter");
 tolua_usertype(tolua_S,"uint16_t");
 tolua_usertype(tolua_S,"uint8_t");
}

/* method: baseOnType of class  CCharacter */
#ifndef TOLUA_DISABLE_tolua_CLuaInterface_CCharacter_baseOnType00
static int tolua_CLuaInterface_CCharacter_baseOnType00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCharacter",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCharacter* self = (CCharacter*)  tolua_tousertype(tolua_S,1,0);
  std::string otherType = ((std::string)  tolua_tocppstring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'baseOnType'", NULL);
#endif
  {
   self->baseOnType(otherType);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'baseOnType'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setStrength of class  CCharacter */
#ifndef TOLUA_DISABLE_tolua_CLuaInterface_CCharacter_setStrength00
static int tolua_CLuaInterface_CCharacter_setStrength00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCharacter",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCharacter* self = (CCharacter*)  tolua_tousertype(tolua_S,1,0);
  int newStrength = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setStrength'", NULL);
#endif
  {
   self->setStrength(newStrength);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setStrength'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getStrength of class  CCharacter */
#ifndef TOLUA_DISABLE_tolua_CLuaInterface_CCharacter_getStrength00
static int tolua_CLuaInterface_CCharacter_getStrength00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CCharacter",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CCharacter* self = (const CCharacter*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getStrength'", NULL);
#endif
  {
   uint16_t tolua_ret = (uint16_t)  self->getStrength();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((uint16_t)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"uint16_t");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(uint16_t));
     tolua_pushusertype(tolua_S,tolua_obj,"uint16_t");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getStrength'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: modifyStrength of class  CCharacter */
#ifndef TOLUA_DISABLE_tolua_CLuaInterface_CCharacter_modifyStrength00
static int tolua_CLuaInterface_CCharacter_modifyStrength00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCharacter",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCharacter* self = (CCharacter*)  tolua_tousertype(tolua_S,1,0);
  int strengthModifier = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'modifyStrength'", NULL);
#endif
  {
   self->modifyStrength(strengthModifier);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'modifyStrength'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setDexterity of class  CCharacter */
#ifndef TOLUA_DISABLE_tolua_CLuaInterface_CCharacter_setDexterity00
static int tolua_CLuaInterface_CCharacter_setDexterity00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCharacter",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCharacter* self = (CCharacter*)  tolua_tousertype(tolua_S,1,0);
  int newDexterity = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setDexterity'", NULL);
#endif
  {
   self->setDexterity(newDexterity);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setDexterity'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getDexterity of class  CCharacter */
#ifndef TOLUA_DISABLE_tolua_CLuaInterface_CCharacter_getDexterity00
static int tolua_CLuaInterface_CCharacter_getDexterity00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CCharacter",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CCharacter* self = (const CCharacter*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getDexterity'", NULL);
#endif
  {
   uint16_t tolua_ret = (uint16_t)  self->getDexterity();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((uint16_t)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"uint16_t");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(uint16_t));
     tolua_pushusertype(tolua_S,tolua_obj,"uint16_t");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getDexterity'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: modifyDexterity of class  CCharacter */
#ifndef TOLUA_DISABLE_tolua_CLuaInterface_CCharacter_modifyDexterity00
static int tolua_CLuaInterface_CCharacter_modifyDexterity00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCharacter",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCharacter* self = (CCharacter*)  tolua_tousertype(tolua_S,1,0);
  int dexterityModifier = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'modifyDexterity'", NULL);
#endif
  {
   self->modifyDexterity(dexterityModifier);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'modifyDexterity'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setVitality of class  CCharacter */
#ifndef TOLUA_DISABLE_tolua_CLuaInterface_CCharacter_setVitality00
static int tolua_CLuaInterface_CCharacter_setVitality00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCharacter",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCharacter* self = (CCharacter*)  tolua_tousertype(tolua_S,1,0);
  int newVitality = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setVitality'", NULL);
#endif
  {
   self->setVitality(newVitality);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setVitality'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getVitality of class  CCharacter */
#ifndef TOLUA_DISABLE_tolua_CLuaInterface_CCharacter_getVitality00
static int tolua_CLuaInterface_CCharacter_getVitality00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CCharacter",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CCharacter* self = (const CCharacter*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getVitality'", NULL);
#endif
  {
   uint16_t tolua_ret = (uint16_t)  self->getVitality();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((uint16_t)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"uint16_t");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(uint16_t));
     tolua_pushusertype(tolua_S,tolua_obj,"uint16_t");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getVitality'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: modifyVitality of class  CCharacter */
#ifndef TOLUA_DISABLE_tolua_CLuaInterface_CCharacter_modifyVitality00
static int tolua_CLuaInterface_CCharacter_modifyVitality00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCharacter",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCharacter* self = (CCharacter*)  tolua_tousertype(tolua_S,1,0);
  int vitalityModifier = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'modifyVitality'", NULL);
#endif
  {
   self->modifyVitality(vitalityModifier);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'modifyVitality'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setIntellect of class  CCharacter */
#ifndef TOLUA_DISABLE_tolua_CLuaInterface_CCharacter_setIntellect00
static int tolua_CLuaInterface_CCharacter_setIntellect00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCharacter",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCharacter* self = (CCharacter*)  tolua_tousertype(tolua_S,1,0);
  int newIntellect = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setIntellect'", NULL);
#endif
  {
   self->setIntellect(newIntellect);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setIntellect'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getIntellect of class  CCharacter */
#ifndef TOLUA_DISABLE_tolua_CLuaInterface_CCharacter_getIntellect00
static int tolua_CLuaInterface_CCharacter_getIntellect00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CCharacter",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CCharacter* self = (const CCharacter*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getIntellect'", NULL);
#endif
  {
   uint16_t tolua_ret = (uint16_t)  self->getIntellect();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((uint16_t)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"uint16_t");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(uint16_t));
     tolua_pushusertype(tolua_S,tolua_obj,"uint16_t");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getIntellect'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: modifyIntellect of class  CCharacter */
#ifndef TOLUA_DISABLE_tolua_CLuaInterface_CCharacter_modifyIntellect00
static int tolua_CLuaInterface_CCharacter_modifyIntellect00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCharacter",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCharacter* self = (CCharacter*)  tolua_tousertype(tolua_S,1,0);
  int intellectModifier = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'modifyIntellect'", NULL);
#endif
  {
   self->modifyIntellect(intellectModifier);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'modifyIntellect'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setWisdom of class  CCharacter */
#ifndef TOLUA_DISABLE_tolua_CLuaInterface_CCharacter_setWisdom00
static int tolua_CLuaInterface_CCharacter_setWisdom00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCharacter",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCharacter* self = (CCharacter*)  tolua_tousertype(tolua_S,1,0);
  int newWisdom = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setWisdom'", NULL);
#endif
  {
   self->setWisdom(newWisdom);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setWisdom'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getWisdom of class  CCharacter */
#ifndef TOLUA_DISABLE_tolua_CLuaInterface_CCharacter_getWisdom00
static int tolua_CLuaInterface_CCharacter_getWisdom00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CCharacter",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CCharacter* self = (const CCharacter*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getWisdom'", NULL);
#endif
  {
   uint16_t tolua_ret = (uint16_t)  self->getWisdom();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((uint16_t)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"uint16_t");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(uint16_t));
     tolua_pushusertype(tolua_S,tolua_obj,"uint16_t");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getWisdom'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: modifyWisdom of class  CCharacter */
#ifndef TOLUA_DISABLE_tolua_CLuaInterface_CCharacter_modifyWisdom00
static int tolua_CLuaInterface_CCharacter_modifyWisdom00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCharacter",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCharacter* self = (CCharacter*)  tolua_tousertype(tolua_S,1,0);
  int wisdomModifier = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'modifyWisdom'", NULL);
#endif
  {
   self->modifyWisdom(wisdomModifier);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'modifyWisdom'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setMaxHealth of class  CCharacter */
#ifndef TOLUA_DISABLE_tolua_CLuaInterface_CCharacter_setMaxHealth00
static int tolua_CLuaInterface_CCharacter_setMaxHealth00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCharacter",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCharacter* self = (CCharacter*)  tolua_tousertype(tolua_S,1,0);
  int newMaxHealth = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setMaxHealth'", NULL);
#endif
  {
   self->setMaxHealth(newMaxHealth);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setMaxHealth'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getMaxHealth of class  CCharacter */
#ifndef TOLUA_DISABLE_tolua_CLuaInterface_CCharacter_getMaxHealth00
static int tolua_CLuaInterface_CCharacter_getMaxHealth00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CCharacter",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CCharacter* self = (const CCharacter*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getMaxHealth'", NULL);
#endif
  {
   uint16_t tolua_ret = (uint16_t)  self->getMaxHealth();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((uint16_t)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"uint16_t");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(uint16_t));
     tolua_pushusertype(tolua_S,tolua_obj,"uint16_t");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getMaxHealth'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: modifyMaxHealth of class  CCharacter */
#ifndef TOLUA_DISABLE_tolua_CLuaInterface_CCharacter_modifyMaxHealth00
static int tolua_CLuaInterface_CCharacter_modifyMaxHealth00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCharacter",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCharacter* self = (CCharacter*)  tolua_tousertype(tolua_S,1,0);
  int maxHealthModifier = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'modifyMaxHealth'", NULL);
#endif
  {
   self->modifyMaxHealth(maxHealthModifier);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'modifyMaxHealth'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setMaxMana of class  CCharacter */
#ifndef TOLUA_DISABLE_tolua_CLuaInterface_CCharacter_setMaxMana00
static int tolua_CLuaInterface_CCharacter_setMaxMana00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCharacter",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCharacter* self = (CCharacter*)  tolua_tousertype(tolua_S,1,0);
  int newMaxMana = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setMaxMana'", NULL);
#endif
  {
   self->setMaxMana(newMaxMana);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setMaxMana'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getMaxMana of class  CCharacter */
#ifndef TOLUA_DISABLE_tolua_CLuaInterface_CCharacter_getMaxMana00
static int tolua_CLuaInterface_CCharacter_getMaxMana00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CCharacter",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CCharacter* self = (const CCharacter*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getMaxMana'", NULL);
#endif
  {
   uint16_t tolua_ret = (uint16_t)  self->getMaxMana();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((uint16_t)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"uint16_t");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(uint16_t));
     tolua_pushusertype(tolua_S,tolua_obj,"uint16_t");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getMaxMana'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: modifyMaxMana of class  CCharacter */
#ifndef TOLUA_DISABLE_tolua_CLuaInterface_CCharacter_modifyMaxMana00
static int tolua_CLuaInterface_CCharacter_modifyMaxMana00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCharacter",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCharacter* self = (CCharacter*)  tolua_tousertype(tolua_S,1,0);
  int maxManaModifier = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'modifyMaxMana'", NULL);
#endif
  {
   self->modifyMaxMana(maxManaModifier);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'modifyMaxMana'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setMaxEnergy of class  CCharacter */
#ifndef TOLUA_DISABLE_tolua_CLuaInterface_CCharacter_setMaxEnergy00
static int tolua_CLuaInterface_CCharacter_setMaxEnergy00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCharacter",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCharacter* self = (CCharacter*)  tolua_tousertype(tolua_S,1,0);
  int newMaxEnergy = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setMaxEnergy'", NULL);
#endif
  {
   self->setMaxEnergy(newMaxEnergy);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setMaxEnergy'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getMaxEnergy of class  CCharacter */
#ifndef TOLUA_DISABLE_tolua_CLuaInterface_CCharacter_getMaxEnergy00
static int tolua_CLuaInterface_CCharacter_getMaxEnergy00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CCharacter",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CCharacter* self = (const CCharacter*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getMaxEnergy'", NULL);
#endif
  {
   uint16_t tolua_ret = (uint16_t)  self->getMaxEnergy();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((uint16_t)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"uint16_t");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(uint16_t));
     tolua_pushusertype(tolua_S,tolua_obj,"uint16_t");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getMaxEnergy'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: modifyMaxEnergy of class  CCharacter */
#ifndef TOLUA_DISABLE_tolua_CLuaInterface_CCharacter_modifyMaxEnergy00
static int tolua_CLuaInterface_CCharacter_modifyMaxEnergy00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCharacter",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCharacter* self = (CCharacter*)  tolua_tousertype(tolua_S,1,0);
  int maxEnergyModifier = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'modifyMaxEnergy'", NULL);
#endif
  {
   self->modifyMaxEnergy(maxEnergyModifier);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'modifyMaxEnergy'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setMoveTexture of class  CCharacter */
#ifndef TOLUA_DISABLE_tolua_CLuaInterface_CCharacter_setMoveTexture00
static int tolua_CLuaInterface_CCharacter_setMoveTexture00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCharacter",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCharacter* self = (CCharacter*)  tolua_tousertype(tolua_S,1,0);
  int direction = ((int)  tolua_tonumber(tolua_S,2,0));
  std::string filename = ((std::string)  tolua_tocppstring(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setMoveTexture'", NULL);
#endif
  {
   self->setMoveTexture(direction,filename);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setMoveTexture'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setLifeTexture of class  CCharacter */
#ifndef TOLUA_DISABLE_tolua_CLuaInterface_CCharacter_setLifeTexture00
static int tolua_CLuaInterface_CCharacter_setLifeTexture00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCharacter",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCharacter* self = (CCharacter*)  tolua_tousertype(tolua_S,1,0);
  std::string filename = ((std::string)  tolua_tocppstring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setLifeTexture'", NULL);
#endif
  {
   self->setLifeTexture(filename);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setLifeTexture'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setWanderRadius of class  CCharacter */
#ifndef TOLUA_DISABLE_tolua_CLuaInterface_CCharacter_setWanderRadius00
static int tolua_CLuaInterface_CCharacter_setWanderRadius00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCharacter",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCharacter* self = (CCharacter*)  tolua_tousertype(tolua_S,1,0);
  int newWanderRadius = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setWanderRadius'", NULL);
#endif
  {
   self->setWanderRadius(newWanderRadius);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setWanderRadius'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getWanderRadius of class  CCharacter */
#ifndef TOLUA_DISABLE_tolua_CLuaInterface_CCharacter_getWanderRadius00
static int tolua_CLuaInterface_CCharacter_getWanderRadius00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CCharacter",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CCharacter* self = (const CCharacter*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getWanderRadius'", NULL);
#endif
  {
   uint16_t tolua_ret = (uint16_t)  self->getWanderRadius();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((uint16_t)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"uint16_t");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(uint16_t));
     tolua_pushusertype(tolua_S,tolua_obj,"uint16_t");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getWanderRadius'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setName of class  CCharacter */
#ifndef TOLUA_DISABLE_tolua_CLuaInterface_CCharacter_setName00
static int tolua_CLuaInterface_CCharacter_setName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCharacter",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCharacter* self = (CCharacter*)  tolua_tousertype(tolua_S,1,0);
  std::string newName = ((std::string)  tolua_tocppstring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setName'", NULL);
#endif
  {
   self->setName(newName);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getName of class  CCharacter */
#ifndef TOLUA_DISABLE_tolua_CLuaInterface_CCharacter_getName00
static int tolua_CLuaInterface_CCharacter_getName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CCharacter",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CCharacter* self = (const CCharacter*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getName'", NULL);
#endif
  {
   std::string tolua_ret = (std::string)  self->getName();
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setLevel of class  CCharacter */
#ifndef TOLUA_DISABLE_tolua_CLuaInterface_CCharacter_setLevel00
static int tolua_CLuaInterface_CCharacter_setLevel00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCharacter",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCharacter* self = (CCharacter*)  tolua_tousertype(tolua_S,1,0);
  int newLevel = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setLevel'", NULL);
#endif
  {
   self->setLevel(newLevel);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setLevel'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getLevel of class  CCharacter */
#ifndef TOLUA_DISABLE_tolua_CLuaInterface_CCharacter_getLevel00
static int tolua_CLuaInterface_CCharacter_getLevel00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CCharacter",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CCharacter* self = (const CCharacter*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getLevel'", NULL);
#endif
  {
   uint8_t tolua_ret = (uint8_t)  self->getLevel();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((uint8_t)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"uint8_t");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(uint8_t));
     tolua_pushusertype(tolua_S,tolua_obj,"uint8_t");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getLevel'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setMinDamage of class  CCharacter */
#ifndef TOLUA_DISABLE_tolua_CLuaInterface_CCharacter_setMinDamage00
static int tolua_CLuaInterface_CCharacter_setMinDamage00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCharacter",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCharacter* self = (CCharacter*)  tolua_tousertype(tolua_S,1,0);
  int newMinDamage = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setMinDamage'", NULL);
#endif
  {
   self->setMinDamage(newMinDamage);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setMinDamage'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getMinDamage of class  CCharacter */
#ifndef TOLUA_DISABLE_tolua_CLuaInterface_CCharacter_getMinDamage00
static int tolua_CLuaInterface_CCharacter_getMinDamage00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCharacter",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCharacter* self = (CCharacter*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getMinDamage'", NULL);
#endif
  {
   uint16_t tolua_ret = (uint16_t)  self->getMinDamage();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((uint16_t)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"uint16_t");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(uint16_t));
     tolua_pushusertype(tolua_S,tolua_obj,"uint16_t");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getMinDamage'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setMaxDamage of class  CCharacter */
#ifndef TOLUA_DISABLE_tolua_CLuaInterface_CCharacter_setMaxDamage00
static int tolua_CLuaInterface_CCharacter_setMaxDamage00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCharacter",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCharacter* self = (CCharacter*)  tolua_tousertype(tolua_S,1,0);
  int newMaxDamage = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setMaxDamage'", NULL);
#endif
  {
   self->setMaxDamage(newMaxDamage);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setMaxDamage'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getMaxDamage of class  CCharacter */
#ifndef TOLUA_DISABLE_tolua_CLuaInterface_CCharacter_getMaxDamage00
static int tolua_CLuaInterface_CCharacter_getMaxDamage00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCharacter",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCharacter* self = (CCharacter*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getMaxDamage'", NULL);
#endif
  {
   uint16_t tolua_ret = (uint16_t)  self->getMaxDamage();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((uint16_t)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"uint16_t");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(uint16_t));
     tolua_pushusertype(tolua_S,tolua_obj,"uint16_t");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getMaxDamage'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: DawnInterface::createNewMobType */
#ifndef TOLUA_DISABLE_tolua_CLuaInterface_DawnInterface_createNewMobType00
static int tolua_CLuaInterface_DawnInterface_createNewMobType00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_iscppstring(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  std::string typeID = ((std::string)  tolua_tocppstring(tolua_S,1,0));
  {
   CCharacter* tolua_ret = (CCharacter*)  DawnInterface::createNewMobType(typeID);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCharacter");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'createNewMobType'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: DawnInterface::getCurrentZone */
#ifndef TOLUA_DISABLE_tolua_CLuaInterface_DawnInterface_getCurrentZone00
static int tolua_CLuaInterface_DawnInterface_getCurrentZone00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnoobj(tolua_S,1,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CZone* tolua_ret = (CZone*)  DawnInterface::getCurrentZone();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CZone");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getCurrentZone'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: DawnInterface::addMobSpawnPoint */
#ifndef TOLUA_DISABLE_tolua_CLuaInterface_DawnInterface_addMobSpawnPoint00
static int tolua_CLuaInterface_DawnInterface_addMobSpawnPoint00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_iscppstring(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,6,"CZone",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,7,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  std::string mobID = ((std::string)  tolua_tocppstring(tolua_S,1,0));
  int x_pos = ((int)  tolua_tonumber(tolua_S,2,0));
  int y_pos = ((int)  tolua_tonumber(tolua_S,3,0));
  int respawn_rate = ((int)  tolua_tonumber(tolua_S,4,0));
  int do_respawn = ((int)  tolua_tonumber(tolua_S,5,0));
  CZone* zone = ((CZone*)  tolua_tousertype(tolua_S,6,0));
  {
   DawnInterface::addMobSpawnPoint(mobID,x_pos,y_pos,respawn_rate,do_respawn,zone);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'addMobSpawnPoint'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua_CLuaInterface_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_reg_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
  tolua_constant(tolua_S,"STOP",STOP);
  tolua_constant(tolua_S,"N",N);
  tolua_constant(tolua_S,"NE",NE);
  tolua_constant(tolua_S,"E",E);
  tolua_constant(tolua_S,"SE",SE);
  tolua_constant(tolua_S,"S",S);
  tolua_constant(tolua_S,"SW",SW);
  tolua_constant(tolua_S,"W",W);
  tolua_constant(tolua_S,"NW",NW);
  tolua_cclass(tolua_S,"CCharacter","CCharacter","",NULL);
  tolua_beginmodule(tolua_S,"CCharacter");
   tolua_function(tolua_S,"baseOnType",tolua_CLuaInterface_CCharacter_baseOnType00);
   tolua_function(tolua_S,"setStrength",tolua_CLuaInterface_CCharacter_setStrength00);
   tolua_function(tolua_S,"getStrength",tolua_CLuaInterface_CCharacter_getStrength00);
   tolua_function(tolua_S,"modifyStrength",tolua_CLuaInterface_CCharacter_modifyStrength00);
   tolua_function(tolua_S,"setDexterity",tolua_CLuaInterface_CCharacter_setDexterity00);
   tolua_function(tolua_S,"getDexterity",tolua_CLuaInterface_CCharacter_getDexterity00);
   tolua_function(tolua_S,"modifyDexterity",tolua_CLuaInterface_CCharacter_modifyDexterity00);
   tolua_function(tolua_S,"setVitality",tolua_CLuaInterface_CCharacter_setVitality00);
   tolua_function(tolua_S,"getVitality",tolua_CLuaInterface_CCharacter_getVitality00);
   tolua_function(tolua_S,"modifyVitality",tolua_CLuaInterface_CCharacter_modifyVitality00);
   tolua_function(tolua_S,"setIntellect",tolua_CLuaInterface_CCharacter_setIntellect00);
   tolua_function(tolua_S,"getIntellect",tolua_CLuaInterface_CCharacter_getIntellect00);
   tolua_function(tolua_S,"modifyIntellect",tolua_CLuaInterface_CCharacter_modifyIntellect00);
   tolua_function(tolua_S,"setWisdom",tolua_CLuaInterface_CCharacter_setWisdom00);
   tolua_function(tolua_S,"getWisdom",tolua_CLuaInterface_CCharacter_getWisdom00);
   tolua_function(tolua_S,"modifyWisdom",tolua_CLuaInterface_CCharacter_modifyWisdom00);
   tolua_function(tolua_S,"setMaxHealth",tolua_CLuaInterface_CCharacter_setMaxHealth00);
   tolua_function(tolua_S,"getMaxHealth",tolua_CLuaInterface_CCharacter_getMaxHealth00);
   tolua_function(tolua_S,"modifyMaxHealth",tolua_CLuaInterface_CCharacter_modifyMaxHealth00);
   tolua_function(tolua_S,"setMaxMana",tolua_CLuaInterface_CCharacter_setMaxMana00);
   tolua_function(tolua_S,"getMaxMana",tolua_CLuaInterface_CCharacter_getMaxMana00);
   tolua_function(tolua_S,"modifyMaxMana",tolua_CLuaInterface_CCharacter_modifyMaxMana00);
   tolua_function(tolua_S,"setMaxEnergy",tolua_CLuaInterface_CCharacter_setMaxEnergy00);
   tolua_function(tolua_S,"getMaxEnergy",tolua_CLuaInterface_CCharacter_getMaxEnergy00);
   tolua_function(tolua_S,"modifyMaxEnergy",tolua_CLuaInterface_CCharacter_modifyMaxEnergy00);
   tolua_function(tolua_S,"setMoveTexture",tolua_CLuaInterface_CCharacter_setMoveTexture00);
   tolua_function(tolua_S,"setLifeTexture",tolua_CLuaInterface_CCharacter_setLifeTexture00);
   tolua_function(tolua_S,"setWanderRadius",tolua_CLuaInterface_CCharacter_setWanderRadius00);
   tolua_function(tolua_S,"getWanderRadius",tolua_CLuaInterface_CCharacter_getWanderRadius00);
   tolua_function(tolua_S,"setName",tolua_CLuaInterface_CCharacter_setName00);
   tolua_function(tolua_S,"getName",tolua_CLuaInterface_CCharacter_getName00);
   tolua_function(tolua_S,"setLevel",tolua_CLuaInterface_CCharacter_setLevel00);
   tolua_function(tolua_S,"getLevel",tolua_CLuaInterface_CCharacter_getLevel00);
   tolua_function(tolua_S,"setMinDamage",tolua_CLuaInterface_CCharacter_setMinDamage00);
   tolua_function(tolua_S,"getMinDamage",tolua_CLuaInterface_CCharacter_getMinDamage00);
   tolua_function(tolua_S,"setMaxDamage",tolua_CLuaInterface_CCharacter_setMaxDamage00);
   tolua_function(tolua_S,"getMaxDamage",tolua_CLuaInterface_CCharacter_getMaxDamage00);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"DawnInterface",0);
  tolua_beginmodule(tolua_S,"DawnInterface");
   tolua_function(tolua_S,"createNewMobType",tolua_CLuaInterface_DawnInterface_createNewMobType00);
   tolua_function(tolua_S,"getCurrentZone",tolua_CLuaInterface_DawnInterface_getCurrentZone00);
   tolua_function(tolua_S,"addMobSpawnPoint",tolua_CLuaInterface_DawnInterface_addMobSpawnPoint00);
  tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_CLuaInterface (lua_State* tolua_S) {
 return tolua_CLuaInterface_open(tolua_S);
};
#endif

