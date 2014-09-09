#ifndef DCFTIME_IFACE_H_
#define DCFTIME_IFACE_H_

class dcftime_iface {
public:
  virtual ~dcftime_iface() = default;
  virtual long dcfTimeUnix() = 0;
};

#endif // DCFTIME_IFACE_H_

