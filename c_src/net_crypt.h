#pragma once

#define SWAP16(x) (short)(((x) << 8) | ((x) >> 8))
#define SWAP32(x)                                                             \
  (int)(((x) << 24) | (((x) << 8) & 0x00FF0000) | (((x) >> 8) & 0x0000FF00) | \
        ((x) >> 24))

#define RAND_INC rand() % 0xFF
#define USE_RANDOM_INDEXES

void tk_crypt_static(unsigned char* buffer);
void tk_crypt_dynamic(unsigned char* buffer, const char* key);

int encrypt(int fd);
int decrypt(int fd);

char* generate_hashvalues(const char*, char*, int);
char* populate_table(const char*, char*, int);
int set_packet_indexes(unsigned char*);
char* generate_key2(unsigned char*, char*, char*, int);
char* generate_key(const char*, char*, int);