#pragma once

#include "dsymbol.h"

struct OutBuffer;

struct DebugSymbol : dsymbol {
  unsigned level;

  DebugSymbol(Identifier *ident);
  DebugSymbol(unsigned level);

  void addMember(ScopeDsymbol);
  void semantic(Scope *sc);
  void toCBuffer(OutBuffer *buf);
};

struct VersionSymbol : dsymbol {
  unsigned level;
  VersionSymbol();
}
