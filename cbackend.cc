#include <node.h>
#include <v8.h>
#include <stdlib.h>
#include "data.h"

using namespace v8;

Handle<Value> wrapStock(stock_t *stock);

const char* ToCString(const v8::String::Utf8Value& value) {
  return *value ? *value : "<string conversion failed>";
}

Handle<Value> GetGroups(const Arguments& args) {
  HandleScope scope;

  if (args.Length() > 0) {
    ThrowException(Exception::TypeError(String::New("Wrong number of arguments")));
    return scope.Close(Undefined());
  }

  Local<Array> arr = Array::New();
  group_t* groups = data_get_groups();
  for (int i = 0; groups[i].prod_grp != 0; i++) {
    Local<Object> obj = Object::New();
    obj->Set(String::NewSymbol("prod_grp"), String::New(groups[i].prod_grp));
    obj->Set(String::NewSymbol("desc"), String::New(groups[i].desc));
    char numStr[11]; // FIXME: possible issues around the lifetime of each numStr - do they need to persist beyond the call?
    snprintf(numStr, 10, "%i", i); 
    arr->Set(String::NewSymbol(numStr), obj);
  }
  return scope.Close(arr);
}

Handle<Value> GetSubgroups(const Arguments& args) {
  HandleScope scope;

  if (args.Length() != 1) {
    ThrowException(Exception::TypeError(String::New("Wrong number of arguments")));
    return scope.Close(Undefined());
  }

  if (!args[0]->IsString()) {
    ThrowException(Exception::TypeError(String::New("Wrong arguments")));
    return scope.Close(Undefined());
  }

  String::Utf8Value prod_grp_utf8(args[0]->ToString());
  const char *prod_grp = ToCString(prod_grp_utf8);

  Local<Array> arr = Array::New();
  subgroup_t* subgroups = data_get_subgroups(prod_grp);
  for (int i = 0; subgroups[i].prod_grp != 0; i++) {
    Local<Object> obj = Object::New();
    obj->Set(String::NewSymbol("prod_grp"), String::New(subgroups[i].prod_grp));
    obj->Set(String::NewSymbol("smsgr_id"), String::New(subgroups[i].smsgr_id));
    obj->Set(String::NewSymbol("desc"), String::New(subgroups[i].desc));
    char numStr[11]; // FIXME: possible issues around the lifetime of each numStr - do they need to persist beyond the call?
    snprintf(numStr, 10, "%i", i); 
    arr->Set(String::NewSymbol(numStr), obj);
  }
  free(subgroups);
  return scope.Close(arr);
}

Handle<Value> GetStockByGroup(const Arguments& args) {
  if (args.Length() != 1 && args.Length() != 2) {
    ThrowException(Exception::TypeError(String::New("Wrong number of arguments")));
    HandleScope scope;
    return scope.Close(Undefined());
  }

  if (!args[0]->IsString()) {
    ThrowException(Exception::TypeError(String::New("Wrong arguments")));
    HandleScope scope;
    return scope.Close(Undefined());
  }

  String::Utf8Value prod_grp_utf8(args[0]->ToString());
  const char *prod_grp = ToCString(prod_grp_utf8);

  stock_t* stock;
  if (args.Length() == 1) {
    stock = data_get_stock_by_group(prod_grp);
  } else {
    String::Utf8Value smsgr_id_utf8(args[1]->ToString());
    const char *smsgr_id = ToCString(smsgr_id_utf8);
    stock = data_get_stock_by_subgroup(prod_grp, smsgr_id);
  }

  return wrapStock(stock);
}


Handle<Value> GetStockByKey1P2(const Arguments& args) {

  if (args.Length() != 1) {
    ThrowException(Exception::TypeError(String::New("Wrong number of arguments")));
    HandleScope scope;
    return scope.Close(Undefined());
  }

  if (!args[0]->IsString()) {
    ThrowException(Exception::TypeError(String::New("Wrong arguments")));
    HandleScope scope;
    return scope.Close(Undefined());
  }

  String::Utf8Value key1p2_utf8(args[0]->ToString());
  const char *key1p2 = ToCString(key1p2_utf8);

  stock_t* stock = data_get_stock_by_key1p2(key1p2);

  return wrapStock(stock);
}


Handle<Value> GetStockByBarcode(const Arguments& args) {

  if (args.Length() != 1) {
    ThrowException(Exception::TypeError(String::New("Wrong number of arguments")));
    HandleScope scope;
    return scope.Close(Undefined());
  }

  if (!args[0]->IsString()) {
    ThrowException(Exception::TypeError(String::New("Wrong arguments")));
    HandleScope scope;
    return scope.Close(Undefined());
  }

  String::Utf8Value barcode_utf8(args[0]->ToString());
  const char *barcode = ToCString(barcode_utf8);

  stock_t* stock = data_get_stock_by_barcode(barcode);

  return wrapStock(stock);
}



Handle<Value> wrapStock(stock_t *stock) {
  HandleScope scope;
  Local<Array> arr = Array::New();
  for (int i = 0; stock[i].key1p2 != 0; i++) {
    Local<Object> obj = Object::New();
    obj->Set(String::NewSymbol("key1p2"), String::New(stock[i].key1p2));
    obj->Set(String::NewSymbol("key2p2"), String::New(stock[i].key2p2));
    obj->Set(String::NewSymbol("desc1"), String::New(stock[i].desc1));
    obj->Set(String::NewSymbol("prod_grp"), String::New(stock[i].prod_grp));
    obj->Set(String::NewSymbol("dp_inqty"), Number::New(stock[i].dp_inqty));
    obj->Set(String::NewSymbol("salprc_u"), Number::New(stock[i].salprc_u));
    obj->Set(String::NewSymbol("salprc_e"), Number::New(stock[i].salprc_e));
    obj->Set(String::NewSymbol("b_each"), Number::New(stock[i].b_each));
    obj->Set(String::NewSymbol("b_alloc"), Number::New(stock[i].b_alloc));
    obj->Set(String::NewSymbol("smsgr_id"), String::New(stock[i].smsgr_id));
    Local<Array> barcodes = Array::New();
    if (stock[i].barcodes != NULL) {
      for (int j = 0; stock[i].barcodes[j] != NULL; j++) {
        printf("debug %i, %i\n", i, j);
        char numStr[11]; // FIXME: possible issues around the lifetime of each numStr - do they need to persist beyond the call?
        snprintf(numStr, 10, "%i", j);
        barcodes->Set(String::NewSymbol(numStr), String::New(stock[i].barcodes[j]));
      }
    }

    obj->Set(String::NewSymbol("barcodes"), barcodes);

    char numStr[11]; // FIXME: possible issues around the lifetime of each numStr - do they need to persist beyond the call?
    snprintf(numStr, 10, "%i", i);
    arr->Set(String::NewSymbol(numStr), obj);
  }
  free(stock);
  return scope.Close(arr);
}



extern "C" void
init (Handle<Object> target)
{
  HandleScope scope;
  target->Set(String::New("hello"), String::New("world"));
  target->Set(String::New("get_groups"), FunctionTemplate::New(GetGroups)->GetFunction());
  target->Set(String::New("get_subgroups"), FunctionTemplate::New(GetSubgroups)->GetFunction());
  target->Set(String::New("get_stock_by_group"), FunctionTemplate::New(GetStockByGroup)->GetFunction());
  target->Set(String::New("get_stock_by_key1p2"), FunctionTemplate::New(GetStockByKey1P2)->GetFunction());
  target->Set(String::New("get_stock_by_barcode"), FunctionTemplate::New(GetStockByBarcode)->GetFunction());
}
