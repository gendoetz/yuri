#include "metan_cli.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "class_db.h"
#include "config.h"
#include "core.h"
#include "db_mysql.h"
#include "item_db.h"

char scheme[32];
int filecount;
Sql *sql_handle = NULL;

unsigned short swap16(unsigned short val) {
  int hi, lo;
  unsigned short y;

  hi = val / 256;
  lo = val % 256;

  y = (lo * 256) + hi;

  return y;
}

int output_meta(char *filename, int num, unsigned int list[], int max) {
  FILE *fp;
  int offset;
  int x;
  char buf[64];
  char buf1;
  unsigned short buf2;

  if (max < ((num + 1) * 1000)) {
    offset = max - (num * 1000);
  } else {
    offset = (num + 1) * 1000;
  }

  fp = fopen(filename, "wb");

  buf2 = swap16(offset);  // set the size
  fwrite(&buf2, 2, 1, fp);

  for (x = (num * 1000); x < offset + (num * 1000); x++) {
    buf1 = strlen(itemdb_name(list[x]));
    fwrite(&buf1, 1, 1, fp);                    // write namelen
    fwrite(itemdb_name(list[x]), 1, buf1, fp);  // write name

    buf2 = swap16(20);
    fwrite(&buf2, 2, 1, fp);  // write 20

    memset(buf, 0, 64);
    sprintf(buf, "%d", itemdb_mightreq(list[x]));
    buf2 = swap16(strlen(buf));
    fwrite(&buf2, 2, 1, fp);          // MightReq len
    fwrite(buf, 1, strlen(buf), fp);  // MightReq

    memset(buf, 0, 64);
    sprintf(buf, "%d", itemdb_price(list[x]));
    buf2 = swap16(strlen(buf));

    fwrite(&buf2, 2, 1, fp);
    fwrite(buf, 1, strlen(buf), fp);

    memset(buf, 0, 64);
    sprintf(buf, "%d", itemdb_dura(list[x]));
    buf2 = swap16(strlen(buf));
    fwrite(&buf2, 2, 1, fp);
    fwrite(buf, 1, strlen(buf), fp);

    memset(buf, 0, 64);
    sprintf(buf, "%d", itemdb_ac(list[x]));
    buf2 = swap16(strlen(buf));
    fwrite(&buf2, 2, 1, fp);
    fwrite(buf, 1, strlen(buf), fp);

    memset(buf, 0, 64);
    sprintf(buf, "%d", itemdb_hit(list[x]));
    buf2 = swap16(strlen(buf));
    fwrite(&buf2, 2, 1, fp);
    fwrite(buf, 1, strlen(buf), fp);

    memset(buf, 0, 64);
    sprintf(buf, "%d", itemdb_dam(list[x]));
    buf2 = swap16(strlen(buf));
    fwrite(&buf2, 2, 1, fp);
    fwrite(buf, 1, strlen(buf), fp);

    memset(buf, 0, 64);
    sprintf(buf, "%d", itemdb_vita(list[x]));
    buf2 = swap16(strlen(buf));
    fwrite(&buf2, 2, 1, fp);
    fwrite(buf, 1, strlen(buf), fp);

    memset(buf, 0, 64);
    sprintf(buf, "%d", itemdb_mana(list[x]));
    buf2 = swap16(strlen(buf));
    fwrite(&buf2, 2, 1, fp);
    fwrite(buf, 1, strlen(buf), fp);

    memset(buf, 0, 64);
    sprintf(buf, "%d", itemdb_might(list[x]));
    buf2 = swap16(strlen(buf));
    fwrite(&buf2, 2, 1, fp);
    fwrite(buf, 1, strlen(buf), fp);

    memset(buf, 0, 64);
    sprintf(buf, "%d", itemdb_grace(list[x]));
    buf2 = swap16(strlen(buf));
    fwrite(&buf2, 2, 1, fp);
    fwrite(buf, 1, strlen(buf), fp);

    memset(buf, 0, 64);
    sprintf(buf, "%d", itemdb_will(list[x]));
    buf2 = swap16(strlen(buf));
    fwrite(&buf2, 2, 1, fp);
    fwrite(buf, 1, strlen(buf), fp);

    memset(buf, 0, 64);
    sprintf(buf, "%d", itemdb_wisdom(list[x]));  // Wisdom increase
    buf2 = swap16(strlen(buf));
    fwrite(&buf2, 2, 1, fp);
    fwrite(buf, 1, strlen(buf), fp);

    memset(buf, 0, 64);
    sprintf(buf, "%d", itemdb_con(list[x]));  // etc2 //Con

    buf2 = swap16(strlen(buf));
    fwrite(&buf2, 2, 1, fp);
    fwrite(buf, 1, strlen(buf), fp);

    memset(buf, 0, 64);
    sprintf(buf, "%d", classdb_path(itemdb_class(list[x])));
    buf2 = swap16(strlen(buf));
    fwrite(&buf2, 2, 1, fp);
    fwrite(buf, 1, strlen(buf), fp);

    memset(buf, 0, 64);
    sprintf(buf, "%d", itemdb_rank(list[x]));  // rank
    buf2 = swap16(strlen(buf));
    fwrite(&buf2, 2, 1, fp);
    fwrite(buf, 1, strlen(buf), fp);

    memset(buf, 0, 64);
    sprintf(buf, "%d", itemdb_level(list[x]));
    buf2 = swap16(strlen(buf));
    fwrite(&buf2, 2, 1, fp);
    fwrite(buf, 1, strlen(buf), fp);

    memset(buf, 0, 64);
    sprintf(buf, "%d", itemdb_healing(list[x]));
    buf2 = swap16(strlen(buf));
    fwrite(&buf2, 2, 1, fp);
    fwrite(buf, 1, strlen(buf), fp);

    memset(buf, 0, 64);
    sprintf(buf, "%d", itemdb_protection(list[x]));
    buf2 = swap16(strlen(buf));
    fwrite(&buf2, 2, 1, fp);
    fwrite(buf, 1, strlen(buf), fp);

    memset(buf, 0, 64);
    if (itemdb_minSdam(list[x]) == 0) {
      sprintf(buf, "%d", 0);
      buf2 = swap16(strlen(buf));
    } else {
      sprintf(buf, "%dm%d", itemdb_minSdam(list[x]), itemdb_maxSdam(list[x]));
      buf2 = swap16(strlen(buf));
    }
    fwrite(&buf2, 2, 1, fp);
    fwrite(buf, 1, strlen(buf), fp);

    memset(buf, 0, 64);
    if (itemdb_minLdam(list[x]) == 0) {
      if (itemdb_minSdam(list[x]) == 0) {
        sprintf(buf, "%d", 0);
        buf2 = swap16(strlen(buf));
      } else {
        sprintf(buf, "%dm%d", itemdb_minSdam(list[x]), itemdb_maxSdam(list[x]));
        buf2 = swap16(strlen(buf));
      }
    } else {
      sprintf(buf, "%dm%d", itemdb_minLdam(list[x]), itemdb_maxLdam(list[x]));
      buf2 = swap16(strlen(buf));
    }
    fwrite(&buf2, 2, 1, fp);
    fwrite(buf, 1, strlen(buf), fp);
  }
  fclose(fp);

  return 0;
}

