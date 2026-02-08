#include <iostream>
#include <unordered_map>

class TypeNull;

template <typename HEAD, typename TAIL> struct TypeList {
  typedef HEAD Head;
  typedef TAIL Tail;
};

// enough for now.. can be expand at any point in time as needed
#define TYPELIST_1(T1) TypeList<T1, TypeNull>
#define TYPELIST_2(T1, T2) TypeList<T1, TYPELIST_1(T2)>
#define TYPELIST_3(T1, T2, T3) TypeList<T1, TYPELIST_2(T2, T3)>
#define TYPELIST_4(T1, T2, T3, T4) TypeList<T1, TYPELIST_3(T2, T3, T4)>
#define TYPELIST_5(T1, T2, T3, T4, T5) TypeList<T1, TYPELIST_4(T2, T3, T4, T5)>
#define TYPELIST_6(T1, T2, T3, T4, T5, T6) TypeList<T1, TYPELIST_5(T2, T3, T4, T5, T6)>

template <class OBJECT, class KEY_TYPE>
struct ContainerUnorderedMap {
  std::unordered_map<KEY_TYPE, OBJECT *> _element;
};

template <class KEY_TYPE>
struct ContainerUnorderedMap<TypeNull, KEY_TYPE>
{
};

template <class H, class T, class KEY_TYPE>
struct ContainerUnorderedMap<TypeList<H, T>, KEY_TYPE> {
  ContainerUnorderedMap<H, KEY_TYPE> _elements;
  ContainerUnorderedMap<T, KEY_TYPE> _TailElements;
};

typedef TYPELIST_5(bool, char, short, int, long) AllMapStoredObjectTypes;

int32_t main(int32_t argc, char *argv[]) {
  ContainerUnorderedMap<AllMapStoredObjectTypes, float> _elements;

  return 0;
}
