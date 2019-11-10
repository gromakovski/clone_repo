#ifndef TYPES_H
#define TYPES_H

#include <stdint.h>
#include <vector>

using IpAdress = std::vector<uint8_t> ; //содержит 4 поля для ip адреса. Может лучше std::array<std::string, 4>
using IpVector = std::vector<IpAdress> ;

#endif