int main(int argc, char **argv) {
  char filename[128];
  int x = 0;
  unsigned int id;
  unsigned int charicinfo[100000];
  unsigned int iteminfo[100000];
  int ci_max = 0;
  int ii_max = 0;
  int ci_count = 0;
  int ii_count = 0;
  int a, c;

  config_read("conf/server.yaml");
  // sql_init();
  sql_handle = Sql_Malloc();
  if (sql_handle == NULL) {
    Sql_ShowDebug(sql_handle);
    exit(1);
  }
  if (SQL_ERROR == Sql_Connect(sql_handle, sql_id, sql_pw, sql_ip,
                               (uint16_t)sql_port, sql_db)) {
    Sql_ShowDebug(sql_handle);
    Sql_Free(sql_handle);
    exit(1);
  }
  itemdb_init();   // Load itemdb
  classdb_init();  // Load classdb

  SqlStmt *stmt = SqlStmt_Malloc(sql_handle);

  if (stmt == NULL) {
    SqlStmt_ShowDebug(stmt);
    return 0;
  }

  if (SQL_ERROR ==
          SqlStmt_Prepare(stmt,
                          "SELECT `ItmId` FROM `Items` WHERE `ItmType` > 2 AND "
                          "`ItmType` < 17 ORDER BY `ItmId`") ||
      SQL_ERROR == SqlStmt_Execute(stmt) ||
      SQL_ERROR ==
          SqlStmt_BindColumn(stmt, 0, SQLDT_UINT, &id, 0, NULL, NULL)) {
    SqlStmt_ShowDebug(stmt);
    SqlStmt_Free(stmt);
    return 0;
  }

  x = SqlStmt_NumRows(stmt);

  ci_max = x;
  for (a = 0; a < ci_max && SQL_SUCCESS == SqlStmt_NextRow(stmt); a++) {
    charicinfo[ci_count] = id;
    ci_count++;
  }

  if (SQL_ERROR ==
          SqlStmt_Prepare(stmt,
                          "SELECT `ItmId` FROM `Items` WHERE `ItmType` < 3 OR "
                          "`ItmType` > 16 ORDER BY `ItmId`") ||
      SQL_ERROR == SqlStmt_Execute(stmt) ||
      SQL_ERROR ==
          SqlStmt_BindColumn(stmt, 0, SQLDT_UINT, &id, 0, NULL, NULL)) {
    SqlStmt_ShowDebug(stmt);
    SqlStmt_Free(stmt);
    return 0;
  }

  x = SqlStmt_NumRows(stmt);
  ii_max = x;
  for (c = 0; c < ii_max && SQL_SUCCESS == SqlStmt_NextRow(stmt); c++) {
    iteminfo[ii_count] = id;
    ii_count++;
  }

  SqlStmt_Free(stmt);

  filecount = ci_max / 1000 + 1;
  for (x = 0; x < filecount; x++) {
    sprintf(filename, "%sCharicInfo%d", meta_dir, x);
    printf("	%s\n", filename);

    output_meta(filename, x, charicinfo, ci_max);
  }

  filecount = ii_max / 1000 + 1;
  if (ii_max > 0) {
    for (x = 0; x < filecount; x++) {
      sprintf(filename, "%sItemInfo%d", meta_dir, x);
      printf("	%s\n", filename);
      output_meta(filename, x, iteminfo, ii_max);
    }
  }
  return 0;
}