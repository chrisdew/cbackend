#include "data.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

group_t data_group[] = {
  { "71", "Starters" },
  { "72", "Mains" },
  { "73", "Sides" },
  { "74", "Deserts" },
  { "75", "Drinks" },
  { "76", "Alcoholic Drinks" },
  { NULL, NULL }
};

subgroup_t data_subgroup[] = {
  { "72", "01", "Meat" },
  { "72", "02", "Fish" },
  { "72", "03", "Vegetarian" },
  { "75", "01", "Hot" },
  { "75", "02", "Cold" },
  { NULL, NULL, NULL }
};

/*
const char *barcodes0001[] = {"12345", "23456", NULL};
const char *barcodes0002[] = {"34567", "45678", NULL};
const char *barcodes0003[] = {"56789", "67890", NULL};
const char *barcodes0005[] = {"78901", NULL};

stock_t data_stock[] = {
  { "0001", "Soup",  "Tomato Soup",     "71", 0, 100, 120, 10, 0, "",   barcodes0001 },
  { "0002", "Melon", "Melon and Ham",   "71", 0, 200, 240, 10, 0, "",   barcodes0002 },
  { "0003", "Stew",  "Beef Stew",       "72", 0, 400, 480, 10, 0, "01", barcodes0003 },
  { "0004", "Steak", "Steak and Chips", "72", 0, 500, 600, 10, 0, "01", NULL         },
  { "0005", "Salmon","Salmon Fillet",   "72", 0, 400, 480, 10, 0, "02", barcodes0005 },
  { "0006", "Fish",  "Fish and Chips",  "72", 0, 500, 600, 10, 0, "02", NULL         },
  { "0007", "Bake",  "Vegetable Bake",  "72", 0, 500, 600, 10, 0, "03", NULL         },
  { NULL,   NULL,    NULL,              NULL, 0,   0,   0,  0, 0, NULL, NULL         }
};
*/
stock_t data_stock[] = {
  { "0001", "Soup",  "Tomato Soup",     "71", 0, 100, 120, 10, 0, "",   (const char*[]){"12345", "23456", NULL} },
  { "0002", "Melon", "Melon and Ham",   "71", 0, 200, 240, 10, 0, "",   (const char*[]){"34567", "45678", NULL} },
  { "0003", "Stew",  "Beef Stew",       "72", 0, 400, 480, 10, 0, "01", (const char*[]){"56789", "67890", NULL} },
  { "0004", "Steak", "Steak and Chips", "72", 0, 500, 600, 10, 0, "01", NULL                                    },
  { "0005", "Salmon","Salmon Fillet",   "72", 0, 400, 480, 10, 0, "02", (const char*[]){"78901", NULL}          },
  { "0006", "Fish",  "Fish and Chips",  "72", 0, 500, 600, 10, 0, "02", NULL                                    },
  { "0007", "Bake",  "Vegetable Bake",  "72", 0, 500, 600, 10, 0, "03", NULL                                    },
  { NULL,   NULL,    NULL,              NULL, 0,   0,   0,  0, 0, NULL, NULL                                    }
};

group_t* data_get_groups(void) {
  return data_group;
}

subgroup_t* data_get_subgroups(const char *prod_grp) {
  subgroup_t* results = NULL;
  int j = 0; // destination counter
  for (int i = 0; data_subgroup[i].prod_grp != NULL; i++) {
    if (strcmp(prod_grp, data_subgroup[i].prod_grp) == 0) { 
      results = (subgroup_t *) realloc(results, sizeof(subgroup_t) * (j + 1));
      memmove(&results[j], &data_subgroup[i], sizeof(subgroup_t));
      j++;
    }
  }
  results = (subgroup_t *) realloc(results, sizeof(subgroup_t) * (j + 1));
  results[j].prod_grp = NULL; // terminate the results
  return results;
}

stock_t* data_get_stock_by_group(const char *prod_grp) {
  stock_t* results = NULL;
  int j = 0; // destination counter
  for (int i = 0; data_stock[i].prod_grp != NULL; i++) {
    if (strcmp(prod_grp, data_stock[i].prod_grp) == 0) { 
      results = (stock_t *) realloc(results, sizeof(stock_t) * (j + 1));
      memmove(&results[j], &data_stock[i], sizeof(stock_t));
      j++;
    }
  }
  results = (stock_t *) realloc(results, sizeof(stock_t) * (j + 1));
  results[j].key1p2 = NULL; // terminate the results
  return results;
}

stock_t* data_get_stock_by_subgroup(const char *prod_grp, const char *smsgr_id) {
  stock_t* results = NULL;
  int j = 0; // destination counter
  for (int i = 0; data_stock[i].prod_grp != NULL; i++) {
    if (strcmp(prod_grp, data_stock[i].prod_grp) == 0 && strcmp(smsgr_id, data_stock[i].smsgr_id) == 0) {
      results = (stock_t *) realloc(results, sizeof(stock_t) * (j + 1));
      memmove(&results[j], &data_stock[i], sizeof(stock_t));
      j++;
    }
  }
  results = (stock_t *) realloc(results, sizeof(stock_t) * (j + 1));
  results[j].key1p2 = NULL; // terminate the results
  return results;
}

stock_t* data_get_stock_by_key1p2(const char *key1p2) {
  stock_t* results = NULL;
  int j = 0; // destination counter
  for (int i = 0; data_stock[i].prod_grp != NULL; i++) {
    if (strcmp(key1p2, data_stock[i].key1p2) == 0) {
      results = (stock_t *) realloc(results, sizeof(stock_t) * (j + 1));
      memmove(&results[j], &data_stock[i], sizeof(stock_t));
      j++;
    }
  }
  results = (stock_t *) realloc(results, sizeof(stock_t) * (j + 1));
  results[j].key1p2 = NULL; // terminate the results
  return results;
}

stock_t* data_get_stock_by_barcode(const char *barcode) {
  stock_t* results = NULL;
  int j = 0; // destination counter
  for (int i = 0; data_stock[i].prod_grp != NULL; i++) {
    if (data_stock[i].barcodes == NULL) continue;
    for (int b = 0; data_stock[i].barcodes[b] != NULL; b++) {
      if (strcmp(barcode, data_stock[i].barcodes[b]) == 0) {
        results = (stock_t *) realloc(results, sizeof(stock_t) * (j + 1));
        memmove(&results[j], &data_stock[i], sizeof(stock_t));
        j++;
      }
    }
  }
  results = (stock_t *) realloc(results, sizeof(stock_t) * (j + 1));
  results[j].key1p2 = NULL; // terminate the results
  return results;
}






