module std.meta;

template AliasSeq(TList...) {
    alias AliasSeq = TList;
}

unittest {
    import std.meta;
    alias TL = AliasSeq!(int, double);

    int foo(TL td) {
	return td[0] + cast(int)td[1];
    }
}

unittest {
    alias TL = AliasSeq!(int, double);

    alias Types = AliasSeq!(TL, char);
    static assert(is(Types == AliasSeq!(int, double, char)));
}
