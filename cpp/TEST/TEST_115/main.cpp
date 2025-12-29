#define INTERFACE_NAME LoginIntInterface

#define BEGIN_MERCURY_INTERFACE(INAME)                                         \
  namespace INAME {                                                            \
  Mercury::InterfaceMinder gMinder(#INAME);                                    \
                                                                               \
  void registerWithInterface(Mercury::NetworkInterface &networkInterface) {    \
    gMinder.registerWithInterface(networkInterface);                           \
  }                                                                            \
                                                                               \
  Mercury::Reason                                                              \
  registerWithMachined(Mercury::NetworkInterface &networkInterface, int id) {  \
    return gMinder.registerWithMachined(networkInterface.address(), id);       \
  }                                                                            \
                                                                               \
  Mercury::Reason registerWithMachinedAs(                                      \
      const char *name, Mercury::NetworkInterface &networkInterface, int id) { \
    return gMinder.registerWithMachinedAs(name, networkInterface.address(),    \
                                          id);                                 \
  }

#define END_MERCURY_INTERFACE() }

#define NULL_IF_NOT_SERVER(ARG) ARG

#define HANDLER_ARGUMENT(NAME) &gHandler_##NAME

#define USE_TYPEDEF_WORKAROUND(TYPE, NAME) TYPE##_##NAME##_Handler

#define HANDLER_STATEMENT(NAME, TYPE, ARG) TYPE gHandler_##NAME(ARG);

#define MERCURY_MESSAGE(NAME, STYLE, PARAM, HANDLER)                           \
  const Mercury::InterfaceElement &NAME =                                      \
      gMinder.add(#NAME, Mercury::STYLE, PARAM, NULL_IF_NOT_SERVER(HANDLER));

#define MERCURY_EMPTY_MESSAGE(NAME, HANDLER)                                   \
  MERCURY_MESSAGE(NAME, FIXED_LENGTH_MESSAGE, 0, HANDLER)

#define MERCURY_FIXED_MESSAGE(NAME, PARAM, HANDLER)                            \
  MERCURY_MESSAGE(NAME, FIXED_LENGTH_MESSAGE, PARAM, HANDLER)

#define MERCURY_VARIABLE_MESSAGE(NAME, PARAM, HANDLER)                         \
  MERCURY_MESSAGE(NAME, VARIABLE_LENGTH_MESSAGE, PARAM, HANDLER)

#define MERCURY_STRUCT_MESSAGE(NAME, HANDLER)                                  \
  struct NAME##Args;                                                           \
  MERCURY_MESSAGE(NAME, 0, 0, 0)                                               \
  /** @internal */                                                             \
  Mercury::Bundle &operator<<(Mercury::Bundle &b, const struct NAME##Args &s); \
  /** @internal */                                                             \
  struct NAME##Args

#define CREATE_TYPEDEF_WORKAROUND(TYPE, NAME)                                  \
  typedef StructMessageHandler<TYPE, INTERFACE_NAME::NAME##Args>               \
      TYPE##_##NAME##_Handler;

#define MERCURY_HANDLED_STRUCT_MESSAGE(NAME, HANDLERTYPE, HANDLERARG)          \
  HANDLER_STATEMENT(NAME, HANDLERTYPE, HANDLERARG)                             \
  MERCURY_STRUCT_MESSAGE(NAME, HANDLER_ARGUMENT(NAME))

#define MERCURY_STRUCT_GOODIES(NAME)                                           \
  static NAME##Args &start(Mercury::Bundle &b,                                 \
                           Mercury::ReliableType reliable =                    \
                               Mercury::RELIABLE_DRIVER) {                     \
    return *(NAME##Args *)b.startStructMessage(NAME, reliable);                \
  }                                                                            \
  static NAME##Args &startRequest(                                             \
      Mercury::Bundle &b, Mercury::ReplyMessageHandler *handler,               \
      void *arg = NULL, int timeout = Mercury::DEFAULT_REQUEST_TIMEOUT,        \
      Mercury::ReliableType reliable = Mercury::RELIABLE_DRIVER) {             \
    return *(NAME##Args *)b.startStructRequest(NAME, handler, arg, timeout,    \
                                               reliable);                      \
  }                                                                            \
  static const Mercury::InterfaceElement &interfaceElement() { return NAME; }

#define BEGIN_HANDLED_STRUCT_MESSAGE(NAME, HANDLERTYPE, HANDLERARG)            \
  MERCURY_HANDLED_STRUCT_MESSAGE(NAME, HANDLERTYPE, HANDLERARG) {              \
    MERCURY_STRUCT_GOODIES(NAME)

#define BW_BEGIN_STRUCT_MSG(TYPE, NAME)                                        \
  CREATE_TYPEDEF_WORKAROUND(TYPE, NAME)                                        \
  BEGIN_HANDLED_STRUCT_MESSAGE(NAME, USE_TYPEDEF_WORKAROUND(TYPE, NAME),       \
                               &TYPE::NAME)

#define END_STRUCT_MESSAGE()                                                   \
  }                                                                            \
  ;

#define BW_ANONYMOUS_CHANNEL_CLIENT_MSG(SERVER_INTERFACE)                      \
  MERCURY_FIXED_MESSAGE(                                                       \
      SERVER_INTERFACE##Birth, sizeof(Mercury::Address),                       \
      NULL /* Handler set by BW_INIT_ANONYMOUS_CHANNEL_CLIENT */)

#define MF_REVIVER_PING_MSG()                                                  \
  MERCURY_VARIABLE_MESSAGE(reviverPing, 2, &ReviverSubject::instance())

BEGIN_MERCURY_INTERFACE(LoginIntInterface)

  BW_ANONYMOUS_CHANNEL_CLIENT_MSG(DBAppMgrInterface)
  
  MERCURY_EMPTY_MESSAGE(controlledShutDown, &gShutDownHandler)
  
  BW_BEGIN_STRUCT_MSG(LoginApp, handleDBAppMgrBirth)
  Mercury::Address addr;
  END_STRUCT_MESSAGE()
  
  BW_BEGIN_STRUCT_MSG(LoginApp, notifyDBAppAlpha)
  Mercury::Address addr;
  END_STRUCT_MESSAGE()
  
  MF_REVIVER_PING_MSG()

END_MERCURY_INTERFACE()
