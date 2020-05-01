/* Copyright (C) 2000 by Massimiliano Ghilardi
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 */
#ifndef _TWIN_METHODS_H
#define _TWIN_METHODS_H

#include "obj/fn.h"

byte FindInfo(menu Menu, dat i);
window FakeOpenTerm(const char *arg0, const char *const *argv);
widget FakeKbdFocus(widget W);
byte FakeWriteAscii(window Window, uldat Len, const char *Ascii);
byte FakeWriteString(window Window, uldat Len, const char *String);
byte FakeWriteTRune(window Window, uldat Len, const trune *TRune);
byte FakeWriteTCell(window Window, dat x, dat y, uldat Len, const tcell *Attr);
tpos FakeFindBorderWindow(window W, dat u, dat v, byte Border, tcell *PtrAttr);

#define Do(Command, ObjName) (Fn##ObjName->Command)

#define Act(Command, Obj) ((Obj)->Fn->Command)

#define Delete(Obj) Act(Delete, Obj)(Obj)

#define DeleteList(First)                                                                          \
  while (First)                                                                                    \
  Delete(First)

#define InsertOnly(ObjName, Obj, Parent) Act(Insert, (Obj))((Obj), (Parent), NULL, NULL)

#define InsertFirst(ObjName, Obj, Parent)                                                          \
  Act(Insert, (Obj))((Obj), (Parent), NULL, (Parent)->First##ObjName)

#define InsertMiddle(ObjName, Obj, Parent, ObjPrev, ObjNext)                                       \
  Act(Insert, (Obj))((Obj), (Parent), (ObjPrev), (ObjNext))

#define InsertLast(ObjName, Obj, Parent)                                                           \
  Act(Insert, (Obj))((Obj), (Parent), (Parent)->Last##ObjName, NULL)

#define Remove(Obj) Act(Remove, (Obj))(Obj)

#define MoveFirst(ObjName, Parent, Obj) (Remove(Obj), InsertFirst(ObjName, (Obj), (Parent)))

#define MoveLast(ObjName, Parent, Obj) (Remove(Obj), InsertLast(ObjName, (Obj), (Parent)))

#define SendMsg(MsgPort, WhichMsg) (InsertLast(Msg, (WhichMsg), (MsgPort)))

#define Info4Menu(Menu, Flags, Len, Text, ColText)                                                 \
  Act(SetInfo, (Menu))((Menu), (Flags), (Len), (Text), (ColText))

#define Win4Menu(Menu) Do(Create4Menu, Window)(FnWindow, (Menu))

#define Row4Menu(Window, Code, Flags, Len, Name)                                                   \
  (row) Do(Create4Menu, MenuItem)(FnMenuItem, (obj)(Window), (window)0, (Code), (Flags), (Len),    \
                                  (Name))

#define Item4Menu(Menu, Window, Flags, Len, Name)                                                  \
  Do(Create4Menu, MenuItem)(FnMenuItem, (obj)(Menu), (Window), (udat)0, (Flags), (Len), (Name))

#define Item4MenuCommon(Menu) Do(Create4MenuCommon, MenuItem)(FnMenuItem, (Menu))

void *OverrideMth(void **where, void *OldMethod, void *NewMethod);

#define OverrideMethod(ObjName, Command, ExpectedMethod, NewMethod)                                \
  OverrideMth((void **)&(Fn##ObjName->Command), (void *)ExpectedMethod, (void *)NewMethod)

#endif /* _TWIN_METHODS_H */
