#pragma once

struct clan_data {
  int id;
  char name[64];
  int maxslots;
  int maxperslot;
  int level;
  struct clan_bank* clanbanks;
};

struct clan_bank {
  unsigned int item_id, amount, owner, time, customIcon, customLook, pos;
  char real_name[64];
  unsigned int customLookColor, customIconColor, protected;
  char note[300];
};

extern struct DBMap* clan_db;

struct clan_data* clandb_search(int);
struct clan_data* clandb_searchexist(int);
char* clandb_name(int);
struct clan_data* clandb_searchname(const char*);

int clandb_read();
int clandb_term();
int clandb_init();
int clandb_add(void* sd, const char* name);