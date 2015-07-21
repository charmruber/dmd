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

template staticIndexOf(T, TList...) {
    enum staticIndexOf = genericIndexOf!(T, TList).index;
}

template staticIndexOf(alias T, Tlist...) {
    enum staticIndexOf = genericIndexOf!(T, TList).index;
}

unittest {
    import std.stdio;

    void foo() {
	writeln("The index of long is $s", staticIndexOf!(long, AliasSeq!(int, long, double)));
    }
}

private template genericIndexOf(args...)
    if(args.length >= 1) {
    alias e = Alias!(args[0]);
    alias tuple = args[1 .. $];

    static if(tuple.length) {
	alias head = Alias!(tuple[0]);
	alias tail = tuple[1 .. $];

	static if(isSame!(e, head)) {
	    enum index = 0;
	}else {
	    enum next = genericIndexOf!(e, tail).index;
	    enum index = (next == -1) ? -1 : 1 + next;
	}
    }else {
	enum index = -1;
    }
}

unittest {
    static assert(staticIndexOf!( byte, byte, short, int, long) ==  0);
    static assert(staticIndexOf!(short, byte, short, int, long) ==  1);
    static assert(staticIndexOf!(  int, byte, short, int, long) ==  2);
    static assert(staticIndexOf!( long, byte, short, int, long) ==  3);
    static assert(staticIndexOf!( char, byte, short, int, long) == -1);
    static assert(staticIndexOf!(   -1, byte, short, int, long) == -1);
    static assert(staticIndexOf!(void) == -1);
}

package:

template Alias(alias a) {
    static if(__traits(compiles, { alias x = a; }))
	alias Alias = a;
    else static if(__traits(compiles, { enum x = a; }))
	enum Alias a;
    else
        static assert(0, "Cannot alias " ~ a.stringof);
}

template Alias() {

}
	       
