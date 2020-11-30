#pragma once

#include <stdarg.h>

#include "map_server.h"
#include "mmo.h"

int pc_requestmp(USER *);
int pc_sendpong(int, int);
int pc_item_timer(int, int);
int pc_magic_startup(USER *);
int pc_givexp(USER *, unsigned int, unsigned int);
int pc_runfloor_sub(USER *);
int pc_isequip(USER *, int);
int pc_setpos(USER *, int, int, int);
int pc_warp(USER *, int, int, int);
int pc_calcstat(USER *);
int pc_loaditem(USER *);
int pc_loadequip(USER *);
int pc_additem(USER *, struct item *);
int pc_additemnolog(USER *, struct item *);
int pc_delitem(USER *, int, int, int);
int pc_useitem(USER *, int);
int pc_dropitemmap(USER *, int, int);
int pc_getitemmap(USER *, int);
int pc_getitemsaround(USER *);
int pc_getitemscript(USER *, int);
int pc_changeitem(USER *, int, int);
int pc_equipitem(USER *, int);
int pc_equipscript(USER *);
int pc_unequip(USER *, int);
int pc_unequipscript(USER *);
int pc_heal(USER *, int, int, int);
int pc_res(USER *);
int pc_die(USER *);
int pc_diescript(USER *);
float pc_calcdamage(USER *);
int pc_calcdam(USER *);
int pc_loadmagic(USER *);
int pc_isinvenspace(USER *, int, int, const char *, unsigned int, unsigned int,
                    unsigned int, unsigned int);
int pc_isinvenitemspace(USER *, int, int, int, char *);
int pc_checklevel(USER *);
int pc_readreg(USER *, int);
int pc_setreg(USER *, int, int);
char *pc_readregstr(USER *, int);
int pc_setregstr(USER *, int, char *);
int pc_readglobalreg(USER *, const char *);
int pc_setglobalreg(USER *, const char *, unsigned long);
int pc_readparam(USER *, int);
int pc_setparam(USER *, int, int);
int pc_starttimer(USER *);
int pc_timer(int, int);
int pc_stoptimer(USER *);
int pc_healing(int, int);
int pc_uncast(USER *);
int pc_checkformail(USER *);
int pc_handle_item(int, int);
int pc_handle_item_sub(struct block_list *, va_list);
int pc_loaditemrealname(USER *);
int pc_loadequiprealname(USER *);
int pc_addtocurrent(struct block_list *, va_list);
int bl_duratimer(int, int);
int bl_secondduratimer(int, int);
int bl_thirdduratimer(int, int);
int bl_fourthduratimer(int, int);
int bl_fifthduratimer(int, int);
int bl_aethertimer(int, int);
int pc_saveacctregistry(USER *, int);
int pc_setacctreg(USER *, const char *, int);
int pc_readacctreg(USER *, const char *);
int pc_setnpcintreg(USER *, const char *, int);
int pc_readnpcintreg(USER *, const char *);
int pc_setquestreg(USER *, const char *, int);
int pc_readquestreg(USER *, const char *);
int pc_scripttimer(int, int);
int pc_atkspeed(int, int);
int pc_disptimertick(int, int);
char *pc_readglobalregstring(USER *, const char *);
int pc_setglobalregstring(USER *, const char *, const char *);
int pc_reload_aether(USER *);