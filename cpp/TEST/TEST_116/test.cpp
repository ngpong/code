#include <iostream>
#include <unordered_map>

class TypeNull;

template<typename HEAD, typename TAIL>
struct TypeList
{
  using Head = HEAD;
  using Tail = TAIL;
};


template<class OBJECT, class KEY_TYPE>
struct ContainerUnorderedMap
{
  std::unordered_map<KEY_TYPE, OBJECT *> _element;
};

/* First instantiated from: insights.cpp:31 */
#ifdef INSIGHTS_USE_TEMPLATE
template<>
struct ContainerUnorderedMap<bool, float>
{
  std::unordered_map<float, bool *, std::hash<float>, std::equal_to<float>, std::allocator<std::pair<const float, bool *> > > _element;
  // inline ContainerUnorderedMap() noexcept = default;
  // inline ~ContainerUnorderedMap() noexcept = default;
};

#endif
/* First instantiated from: insights.cpp:31 */
#ifdef INSIGHTS_USE_TEMPLATE
template<>
struct ContainerUnorderedMap<char, float>
{
  std::unordered_map<float, char *, std::hash<float>, std::equal_to<float>, std::allocator<std::pair<const float, char *> > > _element;
  // inline ContainerUnorderedMap() noexcept = default;
  // inline ~ContainerUnorderedMap() noexcept = default;
};

#endif
/* First instantiated from: insights.cpp:31 */
#ifdef INSIGHTS_USE_TEMPLATE
template<>
struct ContainerUnorderedMap<short, float>
{
  std::unordered_map<float, short *, std::hash<float>, std::equal_to<float>, std::allocator<std::pair<const float, short *> > > _element;
  // inline ContainerUnorderedMap() noexcept = default;
  // inline ~ContainerUnorderedMap() noexcept = default;
};

#endif
/* First instantiated from: insights.cpp:31 */
#ifdef INSIGHTS_USE_TEMPLATE
template<>
struct ContainerUnorderedMap<int, float>
{
  std::unordered_map<float, int *, std::hash<float>, std::equal_to<float>, std::allocator<std::pair<const float, int *> > > _element;
  // inline ContainerUnorderedMap() noexcept = default;
  // inline ~ContainerUnorderedMap() noexcept = default;
};

#endif
/* First instantiated from: insights.cpp:31 */
#ifdef INSIGHTS_USE_TEMPLATE
template<>
struct ContainerUnorderedMap<long, float>
{
  std::unordered_map<float, long *, std::hash<float>, std::equal_to<float>, std::allocator<std::pair<const float, long *> > > _element;
  // inline ContainerUnorderedMap() noexcept = default;
  // inline ~ContainerUnorderedMap() noexcept = default;
};

#endif
/* First instantiated from: insights.cpp:32 */
#ifdef INSIGHTS_USE_TEMPLATE
template<>
struct ContainerUnorderedMap<TypeList<char, TypeList<short, TypeList<int, TypeList<long, TypeNull> > > >, float>
{
  ContainerUnorderedMap<char, float> _elements;
  ContainerUnorderedMap<TypeList<short, TypeList<int, TypeList<long, TypeNull> > >, float> _TailElements;
  // inline ContainerUnorderedMap() noexcept = default;
  // inline ~ContainerUnorderedMap() noexcept = default;
};

#endif
/* First instantiated from: insights.cpp:32 */
#ifdef INSIGHTS_USE_TEMPLATE
template<>
struct ContainerUnorderedMap<TypeList<short, TypeList<int, TypeList<long, TypeNull> > >, float>
{
  ContainerUnorderedMap<short, float> _elements;
  ContainerUnorderedMap<TypeList<int, TypeList<long, TypeNull> >, float> _TailElements;
  // inline ContainerUnorderedMap() noexcept = default;
  // inline ~ContainerUnorderedMap() noexcept = default;
};

#endif
/* First instantiated from: insights.cpp:32 */
#ifdef INSIGHTS_USE_TEMPLATE
template<>
struct ContainerUnorderedMap<TypeList<int, TypeList<long, TypeNull> >, float>
{
  ContainerUnorderedMap<int, float> _elements;
  ContainerUnorderedMap<TypeList<long, TypeNull>, float> _TailElements;
  // inline ContainerUnorderedMap() noexcept = default;
  // inline ~ContainerUnorderedMap() noexcept = default;
};

#endif
/* First instantiated from: insights.cpp:32 */
#ifdef INSIGHTS_USE_TEMPLATE
template<>
struct ContainerUnorderedMap<TypeList<long, TypeNull>, float>
{
  ContainerUnorderedMap<long, float> _elements;
  ContainerUnorderedMap<TypeNull, float> _TailElements;
  // inline ContainerUnorderedMap() noexcept = default;
  // inline ~ContainerUnorderedMap() noexcept = default;
};

#endif
/* First instantiated from: insights.cpp:32 */
#ifdef INSIGHTS_USE_TEMPLATE
template<>
struct ContainerUnorderedMap<TypeNull, float>
{
  // inline constexpr ContainerUnorderedMap() noexcept = default;
};

#endif
/* First instantiated from: insights.cpp:38 */
#ifdef INSIGHTS_USE_TEMPLATE
template<>
struct ContainerUnorderedMap<TypeList<bool, TypeList<char, TypeList<short, TypeList<int, TypeList<long, TypeNull> > > > >, float>
{
  ContainerUnorderedMap<bool, float> _elements;
  ContainerUnorderedMap<TypeList<char, TypeList<short, TypeList<int, TypeList<long, TypeNull> > > >, float> _TailElements;
  // inline ContainerUnorderedMap() noexcept = default;
  // inline ~ContainerUnorderedMap() noexcept = default;
};

#endif

template<class KEY_TYPE>
struct ContainerUnorderedMap<TypeNull, KEY_TYPE>
{
};


template<class H, class T, class KEY_TYPE>
struct ContainerUnorderedMap<TypeList<H, T>, KEY_TYPE>
{
  ContainerUnorderedMap<H, KEY_TYPE> _elements;
  ContainerUnorderedMap<T, KEY_TYPE> _TailElements;
};


using AllMapStoredObjectTypes = TypeList<bool, TypeList<char, TypeList<short, TypeList<int, TypeList<long, TypeNull> > > > >;

int32_t main(int32_t argc, char ** argv)
{
  ContainerUnorderedMap<TypeList<bool, TypeList<char, TypeList<short, TypeList<int, TypeList<long, TypeNull> > > > >, float> _elements = ContainerUnorderedMap<TypeList<bool, TypeList<char, TypeList<short, TypeList<int, TypeList<long, TypeNull> > > > >, float>();
  return 0;
}
