syscall:::entry
{
	trace(execname);
}

proc:::exec-success 
/
	uid == $uid
/
{
	trace(curpsinfo->pr_psargs); 
}

proc:::exit
{
        @[execname] = quantize(timestamp);
}

proc:::signal-send
{
        @[execname, stringof(args[1]->pr_fname), args[2]] = count();
}

syscall::open*:entry
{
	printf("%s %s",execname,copyinstr(arg0));
}

syscall:::entry
{
	@num[execname] = count();
}

proc:::lwp-exit
/tid != 1/
{
	@[execname] = quantize(timestamp);
}

io:::done
/uid == $1/
{
	printf("%d took input",$1);
}

syscall:::exit
{
	@num[probefunc] = count();
}

syscall:::entry
{
	@num[pid,execname] = count();
}

