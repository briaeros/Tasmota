/********************************************************************
 * Tasmota ctypes mapping headers
 *******************************************************************/
#ifndef __BE_CONSTOBJ_H__
#define __BE_CONSTOBJ_H__

#include "be_constobj.h"

enum {
    ctypes_i32    =  14,
    ctypes_i16    =  12,
    ctypes_i8     =  11,
    ctypes_u32    =   4,
    ctypes_u16    =   2,
    ctypes_u8     =   1,

    // big endian
    ctypes_be_i32 = -14,
    ctypes_be_i16 = -12,
    ctypes_be_i8  = -11,
    ctypes_be_u32 =  -4,
    ctypes_be_u16 =  -2,
    ctypes_be_u8  =  -1,

    // floating point
    ctypes_float  =   5,
    ctypes_double =  10,

    // pointer
    ctypes_ptr32  =   9,
    ctypes_ptr64  =  -9,

    ctypes_bf     =   0,    //bif-field
};

typedef struct be_ctypes_structure_item_t {
    const char * name;
    uint16_t  offset_bytes;
    uint8_t   offset_bits : 3;
    uint8_t   len_bits : 5;
    int8_t    type : 5;
    uint8_t   mapping : 3;
} be_ctypes_structure_item_t;

typedef struct be_ctypes_structure_t {
    uint16_t  size_bytes;       /* size in bytes */
    uint16_t  size_elt;         /* number of elements */
    const char **instance_mapping;  /* array of instance class names for automatic instanciation of class */
    const be_ctypes_structure_item_t * items;
} be_ctypes_structure_t;

typedef struct be_ctypes_class_t {
    const char * name;
    const be_ctypes_structure_t * definitions;
} be_ctypes_class_t;

typedef struct be_ctypes_classes_t {
    uint16_t  size;
    const char **instance_mapping;  /* array of instance class names for automatic instanciation of class */
    const be_ctypes_class_t * classes;
} be_ctypes_classes_t;

BE_EXPORT_VARIABLE const bclass be_class_ctypes;

static void ctypes_register_class(bvm *vm, const bclass * ctypes_class, const be_ctypes_structure_t * definitions) {
    be_pushntvclass(vm, ctypes_class);
    be_setglobal(vm, str(ctypes_class->name));
    be_pop(vm, 1);
}

// Define a sub-class of ctypes with only one member which points to the ctypes defintion
#define be_define_ctypes_class(_c_name, _def, _super, _name)                \
  be_local_class(_c_name,                                                   \
      0,                                                                    \
      _super,                                                               \
      be_nested_map(1,                                                      \
      ( (struct bmapnode*) &(const bmapnode[]) {                            \
          { be_nested_key("_def", 1985022181, 4, -1), be_const_comptr(_def) },\
      })),                                                                  \
      (be_nested_const_str(_name, 0, sizeof(_name)-1))                      \
  )

#endif // __BE_CONSTOBJ_H__
