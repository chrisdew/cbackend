#ifndef DATA_H
#define DATA_H
#ifdef __cplusplus
extern "C" {
#endif

typedef struct group {
  const char* prod_grp;
  const char* desc;
} group_t;

typedef struct subgroup {
  const char* prod_grp;
  const char* smsgr_id;
  const char* desc;
} subgroup_t;

typedef struct stock {
  const char* key1p2;    // stock code
  const char* key2p2;    // short desc
  const char* desc1;     // description
  const char* prod_grp;  // product group
  const char dp_inqty;   // decimal places in quantity
  const long salprc_u;   // VAT excl price
  const long salprc_e;   // VAT includive price
  const long b_each;     // quantity in stock
  const long b_alloc;    // allocated qty
  const char* smsgr_id;  // subgroup
  const char** barcodes; // barcodes
} stock_t;

extern group_t data_group[];
extern subgroup_t data_subgroup[];
extern stock_t data_stock[];

extern group_t* data_get_groups();
extern subgroup_t* data_get_subgroups(const char* prod_grp);
extern stock_t* data_get_stock_by_group(const char *prod_grp);
extern stock_t* data_get_stock_by_subgroup(const char *prod_grp, const char *smsgr_id);
extern stock_t* data_get_stock_by_key1p2(const char *key1p2);
extern stock_t* data_get_stock_by_barcode(const char *barcode);

#ifdef __cplusplus
}
#endif
#endif

